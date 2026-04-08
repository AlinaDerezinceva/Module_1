#ifndef IP_UTILS_H
#define IP_UTILS_H

#include <stdint.h>

// Преобразование IP из строки в число
uint32_t ip_to_int(const char *ip_str);

// Преобразование числа в IP строку
void int_to_ip(uint32_t ip, char *str);

// Получение адреса сети
uint32_t get_network(uint32_t ip, uint32_t mask);

// Генерация случайного IP
uint32_t random_ip(void);

#endif