FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    python3-venv \
    gcc \
    gdb \
    libc6-dbg \
    curl \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m venv /opt/venv \
    && /opt/venv/bin/pip install --no-cache-dir \
       "cvss==3.6" \
       "Flask==3.1.1"

ENV PATH="/opt/venv/bin:${PATH}"

RUN useradd -m -s /bin/bash student
USER student
WORKDIR /workspace

CMD ["/bin/bash"]
