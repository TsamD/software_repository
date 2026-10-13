#include <stdio.h>
#include <stdlib.h>
int main(void){
    int *t = malloc(4*sizeof(int));
    t[0]=1; t[1]=2;           /* t[2], t[3] non initialises */
    int s=0;
    for(int i=0;i<4;i++) s += t[i];   /* lecture de valeurs non initialisees */
    if (s > 1000) printf("grand\n"); else printf("petit (s=%d)\n", s);
    free(t);
    return 0;
}
