#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * stack5 — détournement du flot via un gadget `jmp esp` et shellcode sur la pile.
 *
 * Choix pédagogique : le gadget `jmp esp` (octets ff e4) est fourni À UNE ADRESSE
 * FIXE dans le binaire lui-même (compilé -no-pie). Conséquences :
 *   - adresse identique sous GDB, hors GDB, avec core, quelle que soit la longueur
 *     d'argv/env et l'état de l'ASLR  => labo reproductible, aucun hard-code ;
 *   - on n'exécute AUCUNE adresse libc, donc plus de dépendance à la base libc
 *     observée sous GDB (cause du segfault de la version précédente).
 * La technique enseignée (ret -> jmp esp -> shellcode sur la pile) est identique
 * à celle d'un gadget libc ; seule la SOURCE du gadget change.
 */
__asm__(
    ".text\n"
    ".globl jmp_esp_gadget\n"
    ".type  jmp_esp_gadget, @function\n"
    "jmp_esp_gadget:\n"
    "    jmp *%esp\n"              /* ff e4 */
    ".size  jmp_esp_gadget, .-jmp_esp_gadget\n"
);

__attribute__((noinline)) void greet(const char *name) {
    char buffer[40];
    strcpy(buffer, name);          /* deliberately unsafe */
    printf("Bonjour %s\n", buffer);
}

int main(int argc, char **argv) {
    if (argc != 2) { fprintf(stderr, "Usage: %s NAME\n", argv[0]); return 1; }
    greet(argv[1]);
    return 0;
}
