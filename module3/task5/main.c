#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

static volatile sig_atomic_t sigint_cnt = 0;
static volatile sig_atomic_t should_quit = 0;
static int log_fd = -1;

void signal_handler(int sig) {
    const char *msg;
    
    if (sig == SIGINT) {
        sigint_cnt++;
        msg = "Получен и обработан сигнал SIGINT\n";
        if (sigint_cnt >= 3) {
            should_quit = 1;
        }
    } else if (sig == SIGQUIT) {
        msg = "Получен и обработан сигнал SIGQUIT\n";
    } else {
        return; 
    }

    write(log_fd, msg, strlen(msg));
}

int main(void) {
    log_fd = open("counter.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (log_fd < 0) {
        perror("Ошибка открытия файла");
        return 1;
    }

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; 

    if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("Ошибка установки обработчика сигнала");
        close(log_fd);
        return 1;
    }

    int counter = 1;
    char buf[32];

    while (!should_quit) {
        int len = snprintf(buf, sizeof(buf), "%d\n", counter);
        if (len > 0) {
            write(log_fd, buf, len);
        }
        sleep(1);
        counter++;
    }

    const char *end_msg = "Программа завершена после 3-го сигнала SIGINT.\n";
    write(log_fd, end_msg, strlen(end_msg));
    close(log_fd);
    
    return 0;
}