#include <stdio.h>
#include "menu.h"
#include "operations.h"

void print_menu() {
    const char *names[] = {"Сложение", "Вычитание", "Умножение", "Деление"};
    printf("\n");
    for (int i = 0; i < OPS_COUNT; i++) {
        printf("%d. %s\n", i + 1, names[i]);
    }
    printf("0. Выход\n");
}

int get_choice() {
    int c;
    printf("Выберите действие: ");
    if (scanf("%d", &c) == 1) {
        return c;
    } else {
        return -1;
    }
}

int get_numbers(double *a, double *b) {
    printf("Введите два числа: ");
    return (scanf("%lf %lf", a, b) == 2);
}