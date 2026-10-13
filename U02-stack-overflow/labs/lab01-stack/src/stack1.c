#include <stdio.h>
#include <string.h>
#include <stddef.h>
struct frame { char buffer[32]; unsigned int value; };
int main(int argc, char **argv) {
    struct frame f = {{0}, 0};
    if (argc != 2) { fprintf(stderr, "Usage: %s INPUT\n", argv[0]); return 1; }
    strcpy(f.buffer, argv[1]); /* deliberately unsafe */
    printf("value = 0x%08x\n", f.value);
    return 0;
}
