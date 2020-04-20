/* Korean Sentence Splitter
 * Split Korean text into sentences using heuristic algorithm.
 *
 * Copyright (C) 2019 Sang-Kil Park <skpark1224@hyundai.com>
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */
#include <iostream>
#include <vector>

#include <algorithm>
#include <cctype>
#include <stack>
#include "sentence_splitter.h"

/**
 * kss is an abbreviate of 'Korean Sentence Splitter'.
 */
namespace kss {
    // Return length of UTF-8 character from a text.
    int getUTF8ChrLength(const std::string &text, size_t i) {
        int len = 1;

        if ((text[i] & 0xf8) == 0xf0) len = 4;       // 1111 0xxx
        else if ((text[i] & 0xf0) == 0xe0) len = 3;  // 1110 xxxx
        else if ((text[i] & 0xe0) == 0xc0) len = 2;  // 110x xxxx
        if ((i + len) > text.length()) len = 1;

        return len;
    }

    // Be careful using only this function to test for string equality because there's a hash collision exists.
    // https://stackoverflow.com/a/16388610
    constexpr unsigned int str2hash(const char *str, int h = 0) {
        return !str[h] ? 5381 : (str2hash(str, h + 1) * 33) ^ str[h];
    }

    void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !isspace(ch);
        }));
    }

    void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !isspace(ch);
        }).base(), s.end());
    }

    // Trim std::string using C++11 lambdas.
    void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    // Trim sentence and adds to result vector.
    void doTrimSentPushResults(std::string &curSentence, std::vector<std::string> &results) {
#if DEBUG
        std::cout << "BREAK:" << curSentence << std::endl;
#endif
        trim(curSentence);
        results.push_back(curSentence);
        curSentence.clear();
    }

    void doPushPopSymbol(std::stack<std::string> &stack, const std::string &symbol) {
        if (stack.empty()) {
            stack.push(symbol);
        } else {
            if (stack.top() == symbol) {
                stack.pop();
            } else {
                stack.push(symbol);
            }
        }
    }

    void processSingleQuotes(unsigned int hash, const std::string &str, const std::string &prevChr,
                             const std::string &prevPrevChr, std::stack<std::string> &stack) {
        // str[1] must be single quotation mark(').
        if (hash == str2hash(str.substr(2, 1).c_str())) {
            if (str2hash(prevChr.c_str()) == str2hash(str.substr(1, 1).c_str())) {
                if (str2hash(prevPrevChr.c_str()) == str2hash(str.substr(0, 1).c_str())) {
                    doPushPopSymbol(stack, "'");
                }
            }
        }
    }
} // kss

std::vector<std::string> splitSentences(const std::string &text) {
    using namespace kss;

    std::string prevChr;
    std::string prevPrevChr;
    std::string curSentence;

    std::vector<std::string> results;
    Stats curStat = Stats::DEFAULT;

    std::stack<std::string> stack;

    for (size_t i = 0; i < text.length();) {
        int len = getUTF8ChrLength(text, i);
        // Due to Cython's `const char *` unexpected operation, use `std::string` instead of  `*chr`.
        const std::string chrString = text.substr(i, len);

        if (curStat == Stats::DEFAULT) {
            switch (str2hash(chrString.c_str())) {
                case str2hash("\""):    // Double Quotes
                case str2hash("“"):
                case str2hash("”"):
                    doPushPopSymbol(stack, "\"");
                    break;
                case str2hash("'"):     // Single Quotes
                case str2hash("´"):
                case str2hash("‘"):
                case str2hash("’"):
                    doPushPopSymbol(stack, "'");
                    break;
                case str2hash("다"):
                    if (stack.empty() && map[Stats::DA][prevChr] & ID::PREV) curStat = Stats::DA;
                    break;
                case str2hash("요"):
                    if (stack.empty() && map[Stats::YO][prevChr] & ID::PREV) curStat = Stats::YO;
                    break;
                case str2hash("."):
                case str2hash("!"):
                case str2hash("?"):
                    if (stack.empty() && map[Stats::SB][prevChr] & ID::PREV) curStat = Stats::SB;
                    break;
            }

            processSingleQuotes(str2hash(chrString.c_str()), "e's", prevChr, prevPrevChr, stack);     // He's, She's, There's
            processSingleQuotes(str2hash(chrString.c_str()), "I'm", prevChr, prevPrevChr, stack);     // I'm
            processSingleQuotes(str2hash(chrString.c_str()), "e'd", prevChr, prevPrevChr, stack);     // He'd
            processSingleQuotes(str2hash(chrString.c_str()), "n's", prevChr, prevPrevChr, stack);     // Men's
            processSingleQuotes(str2hash(chrString.c_str()), "n't", prevChr, prevPrevChr, stack);     // doesn't
        } else {
            if (isspace(*chrString.c_str()) || // Space
                map[Stats::COMMON][chrString] & ID::CONT) {
#if DEBUG
                std::cout << "STEP1:" << chrString << "/" << curStat << std::endl;
#endif

                if (map[curStat][prevChr] & ID::NEXT1) {
                    doTrimSentPushResults(curSentence, results);
                    curSentence.append(prevChr);
                    curStat = Stats::DEFAULT;
                }

                goto endif;
            }

            if (map[curStat][chrString] & ID::NEXT) {
#if DEBUG
                std::cout << "STEP2:" << chrString << "/" << curStat << std::endl;
#endif
                if (map[curStat][prevChr] & ID::NEXT1) {
                    curSentence.append(prevChr);
                }
                curStat = Stats::DEFAULT;
                goto endif;
            }

            if (map[curStat][chrString] & ID::NEXT1) {
#if DEBUG
                std::cout << "STEP3:" << chrString << "/" << curStat << std::endl;
#endif

                if (map[curStat][prevChr] & ID::NEXT1) {
                    doTrimSentPushResults(curSentence, results);
                    curSentence.append(prevChr);
                    curStat = Stats::DEFAULT;
                }
                goto endif;
            }

            if (map[curStat][chrString] & ID::NEXT2) {
#if DEBUG
                std::cout << "STEP4:" << chrString << "/" << curStat << std::endl;
#endif
                if (map[curStat][prevChr] & ID::NEXT1) {
                    curSentence.append(prevChr);
                } else {
                    doTrimSentPushResults(curSentence, results);
                }
                curStat = Stats::DEFAULT;
                goto endif;
            }

            if (!map[curStat][chrString] || // NOT exists.
                map[curStat][chrString] & ID::PREV) {
#if DEBUG
                std::cout << "STEP5:" << chrString << "/" << curStat << std::endl;
#endif

                doTrimSentPushResults(curSentence, results);
                if (map[curStat][prevChr] & ID::NEXT1) {
                    curSentence.append(prevChr);
                }
                curStat = Stats::DEFAULT;

                // It's not a good design we suppose, but it's the best unless we change the whole structure.
                switch (str2hash(chrString.c_str())) {
                    case str2hash("\""):
                    case str2hash("“"):
                    case str2hash("”"):
                        doPushPopSymbol(stack, "\"");
                        break;
                    case str2hash("'"):
                    case str2hash("´"):
                    case str2hash("‘"):
                    case str2hash("’"):
                        doPushPopSymbol(stack, "'");
                        break;
                }
                goto endif;
            }
#if DEBUG
            std::cout << "ERROR:" << chrString << "," << curStat << std::endl;
#endif
        }

        endif:
        if (curStat == Stats::DEFAULT || !(map[curStat][chrString] & ID::NEXT1)) {
            curSentence.append(chrString);
        }
        prevPrevChr = prevChr;
        prevChr = chrString;
        i += len;
    }

    if (!curSentence.empty()) {
        doTrimSentPushResults(curSentence, results);
    }
    if (map[curStat][prevChr] & ID::NEXT1) {
        curSentence.append(prevChr);
        doTrimSentPushResults(curSentence, results);
    }

    return results;
}
