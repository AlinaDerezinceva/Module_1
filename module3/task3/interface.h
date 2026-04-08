#ifndef INTERFACE_H
#define INTERFACE_H

#include "structures.h"

void readLine(char* s, int n);
void clearInput(void);
int printMainMenu(void);
Contact printAddMenu(void);
void printOne(Contact* c);

#endif