#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "structures.h"
#include "logic.h"

#define EXIT_NOT_FOUND 127


int is_builtin(const char *cmd) {
    return (cmd != NULL && (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0));
}

int parse_line(char *line, CmdStage stages[]) {
    int stage_count = 0;
    char *p = line;

    while (*p) {
        while (isspace((unsigned char)*p)) p++;
        if (*p == '\0') break;

        if (stage_count >= MAX_STAGES) break;

        stages[stage_count].argc = 0;
        stages[stage_count].infile = NULL;
        stages[stage_count].outfile = NULL;

        while (*p && *p != '|') {
            while (isspace((unsigned char)*p)) p++;
            if (*p == '\0' || *p == '|') break;

            char *token_start = p;
            while (*p && !isspace((unsigned char)*p) && *p != '|') p++;

            if (*p) { *p = '\0'; p++; }

            if (strcmp(token_start, "<") == 0) {
                while (isspace((unsigned char)*p)) p++;
                char *fname = p;
                while (*p && !isspace((unsigned char)*p) && *p != '|') p++;
                if (*p) { *p = '\0'; p++; }
                if (*fname) stages[stage_count].infile = fname;
            } 
            else if (strcmp(token_start, ">") == 0) {
                while (isspace((unsigned char)*p)) p++;
                char *fname = p;
                while (*p && !isspace((unsigned char)*p) && *p != '|') p++;
                if (*p) { *p = '\0'; p++; }
                if (*fname) stages[stage_count].outfile = fname;
            } 
            else if (stages[stage_count].argc < MAX_ARGS - 1) {
                stages[stage_count].argv[stages[stage_count].argc++] = token_start;
            }
        }

        stages[stage_count].argv[stages[stage_count].argc] = NULL;
        if (stages[stage_count].argc > 0) stage_count++;

        if (*p == '|') p++;
    }
    return stage_count;
}

void run_pipeline(CmdStage stages[], int n) {
    if (n <= 0) return;

    int fd[MAX_STAGES-1][2];
    for (int i = 0; i < n - 1; i++) {
        if (pipe(fd[i]) == -1) {
            perror("Ошибка создания канала (pipe)");
            return;
        }
    }

    pid_t pids[MAX_STAGES];
    for (int i = 0; i < n; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("Ошибка fork");
            return;
        }

        if (pids[i] == 0) {
            // Ввод
            if (stages[i].infile) {
                int f = open(stages[i].infile, O_RDONLY);
                if (f == -1) { perror(stages[i].infile); exit(1); }
                dup2(f, STDIN_FILENO);
                close(f);
            } else if (i > 0) {
                dup2(fd[i-1][0], STDIN_FILENO);
            }

            // Вывод
            if (stages[i].outfile) {
                int f = open(stages[i].outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (f == -1) { perror(stages[i].outfile); exit(1); }
                dup2(f, STDOUT_FILENO);
                close(f);
            } else if (i < n - 1) {
                dup2(fd[i][1], STDOUT_FILENO);
            }

            for (int j = 0; j < n - 1; j++) {
                close(fd[j][0]);
                close(fd[j][1]);
            }

            if (stages[i].argc > 0) {
                execvp(stages[i].argv[0], stages[i].argv);
                
                char local_path[MAX_CMD_LEN];
                snprintf(local_path, sizeof(local_path), "./%s", stages[i].argv[0]);
                execv(local_path, stages[i].argv);
                
                perror(stages[i].argv[0]);
            }
            exit(EXIT_NOT_FOUND);
        }
    }

    // Родитель закрывает каналы и ждёт детей
    for (int i = 0; i < n - 1; i++) {
        close(fd[i][0]);
        close(fd[i][1]);
    }

    for (int i = 0; i < n; i++) {
        waitpid(pids[i], NULL, 0);
    }
}