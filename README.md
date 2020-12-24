# Korean Sentence Splitter

<!-- TOC -->

- [Korean Sentence Splitter](#korean-sentence-splitter)
- [Installation](#installation)
    - [Usage](#usage)
    - [Demo](#demo)
    - [Requirements](#requirements)
        - [Mac, Linux](#mac-linux)
        - [Windows](#windows)
- [Build from scratch](#build-from-scratch)
    - [C++](#c)
    - [Python](#python)
        - [Uninstall](#uninstall)
    - [PyPI](#pypi)

<!-- /TOC -->

Split Korean text into sentences using heuristic algorithm. This algorithm was greatly inspired by EungGyun Kim <<jason.eg@kakaocorp.com>> who is Kakao NLP Leader and one of the most brilliant NLP Engineers in Korea.

I've started this project inspired by [this article](http://semantics.kr/%ED%95%9C%EA%B5%AD%EC%96%B4-%ED%98%95%ED%83%9C%EC%86%8C-%EB%B6%84%EC%84%9D%EA%B8%B0-%EB%B3%84-%EB%AC%B8%EC%9E%A5-%EB%B6%84%EB%A6%AC-%EC%84%B1%EB%8A%A5%EB%B9%84%EA%B5%90/) and we've achieved best result on the test set. And of course, It's very robust to both Spoken and Written expressions.

**NOTICE**(Written in Korean - 21 Dec, 2020):  
> 작년 즈음에 카카오에서 사용해오던 한국어 문장 분리기에 착안해 C++로 한국어 문장 분리기를 새롭게 만들었고, 오픈소스로 공개하여 좋은 반응을 얻은 바 있습니다. 그러나 지속적인 문의나 요청 사항에는 거의 대응을 하지 못했고, 결정적으로 저 또한 전혀 다른 프로젝트를 맡게 되어 더 이상 유지보수를 할 수가 없었는데요. 특히 C++로 구현하다 보니 빌드 문의가 정말 많았고, 원래는 Windows, Mac, Linux 각 OS별로 빌드하여 바이너리를 업로드하여 배포하도록 권장하고 있는데, 상용 프로젝트도 아니고 그렇게 까지 관리할 수는 없었습니다.  
>
> 결정적으로 문장 분리 자체가 엄청난 고성능을 요구해서 꼭 C++로 작성해야 하는건 아니었기에 빌드의 번거로움과 개발 유지보수를 감안하면 이제 다른 언어로 바꾸는게 좋겠다고 생각하던 차, 마침 고현웅님께서 파이썬으로 모두 포팅해주셨고, 또 꾸준히 개선해 나가는 모습을 보면서 이제는 프로젝트를 넘겨줄때가 됐음을 깨달았습니다.  
>
> 제가 올 초에 1.3.1까지 올렸었고, 오늘부터 고현웅님이 만드신 파이썬 포팅 버전으로 2.0.0이 시작됩니다. 그동안 저에게 들어와있던, 제가 처리하지 못했던 모든 이슈와 PR이 반영된 최종 개선 버전이고, 아마 앞으로도 잘 개선해주시리라 기대가 큽니다.  
>
> 팩키지 설치는 기존과 동일하게 `pip install kss`로 가능하며, 버그나 개선과 관련한 이슈는 새로운 레포인 https://github.com/hyunwoongko/kss 에 올려주시면 됩니다.  
>
> 앞으로도 많은 응원 부탁드립니다.  
> 감사합니다.

https://www.facebook.com/groups/TensorFlowKR/permalink/1383839988623722/

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
### Mac, Linux
- C++11
    - GCC or Clang with C++11 build supported.
- Python 3+

NOTICE: Google Test binary provided was built on macOS.
### Windows
- Microsoft C++ Build Tools
- Python 3+
- Cython  
```console
$ pip install cython
```

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
Python wrapper has implemented using Cython. You can execute build tasks by the command below:
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
