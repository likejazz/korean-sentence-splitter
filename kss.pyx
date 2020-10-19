from libcpp.string cimport string
from libcpp.vector cimport vector

from typing import List
from collections import namedtuple
import math

cdef extern from "sentence_splitter.h":
    vector[string] splitSentences(string)

def split_sentences(str) -> List[str]:
    results = []
    # Convert Python's `bytes` to C++'s `std::string`.
    res = splitSentences(str.encode('utf-8'))
    for r in res:
        results.append(r.decode('utf-8'))

    return results

SentenceIndex = namedtuple('SentenceIndex', ['start', 'end'])
ChunkWithIndex = namedtuple('ChunkWithIndex', ['start', 'text'])

def split_sentences_index(text) -> List[SentenceIndex]:
    def get_sentence_index(sentence):
        return SentenceIndex(text.index(sentence), text.index(sentence) + len(sentence))
    sentences = split_sentences(text)
    return [get_sentence_index(sentence) for sentence in sentences]


def split_chunks(text: str, max_length=128, overlap=True, indexes=None) -> List[ChunkWithIndex]:
    def get_chunk_with_index():
        start = span[0].start
        end = span[-1].end
        return ChunkWithIndex(span[0].start, text[start:end])
    if(indexes is None):
        indexes = split_sentences_index(text)
    span = []
    chunks = []
    for index in indexes:
        if(len(span) > 0):
            if(index.end - span[0].start > max_length):  # len = last_end - first_start
                chunks.append(get_chunk_with_index())
                if(overlap):
                    span = span[math.trunc(len(span)/2):]  # cut half
                else:
                    span = []
        span.append(index)
    chunks.append(get_chunk_with_index())
    return chunks