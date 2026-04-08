#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <число1> [число2] ...\n", argv[0]);
        return 1;
    }
    long max = LONG_MIN;
    for (int i = 1; i < argc; i++) {
        long val = strtol(argv[i], NULL, 10);
        if (val > max) max = val;
    }
    printf("Максимум: %ld\n", max);
    return 0;
}