FROM python:3.12-slim

RUN groupadd -g 1000 student \
    && useradd -m -u 1000 -g student -s /bin/bash student

RUN pip install --no-cache-dir flask

WORKDIR /workspace/src

USER student
