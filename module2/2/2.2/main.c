#include <stdio.h>
#include "menu.h"
#include "operations.h"

int main() {
    int choice;
    double a, b, result;

    while (1) {
        print_menu();
        choice = get_choice();

        if (choice == -1) {
            printf("Ошибка ввода!\n");
            continue;
        }

        if (choice == 0) {
            printf("Выход\n");
            break;
        }

        if (choice < 1 || choice > 4) {
            printf("Неверный выбор!\n");
            continue;
        }

        if (!get_numbers(&a, &b)) {
            printf("Ошибка ввода чисел!\n");
            continue;
        }

        if (choice == 4 && b == 0) {
            printf("Делить на ноль нельзя!\n");
            continue;
        }

        switch (choice) {
            case 1: result = sum(a, b); break;
            case 2: result = subtract(a, b); break;
            case 3: result = multiply(a, b); break;
            case 4: result = divide(a, b); break;
        }

        printf("Результат: %.2lf\n", result);
    }

    return 0;
}