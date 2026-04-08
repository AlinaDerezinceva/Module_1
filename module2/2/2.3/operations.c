#include "operations.h"

double sum(double a, double b)      
{ 
    return a + b; 
}
double subtract(double a, double b) 
{ 
    return a - b; 
}
double multiply(double a, double b) 
{ 
    return a * b; 
}
double divide(double a, double b)   
{ 
    return a / b; 
}

double (*operations[])(double, double) = {
    sum, subtract, multiply, divide
};
