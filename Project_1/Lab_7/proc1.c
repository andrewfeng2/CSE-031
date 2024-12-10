#include <stdio.h>

int m = 10;
int n = 5;

int sum(int a, int b) {
    return a + b;
}

int main() {
    int result = sum(m, n);
    printf("%d\n", result);
    return 0;
}
