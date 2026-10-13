/* code.c - programme a auditer (TP U5.3 / U9.3)
   Contient plusieurs faiblesses a identifier :
   - debordement via sprintf (CWE-787/121)
   - depassement d'entier sur un calcul de taille (CWE-190)
   - usage de strcpy non borne (CWE-120) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void banniere(const char *utilisateur) {
    char msg[64];
    sprintf(msg, "Bienvenue %s !", utilisateur);   /* pas de borne */
    printf("%s\n", msg);
}

char *copier(const char *src) {
    char *dst = malloc(32);
    strcpy(dst, src);                              /* pas de controle de taille */
    return dst;
}

int main(int argc, char **argv) {
    if (argc < 3) { printf("usage: %s <utilisateur> <n>\n", argv[0]); return 1; }

    banniere(argv[1]);

    int n = atoi(argv[2]);
    int taille = n * 100;                          /* depassement d'entier possible */
    char *buf = malloc(taille);                    /* taille potentiellement erronee */
    if (buf) { memset(buf, 'A', taille); free(buf); }

    char *c = copier(argv[1]);
    printf("copie: %s (%d octets demandes)\n", c, taille);
    free(c);
    return 0;
}
