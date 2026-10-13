#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv){
    int taille = (argc>1)? atoi(argv[1]) : 2000000000;
    int total = taille + 1000000000;   /* BUG : depassement d'entier signe possible */
    printf("total = %d\n", total);
    return 0;
}
