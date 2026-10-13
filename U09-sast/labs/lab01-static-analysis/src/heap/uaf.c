#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct { void (*action)(void); char nom[16]; } Session;
static void deconnexion(void){ printf("deconnexion executee\n"); }
int main(void){
    Session *s = malloc(sizeof *s);
    s->action = deconnexion;
    strcpy(s->nom, "alice");
    free(s);                 /* la memoire est rendue a l'allocateur */
    /* ... plus loin, un pointeur pendouillant est reutilise ... */
    s->action();             /* BUG : use-after-free -> appel indirect */
    return 0;
}
