#!/usr/bin/env bash
set -euo pipefail
mkdir -p bin
for n in 0 1 2 3; do
  gcc -m32 -O0 -g -fno-stack-protector -fno-pie -no-pie "src/stack${n}.c" -o "bin/stack${n}"
done
# stack5 : pile exécutable requise pour exécuter le shellcode déposé sur la pile.
gcc -m32 -O0 -g -fno-stack-protector -fno-pie -no-pie -z execstack "src/stack5.c" -o "bin/stack5"
printf 'Binaires construits dans bin/\n'

# stack4 : démonstration autonome du shellcode i386.
gcc -m32 -O0 -g -fno-stack-protector -fno-pie -no-pie -z execstack \
    src/stack4.c -o bin/stack4