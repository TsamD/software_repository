FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential gcc-multilib libc6-dev-i386 gdb binutils file python3 \
    python3-pip python3-venv ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Installation de Ropper dans un environnement Python isolé
RUN python3 -m venv /opt/ropper-venv \
    && /opt/ropper-venv/bin/pip install --no-cache-dir ropper

ENV PATH="/opt/ropper-venv/bin:${PATH}"

RUN useradd -m -s /bin/bash student

USER student
WORKDIR /workspace

CMD ["/bin/bash"]
