#include "QMC.h"

void QMC::getMT()
{const int n=pow(2,varargs.size());
values=new char[varargs.size()+1];
    for(int i=0; i<n; i++)
    {base_n(i,values,2,varargs.size());

    if(evaluate()=='1')
     min_terms.push_back(i);
    }

}

void QMC::autovarargs(int n)
{string name;
for(int i=0;i<n;i++)
{name=(char)65+i;
varargs.push_back(name);}}

bool QMC::reduce(string expression)
{exps=expression;
getvarargs();
getMT();
reduce();
}

bool QMC::reduce()
{if(min_terms.size()==0)
{Solution.push_back("0");
cout<<"Solution\n"<<Solution[0];
return true;}
vcount=varargs.size();
matrix table,nwtable;
gettable1(table);
vector<node> ftable;
int i=1;
do{

if(table.size()>1)
{cout<<"\n\n-------------------------    Table "<<++i<<"\t------------------------------\n";
tproc(table,nwtable);

}

for(int i=0;i<table.size();i++)
for(int j=0;j<table[i].size();j++)
if(table[i][j].ispaired==0)
ftable.push_back(table[i][j]);
table=nwtable;
nwtable.clear();
}
while(table.size());


cout<<"\n\nImplicant Chart\n\n";
for(int i=0;i<ftable.size();i++)
    {printvec(ftable[i].term);
cout<<'\t'<<ftable[i].data<<endl;}

vector<int> terms = min_terms;

getES(terms,ftable);
/*for(int i=0;i<terms.size();i++)
    cout<<terms[i]<<'\t';*/

/*cout<<"\nreduced ftable\n";
for(int i=0;i<ftable.size();i++)
    {printvec(ftable[i].term);
cout<<'\t'<<ftable[i].data<<endl;}*/
if(terms.size())
getNES(terms,ftable);
else Solution.push_back(ES);

cout<<"\nSolution\n";
for(int i=0;i<Solution.size();i++)
cout<<Solution[i]<<endl;

return 0;}


void QMC::gettable1(matrix &table)
{vector<node> a;
int rec[15]={},temp;
    for(int i=0; i<min_terms.size(); i++)
    {node nwnode;
     nwnode.term.push_back(min_terms[i]);
        nwnode.data=new char[vcount+1];
        base_n(min_terms[i],nwnode.data,2,vcount);

        a.push_back(nwnode);

        for(int j=0; j<vcount; j++)
            if(nwnode.data[j]=='1')
                rec[i]++;

    for(int j=i;j>0;j--)
       if(rec[j-1]>rec[j])
       {temp=rec[j];
       rec[j]=rec[j-1];
       rec[j-1]=temp;
       a[j]=a[j-1];
       a[j-1]=nwnode;
       }
       else break;
       }


        /*for(int i=0;i<a.size();i++)
       {puts(a[i].data);
       cout<<'\t'<<rec[i]<<'\n';}*/

vector<node> order(1,a[0]);
       for(int i=1;i<a.size();i++)
       {if(rec[i]!=rec[i-1])
       {table.push_back(order);
       order.clear();
       }
        order.push_back(a[i]);
       }
       table.push_back(order);
cout<<"Table 1 : Arrange in order according to 1(s)\n";
       for(int i=0;i<table.size();i++)
       {cout<<"\n----------------------------------\n\n";
        for(int j=0;j<table[i].size();j++)
       {cout<<table[i][j].term[0]<<'\t';
       puts(table[i][j].data);}}

}


void QMC::tproc(matrix &table, matrix &nwtable)
{
for(int i=1;i<table.size();i++)
{
vector<node> order;
for(int j=0;j<table[i-1].size();j++)
for(int k=0;k<table[i].size();k++)
{
int pos=-1,m=0;
for( ;m<vcount;m++)
if(table[i-1][j].data[m]!=table[i][k].data[m])
{if(pos==-1)
pos=m;
else
break;}

if(m!=vcount)
continue;

/*else
{
puts(table[i-1][j].data);
cout<<'\t';
puts(table[i][k].data);
cout<<endl;
}*/


table[i-1][j].ispaired=1;
table[i][k].ispaired=1;
if(table[i-1][j].term.size()>1)
{int x=0;
char temp[vcount+1];
strcpy(temp,table[i-1][j].data);
temp[pos]='x';
for(;x<order.size();x++)
if(strcmp(temp,order[x].data)==0)
break;
if(x!=order.size())
continue;}

node nwnode;
nwnode.term.insert(nwnode.term.begin(),table[i-1][j].term.begin(),table[i-1][j].term.end());
nwnode.term.insert(nwnode.term.end(),table[i][k].term.begin(),table[i][k].term.end());
nwnode.data=new char[vcount+1];
strcpy(nwnode.data,table[i-1][j].data);
nwnode.data[pos]='x';


order.push_back(nwnode);

}
if(order.size())
nwtable.push_back(order);
}//cout<<"size="<<nwtable.size()<<'\t'<<nwtable[0].size();
if(nwtable.size())
for(int i=0;i<nwtable.size();i++)
       {cout<<"\n----------------------------------\n";
           for(int j=0;j<nwtable[i].size();j++)
       {cout<<'\n';
       printvec(nwtable[i][j].term);
       cout<<'\t';
       puts(nwtable[i][j].data);}}
else cout<<"No grouping possible\n----------------------------------";
}


void QMC::getES(vector<int> &terms, vector<node> &ftable)
{int i,j,k,match;
for(i=0;i<min_terms.size();i++)
{for(j=0,match=-1;j<ftable.size();j++)
{for(k=0;k<ftable[j].term.size();k++)
if(ftable[j].term[k]==min_terms[i])
if(match==-1)
match=j;
else break;
if(k!=ftable[j].term.size())
break;}
if(j==ftable.size())
ftable[match].ispaired=1;}

for(i=0;i<ftable.size();)
if(ftable[i].ispaired==1)
{if(ES.size()>0)
    ES+='+';
ES+=Translate(ftable[i].data);

for(j=0;j<ftable[i].term.size();j++)
    for(int k=0;k<terms.size();k++)
        if(ftable[i].term[j]==terms[k])
            {terms.erase(terms.begin()+k);
            break;
            }


ftable.erase(ftable.begin()+i);
}
else i++;

cout<<"\n\nEssential : "<<ES<<endl;

}


void QMC::getNES(vector<int> &terms, vector<node> &ftable)
{int i,j,k;
vector<int> implist,term_product;
vector< vector<int> > temp;
vector< vector<int> > sol;
for(i=0;i<terms.size();i++)
{implist.clear();
for(j=0;j<ftable.size();j++)
for(k=0;k<ftable[j].term.size();k++)
if(ftable[j].term[k]==terms[i])
{if(i>0)
    implist.push_back(j);
else sol.push_back(vector<int>(1,j));
//cout<<j<<' ';
}
//cout<<endl;

if(i>0)
{//cout<<endl;
    //printvec(implist);

    for(int i=0;i<implist.size();i++)
    for(int j=0,k;j<sol.size();j++)
    {for(k=0;k<sol[j].size();k++)
    if(implist[i]==sol[j][k])
    break;
term_product=sol[j];
if(k==sol[j].size())
term_product.push_back(implist[i]);


for(int i=0,cont=0;i<temp.size();i++,cont=0)
{

    for(int j=0;j<term_product.size();j++)
    for(int k=0;k<temp[i].size();k++)
    if(term_product[j]==temp[i][k])
    cont++;

if(cont==term_product.size() || cont==temp[i].size())
{if(term_product.size()>temp[i].size())
term_product=temp[i];
temp.erase(temp.begin()+i);
i--;
}
}
temp.push_back(term_product);

}
sol=temp;
/*cout<<"sol\t";
for(int i=0;i<sol.size();i++)
{for(int j=0;j<sol[i].size();j++)
cout<<sol[i][j];
cout<<"\t";
}*/
temp.clear();

}
}

int s=sol.size(),mincost=getImplementationCost(sol[0],ftable),index=1;

while(index<s)
{int cost=getImplementationCost(sol[index],ftable);
    if(cost<=mincost)
        if(cost<mincost)
    {
        mincost=cost;
        sol.erase(sol.begin(),sol.begin()+index);
        s-=index;
        index=1;
    }
        else index++;

    else
    {sol.erase(sol.begin()+index);
    s--;}

}

string implicant;

Solution.insert(Solution.begin(),s,ES);
for(int i=0;i<s;i++)
for(int j=0;j<sol[i].size();j++)
{
    implicant=ftable[sol[i][j]].data;
    if(Solution[i].size())
    Solution[i]+='+';
Solution[i]+=Translate(implicant);
}


/*for(int i=0;i<sol.size();i++)
{for(int j=0;j<sol[i].size();j++)
cout<<sol[i][j];
cout<<'\t'<<sol[i].size()<<endl;
}*/

}


int QMC::getImplementationCost(vector<int> &cover,vector<node> &ftable)
{
    int s=cover.size(),cost=0;
    for(int i=0;i<s;i++)
    for(int j=0;ftable[cover[i]].data[j]!='\0';j++)
    if(ftable[cover[i]].data[j]!='x')
    ++cost;
    return cost;
}

string QMC::Translate(string term)
{string result="";
for(int i=0;i<vcount;i++)
if(term[i]!='x')
{if(result.size()>0)
    result+='.';
result+=varargs[i];
if(term[i]=='0')
    result+=39;
}
if(result.size())
return result;
else return "1";
}

void printvec(vector<int> a)
{for(int i=0;i<a.size();i++)
cout<<a[i]<<' ';}
