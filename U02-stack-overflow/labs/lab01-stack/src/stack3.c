#include <stdio.h>
#include <string.h>
#include <stdlib.h>
__attribute__((noinline)) void func(void) { puts("Bienvenue dans func()"); }
__attribute__((noinline)) void greet(const char *name) {
    char buffer[32];
    strcpy(buffer, name); /* deliberately unsafe: investigate return address */
    printf("Bonjour %s\n", buffer);
}
int main(int argc, char **argv) {
    if (argc != 2) { fprintf(stderr, "Usage: %s NAME\n", argv[0]); return 1; }
    func();
    greet(argv[1]);
    return 0;
}
