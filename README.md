# Korean Sentence Splitter

<!-- TOC -->

- [Korean Sentence Splitter](#korean-sentence-splitter)
- [Installation](#installation)
    - [Usage](#usage)
    - [Demo](#demo)
    - [Requirements](#requirements)
- [Build from scratch](#build-from-scratch)
    - [C++](#c)
    - [Python](#python)
        - [Uninstall](#uninstall)
    - [PyPI](#pypi)

<!-- /TOC -->

Split Korean text into sentences using heuristic algorithm. This algorithm was greatly inspired by EungGyun Kim <<jason.eg@kakaocorp.com>> who is Kakao NLP Leader and one of the most brilliant NLP Engineers in Korea.

I've started this project inspired by [this article](http://semantics.kr/%ED%95%9C%EA%B5%AD%EC%96%B4-%ED%98%95%ED%83%9C%EC%86%8C-%EB%B6%84%EC%84%9D%EA%B8%B0-%EB%B3%84-%EB%AC%B8%EC%9E%A5-%EB%B6%84%EB%A6%AC-%EC%84%B1%EB%8A%A5%EB%B9%84%EA%B5%90/) and we've achieved best result on the test set. And of course, It's very robust to both Spoken and Written expressions.

# Installation
The package is listed in the Python Package Index (PyPI), so you can install it with pip:

```bash
$ pip install kss
```

## Usage
```python
import kss

s = "회사 동료 분들과 다녀왔는데 분위기도 좋고 음식도 맛있었어요 다만, 강남 토끼정이 강남 쉑쉑버거 골목길로 쭉 올라가야 하는데 다들 쉑쉑버거의 유혹에 넘어갈 뻔 했답니다 강남역 맛집 토끼정의 외부 모습."
for sent in kss.split_sentences(s):
    print(sent)
```

The result is shown below:
```
회사 동료 분들과 다녀왔는데 분위기도 좋고 음식도 맛있었어요
다만, 강남 토끼정이 강남 쉑쉑버거 골목길로 쭉 올라가야 하는데 다들 쉑쉑버거의 유혹에 넘어갈 뻔 했답니다
강남역 맛집 토끼정의 외부 모습.
```

## Demo
<img src="https://raw.githubusercontent.com/likejazz/korean-sentence-splitter/master/assets/screenshot.png">

## Requirements
- C++11
    - GCC or Clang with C++11 build supported.
- Python 3

Google Test binary provided was built on macOS.

# Build from scratch
## C++
```
$ mkdir bld
$ cd bld
$ cmake ..
$ make
$ ./sentsplit
```

NOTICE: Google Test binary provided was built on macOS only. So, You cannot build test binary on linux.

```cpp
#include <iostream>
#include "sentence_splitter.h"

int main() {
    std::string s = "회사 동료 분들과 다녀왔는데 분위기도 좋고 음식도 맛있었어요 다만, 강남 토끼정이 강남 쉑쉑버거 골목길로 쭉 올라가야 하는데 다들 쉑쉑버거의 유혹에 넘어갈 뻔 했답니다 강남역 맛집 토끼정의 외부 모습.";
    for (auto sent : splitSentences(s)) {
        std::cout << sent << std::endl;
    }

    return 0;
}
```

The result is shown below:
```
회사 동료 분들과 다녀왔는데 분위기도 좋고 음식도 맛있었어요
다만, 강남 토끼정이 강남 쉑쉑버거 골목길로 쭉 올라가야 하는데 다들 쉑쉑버거의 유혹에 넘어갈 뻔 했답니다
강남역 맛집 토끼정의 외부 모습.
```

## Python
Python wrapper has implemented using Cython. You can execute build tasks by the command below.
```bash
$ python setup.py install --record files.txt
or
$ pip install .
```

### Uninstall
```bash
$ xargs rm -rf < files.txt
or
$ pip uninstall kss
```

## PyPI
```bash
$ python setup.py sdist
$ twine upload --repository-url https://test.pypi.org/legacy/ dist/*
```
