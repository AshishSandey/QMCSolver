#ifndef QMC_H_INCLUDED
#define QMC_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include "conversions.h"
#include <vector>
#include "CalcI.h"

void printvec(vector<int> a);

class QMC : public CalcI
{struct node
{vector<int> term;
char *data;
int ispaired;
node()
{ispaired=0;}
};
typedef vector< vector<node> > matrix;

void gettable1(matrix& );
void tproc(matrix&, matrix&);
void getES(vector<int> &terms, vector<node> &ftable);
void getNES(vector<int> &terms, vector<node> &ftable);
int getImplementationCost(vector<int> &cover, vector<node> &ftable);
string Translate(string term);

public:
vector<int> min_terms;
int vcount;
string ES;
vector<string> Solution;
void getMT();
void autovarargs(int n);
bool reduce(string );
bool reduce();
};



#endif // QMC_H_INCLUDED
