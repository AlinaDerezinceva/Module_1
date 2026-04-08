#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ip_utils.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Использование: %s <шлюз> <маска> <N>\n", argv[0]);
        return 1;
    }

    uint32_t gateway = ip_to_int(argv[1]);
    uint32_t mask = ip_to_int(argv[2]);
    int n = atoi(argv[3]);

    uint32_t network = get_network(gateway, mask);

    srand(time(NULL));

    int local = 0, remote = 0;

    for (int i = 0; i < n; i++) {
        uint32_t dest = random_ip();
        if (get_network(dest, mask) == network)
            local++;
        else
            remote++;
    }

    printf("Всего пакетов: %d\n", n);
    printf("Локальная подсеть: %d (%.2f%%)\n", 
           local, 100.0 * local / n);
    printf("Другие сети: %d (%.2f%%)\n", 
           remote, 100.0 * remote / n);

    return 0;
}