/* vuln.c - mini-analyseur d'un format "FUZZ<payload>" avec un debordement de pile */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Analyse un enregistrement : si l'entete vaut "FUZZ", copie le reste
   dans un tampon de 64 octets SANS verifier la taille (vulnerabilite). */
void parse(const unsigned char *data, size_t len) {
    char buf[64];
    if (len >= 4 && data[0]=='F' && data[1]=='U' && data[2]=='Z' && data[3]=='Z') {
        size_t paylen = len - 4;
        memcpy(buf, data + 4, paylen);   /* BUG : paylen peut depasser 64 */
        buf[paylen] = '\0';              /* BUG : ecriture hors-bornes */
        printf("enregistrement analyse (%zu octets)\n", paylen);
    }
}

int main(int argc, char **argv) {
    unsigned char data[1024];
    long n;
    if (argc >= 2) {                     /* mode fichier (pour rejouer un crash) */
        FILE *f = fopen(argv[1], "rb");
        if (!f) return 1;
        n = (long)fread(data, 1, sizeof data, f);
        fclose(f);
    } else {                             /* mode stdin (fuzzing) */
        n = (long)read(0, data, sizeof data);
    }
    if (n < 0) return 1;
    parse(data, (size_t)n);
    return 0;
}
