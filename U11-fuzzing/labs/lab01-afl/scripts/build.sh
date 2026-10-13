#!/usr/bin/env bash
set -euo pipefail
cd /workspace
mkdir -p build corpus
# Campagne instrumentée AFL++ ; pas de désactivation globale des protections.
afl-clang-fast -O0 -g -fno-inline -fno-stack-protector src/vuln.c -o build/vuln_fuzz
# Diagnostic avec AddressSanitizer.
clang -O0 -g -fsanitize=address -fno-omit-frame-pointer src/vuln.c -o build/vuln_asan
clang -O0 -g -fsanitize=address -fno-omit-frame-pointer src/vuln_fixed.c -o build/vuln_fixed_asan
afl-clang-fast -O0 -g -fno-inline src/vuln_fixed.c -o build/vuln_fixed_fuzz
printf 'FUZZ' > corpus/seed1
printf 'FUZZhello' > corpus/seed2
printf 'Binaires prêts dans build/\n'
