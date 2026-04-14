#include <stdio.h>
#include <string.h>
#include "logic.h"

static int read_command(char *buffer, size_t buf_size) {
    printf("myshell> ");
    fflush(stdout);
    
    if (fgets(buffer, buf_size, stdin) == NULL) {
        printf("\nВыход по EOF\n");
        return 0;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    return 1;
}

int main(void) {
    char line[MAX_CMD_LEN];
    CmdStage stages[MAX_STAGES];

    while (1) {
        if (!read_command(line, sizeof(line))) break;

        int n = parse_line(line, stages);
        if (n == 0) continue;

        if (n == 1 && is_builtin(stages[0].argv[0])) {
            break;
        }

        run_pipeline(stages, n);
    }

    return 0;
}