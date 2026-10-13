FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential gcc-multilib libc6-dev-i386 \
    gdb binutils file python3 python3-pwntools python3-capstone \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /bin/bash student

USER student

WORKDIR /workspace

CMD ["/bin/bash"]
