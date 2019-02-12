#ifndef CONVERSIONS_H_INCLUDED
#define CONVERSIONS_H_INCLUDED

#include <string.h>
#include <math.h>
#define BINARY 1
#define OCTAL 2
#define DECIMAL 3
#define HEX 4
#define TRUE 0
#define FALSE -1

int decimal(char *,int,int &);
int base_n(int,char *,int,int);
int get_samples(char *,int,int *);
void set_bitwidth(char *,int,char *);


#endif // CONVERSIONS_H_INCLUDED
