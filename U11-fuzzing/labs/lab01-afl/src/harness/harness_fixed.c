#include <stdio.h>
#include <string.h>

void analyse_message(const unsigned char *data, size_t size)
{
    char buffer[16];

    if (size < 4)
        return;

    if (memcmp(data, "TEST", 4) != 0)
        return;

    size_t longueur = size - 4;

    /* Correction : ne jamais dépasser la capacité du tampon */
    if (longueur > sizeof(buffer))
        longueur = sizeof(buffer);

    memcpy(buffer, data + 4, longueur);

    puts("Message analyse");
}

int main(void)
{
    unsigned char input[1024];

    size_t n = fread(input, 1, sizeof(input), stdin);

    analyse_message(input, n);

    return 0;
}
