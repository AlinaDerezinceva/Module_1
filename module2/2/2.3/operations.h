#ifndef OPERATIONS_H
#define OPERATIONS_H

extern double (*operations[])(double, double);
#define OPS_COUNT 4

double sum(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

#endif