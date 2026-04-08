#include <stdio.h>
#include "menu.h"

void print_menu() {
    printf("\n1. Сложение\n");
    printf("2. Вычитание\n");
    printf("3. Умножение\n");
    printf("4. Деление\n");
    printf("0. Выход\n");
}

int get_choice() {
    int choice;
    printf("Выберите действие: ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return choice;
}

int get_numbers(double *a, double *b) {
    printf("Введите два числа: ");
    if (scanf("%lf %lf", a, b) != 2) {
        while (getchar() != '\n');
        return 0;
    }
    return 1;
}