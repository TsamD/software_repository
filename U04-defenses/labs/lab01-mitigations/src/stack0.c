#include <stdio.h>
int add(int a, int b) { return a + b; }
int main(void) {
    int a = 1, b = 2, c = 3;
    int result = add(add(a, b), c);
    printf("result = %d\n", result);
    return 0;
}
