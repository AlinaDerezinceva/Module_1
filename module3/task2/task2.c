#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

int read_command(char *buffer, size_t buf_size) {
    printf("myshell> ");
    fflush(stdout);
    
    if (fgets(buffer, buf_size, stdin) == NULL) {
        printf("\nВыход по EOF\n");
        return 0;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    return 1;
}

int parse_args(char *line, char *argv[], int max_args) {
    int argc = 0;
    char *token = strtok(line, " \t");
    
    while (token != NULL && argc < max_args - 1) {
        argv[argc++] = token;
        token = strtok(NULL, " \t");
    }
    argv[argc] = NULL; 
    return argc;
}

int is_builtin(const char *cmd) {
    return (cmd != NULL && (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0));
}

void run_external(char *argv[]) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Ошибка fork");
        return;
    } 
    else if (pid == 0) {
        execvp(argv[0], argv);
        
        char local_path[MAX_CMD_LEN];
        snprintf(local_path, sizeof(local_path), "./%s", argv[0]);
        printf("1111\n");
        execv(local_path, argv);
        
        fprintf(stderr, "myshell: команда не найдена или не исполняемая: %s\n", argv[0]);
        exit(127);
    } 
    else {
        waitpid(pid, NULL, 0);
    }
}

int main(void) {
    char line[MAX_CMD_LEN];
    char *argv[MAX_ARGS];

    while (1) {
        if (!read_command(line, sizeof(line))) break;
        
        int argc = parse_args(line, argv, MAX_ARGS);
        if (argc == 0) continue; 
        
        if (is_builtin(argv[0])) break;
        
        run_external(argv);
    }

    return 0;
}