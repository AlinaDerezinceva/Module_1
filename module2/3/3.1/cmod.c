#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

void show_perms(int mode) {
    char letters[10];    
    
    if (mode & 0400) { 
        letters[0] = 'r'; 
    } else 
    { 
        letters[0] = '-'; 
    }
    if (mode & 0200) 
    { 
        letters[1] = 'w'; 
    } else 
    { 
        letters[1] = '-'; 
    }
    if (mode & 0100) { 
        letters[2] = 'x'; 
    } else 
    { 
        letters[2] = '-'; 
    }
    if (mode & 0040) { 
        letters[3] = 'r'; 
    } else 
    { 
        letters[3] = '-'; 
    }
    if (mode & 0020) 
    { 
        letters[4] = 'w'; 
    } else 
    { 
        letters[4] = '-'; 
    }
    if (mode & 0010) 
    { 
        letters[5] = 'x'; 
    } else 
    { 
        letters[5] = '-'; 
    }
    if (mode & 0004) { 
        letters[6] = 'r'; 
    } else 
    { 
        letters[6] = '-'; 
    }
    if (mode & 0002) { 
        letters[7] = 'w'; 
    } else 
    { 
        letters[7] = '-'; 
    }
    if (mode & 0001) { 
        letters[8] = 'x'; 
    } else 
    { 
        letters[8] = '-'; 
    }
    letters[9] = '\0';
    
    printf("Буквенное: %s\n", letters);
    printf("Цифровое: %o\n", mode & 0777);
    printf("Битовое:  ");
    
    for (int i = 8; i >= 0; i--) {
        if ((mode >> i) & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

int main() {
    int choice;
    char input[50];
    char filename[50];
    int mode = 0;
    struct stat st;

    int u_mask = 0700;
    int g_mask = 0070;
    int o_mask = 0007;
    int r_bit = 0444;
    int w_bit = 0222;
    int x_bit = 0111;

    while (1) {
        printf("Меню\n");
        printf("1. Ввести права\n");
        printf("2. Ввести имя файла\n");
        printf("3. Изменить права\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 0) break;

        if (choice == 1) {
            printf("Введите права (например 755 или rwxr-xr-x): ");
            scanf("%s", input);
            getchar();

            if (isdigit(input[0])) {
                mode = 0;
                for (int i = 0; input[i] != '\0'; i++) {
                    mode = mode * 8 + (input[i] - '0');
                }
            } else {
                mode = 0;
                if (input[0] == 'r') {
                    mode = mode | 0400;
                }
                if (input[1] == 'w') {
                    mode = mode | 0200;
                }
                if (input[2] == 'x') {
                    mode = mode | 0100;
                }
                if (input[3] == 'r') {
                    mode = mode | 0040;
                }
                if (input[4] == 'w') {
                    mode = mode | 0020;
                }
                if (input[5] == 'x') {
                    mode = mode | 0010;
                }
                if (input[6] == 'r') {
                    mode = mode | 0004;
                }
                if (input[7] == 'w') {
                    mode = mode | 0002;
                }
                if (input[8] == 'x') {
                    mode = mode | 0001;
                }
            }
            show_perms(mode);
        } 
        else if (choice == 2) {
            printf("Введите имя файла: ");
            scanf("%s", filename);
            getchar();

            if (stat(filename, &st) == 0) {
                mode = st.st_mode;
                printf("Файл: %s\n", filename);
                show_perms(mode);
            } else {
                printf("Ошибка: файл не найден!\n");
            }
        } 
        else if (choice == 3) {
            printf("Введите текущие права (например 644): ");
            scanf("%s", input);
            getchar();
            
            mode = 0;
            for (int i = 0; input[i] != '\0'; i++) {
                mode = mode * 8 + (input[i] - '0');
            }

            printf("Введите команду (например u+r): ");
            scanf("%s", input);
            getchar();

            char who = input[0];
            char op = input[1];
            char *perms = &input[2];
            
            int perm_val = 0;
            for (int i = 0; perms[i] != '\0'; i++) {
                if (perms[i] == 'r') {
                    perm_val = perm_val | 0444;
                }
                if (perms[i] == 'w'){
                    perm_val = perm_val | 0222;
                } 
                if (perms[i] == 'x') {
                    perm_val = perm_val | 0111;
                }
            }

            if (who == 'u') {
                if (op == '+'){
                    mode = mode | (perm_val & u_mask);
                } 
                if (op == '-'){
                    mode = mode & ~(perm_val & u_mask);
                } 
                if (op == '='){
                    mode = (mode & ~u_mask) | (perm_val & u_mask);
                } 
            }
            else if (who == 'g') {
                if (op == '+'){
                    mode = mode | (perm_val & g_mask);
                } 
                if (op == '-'){
                    mode = mode & ~(perm_val & g_mask);
                } 
                if (op == '='){
                    mode = (mode & ~g_mask) | (perm_val & g_mask);
                } 
            }
            else if (who == 'o') {
                if (op == '+'){
                    mode = mode | (perm_val & o_mask);
                } 
                if (op == '-'){
                    mode = mode & ~(perm_val & o_mask);
                } 
                if (op == '='){
                    mode = (mode & ~o_mask) | (perm_val & o_mask);
                } 
            }

            else if (who == 'a') {
                if (op == '+'){
                    mode = mode | perm_val;
                } 
                if (op == '-'){
                    mode = mode & ~perm_val;
                } 
                if (op == '='){
                    mode = perm_val;
                } 
            }

            printf("Результат изменения:\n");
            show_perms(mode);
        }
        else {
            printf("Неверный выбор.\n");
        }
    }

    return 0;
}
            
            
