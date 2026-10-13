#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void analyse_message(const unsigned char *data, size_t size)
{
    char buffer[16];

    if (size < 4)
        return;

    if (memcmp(data, "TEST", 4) != 0)
        return;

    /* Vulnérabilité volontaire : copie sans contrôle de taille */
    memcpy(buffer, data + 4, size - 4);

    puts("Message analyse");
}

int main(void)
{
    unsigned char input[1024];

    size_t n = fread(input, 1, sizeof(input), stdin);

    analyse_message(input, n);

    return 0;
}
