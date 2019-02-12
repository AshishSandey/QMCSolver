#ifndef CALCI_H_INCLUDED
#define CALCI_H_INCLUDED
#include <vector>
#include <string>
#include"conversions.h"

using namespace std;

class CalcI
{
bool assembler(string &);
char calc(string);
public:
string exps;
vector<string> varargs;
char *values;
char evaluate();
void getvarargs();
};


#endif // CALCI_H_INCLUDED
