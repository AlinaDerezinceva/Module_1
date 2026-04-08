#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int parse_number(const char *str, double *val) {
    char *endptr;
    errno = 0; 
    double v = strtod(str, &endptr);

    if (errno != 0 || str == endptr || *endptr != '\0') {
        return 0;
    }

    *val = v;
    return 1;
}


void process_argument(const char *arg) {
    double val;
    if (parse_number(arg, &val)) {
        printf("%g %g\n", val, val * 2);
    } else {
        printf("%s\n", arg);
    }
    fflush(stdout); 
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Нет аргументов для обработки.\n");
        return 0;
    }

    pid_t pid = fork(); 

    if (pid < 0) {
        perror("Ошибка fork()");
        return 1;
    }

    int total_args = argc - 1;
    int split_index = total_args / 2; 

    if (pid == 0) {
        for (int i = 1; i <= split_index; i++) {
            process_argument(argv[i]);
        }
        exit(0); 
    } else {
        for (int i = split_index + 1; i < argc; i++) {
            process_argument(argv[i]);
        }
        wait(NULL);
    }

    return 0;
}