#include <stdio.h>
#include "operations.h"
#include "menu.h"

int main() {
    int choice;
    double a, b, result;

    while (1) {
        print_menu();
        choice = get_choice();

        if (choice == 0) 
        { 
            printf("Выход\n"); 
            break; 
        }
        if (choice < 1 || choice > OPS_COUNT) 
        { 
            printf("Неверный выбор\n"); 
            continue; 
        }
        if (!get_numbers(&a, &b)) 
        { 
            printf("Ошибка ввода\n"); 
            while(getchar()!='\n'); 
            continue; 
        }
        if (choice == 4 && b == 0) 
        { 
            printf("Деление на ноль\n"); 
            continue; 
        }

        result = operations[choice - 1](a, b);
        
        printf("Результат: %.2lf\n", result);
        
    }
    return 0;
}