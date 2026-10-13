#include <stdio.h>
#include <string.h>
struct frame { char buffer[10]; unsigned char value; };
int main(int argc, char **argv) {
    struct frame f = {{0}, 0};
    if (argc != 2) { fprintf(stderr, "Usage: %s INPUT\n", argv[0]); return 1; }
    strcpy(f.buffer, argv[1]); /* deliberately unsafe */
    printf("value = 0x%02x\n", f.value);
    if (f.value == 0xf7) puts("Condition atteinte");
    return 0;
}
