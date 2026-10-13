FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
       afl++ clang llvm build-essential bash coreutils ca-certificates libclang-rt-18-dev python3 \
    && rm -rf /var/lib/apt/lists/*

ARG LAB_UID=1000
ARG LAB_GID=1000
RUN groupadd --gid "${LAB_GID}" student \
    && useradd --uid "${LAB_UID}" --gid "${LAB_GID}" --create-home --shell /bin/bash student \
    && mkdir -p /workspace \
    && chown student:student /workspace

ENV HOME=/home/student
WORKDIR /workspace
USER student
CMD ["/bin/bash"]
