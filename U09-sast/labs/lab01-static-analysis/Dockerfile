FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    cppcheck clang clang-tidy build-essential ca-certificates \
    python3 python3-pip python3-venv python3-flask  \
    && rm -rf /var/lib/apt/lists/*
# Bandit dans un environnement Python isolé
RUN python3 -m venv /opt/bandit-venv \
    && /opt/bandit-venv/bin/pip install --no-cache-dir bandit

RUN ln -s /opt/bandit-venv/bin/bandit /usr/local/bin/bandit

# Installer Semgrep dans un environnement Python isolé
RUN python3 -m venv /opt/semgrep-venv \
    && /opt/semgrep-venv/bin/pip install --no-cache-dir semgrep
RUN ln -s /opt/semgrep-venv/bin/semgrep /usr/local/bin/semgrep

RUN useradd -m -s /bin/bash student
USER student
WORKDIR /workspace
CMD ["/bin/bash"]
