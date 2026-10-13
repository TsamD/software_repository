#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv){
    char *buf = malloc(16);
    const char *src = (argc>1)? argv[1] : "chaine beaucoup trop longue pour 16";
    strcpy(buf, src);        /* BUG : heap-buffer-overflow si src>15 */
    printf("%s\n", buf);
    free(buf);
    return 0;
}
