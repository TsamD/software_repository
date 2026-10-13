#include <stdlib.h>
#include <string.h>
int main(void){
    char *p = malloc(32);
    strcpy(p, "donnee");
    free(p);
    /* ... chemin d'erreur qui libere a nouveau ... */
    free(p);                 /* BUG : double-free */
    return 0;
}
