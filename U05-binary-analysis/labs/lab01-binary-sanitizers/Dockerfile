FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    llvm-18 libclang-rt-18-dev clang radare2 strace ltrace less binutils gdb file gcc gcc-multilib libc6-dev-i386 python3 \
    && rm -rf /var/lib/apt/lists/*

ENV ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer-18
RUN useradd -m -s /bin/bash student
USER student
WORKDIR /workspace
CMD ["/bin/bash"]
