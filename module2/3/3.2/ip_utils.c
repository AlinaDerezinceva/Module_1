#include "ip_utils.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t ip_to_int(const char *ip_str) {
    unsigned int a, b, c, d;
    sscanf(ip_str, "%u.%u.%u.%u", &a, &b, &c, &d);
    return (a << 24) | (b << 16) | (c << 8) | d;
}

void int_to_ip(uint32_t ip, char *str) {
    sprintf(str, "%u.%u.%u.%u",
            (ip >> 24) & 255,
            (ip >> 16) & 255,
            (ip >> 8) & 255,
            ip & 255);
}

uint32_t get_network(uint32_t ip, uint32_t mask) {
    return ip & mask;
}

uint32_t random_ip(void) {
    return ((uint32_t)rand() << 16) | rand();
}