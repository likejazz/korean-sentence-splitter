FROM ubuntu:latest
MAINTAINER skpark1224@hyundai.com

ENV LC_ALL=C.UTF-8 \
    LANG=C.UTF-8

RUN apt-get update \
  && apt-get install -y python3-pip python3-dev \
  && cd /usr/local/bin \
  && ln -s /usr/bin/python3 python \
  && pip3 install --upgrade pip

WORKDIR /kss
COPY . /kss
RUN pip install -r requirements.txt

CMD tail -f /dev/null

# docker build -t kss .
# docker run -v /Users/likejazz/workspace/github.com/likejazz/korean-sentence-splitter:/kss --rm -it kss /bin/bash
