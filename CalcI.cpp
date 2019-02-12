#include "CalcI.h"

void CalcI::getvarargs()
{string varid;
int len=exps.size();
char ch;
for(int i=0;i<=len;i++)
{ch=exps[i];
    if(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')
        varid+=exps[i];
    else if(varid.size()&&ch>='0'&&ch<='9')
        varid+=exps[i];
    else
    if(varid.size())
    {int j;
    for(j=0;j<varargs.size();j++)
    if(varid==varargs[j])
    break;
    if(j==varargs.size())
    varargs.push_back(varid);
    varid.clear();
    }
}
}


char CalcI::evaluate()
{string exps=CalcI::exps;
    int st,l=exps.size(),en,flag=0,i,cnt;

     for(int i=0;i<exps.size();i++)
        if(exps[i]=='('||exps[i]==')')
        flag++;
    if(flag%2==0)
        cnt=flag/2;
    else
    return 'x';


     for(int n=0;n<cnt;n++)
    {l=exps.size();
        for(i=l-1;i>=0;i--)
    if(exps[i]=='(')
    {
        st=i;
        break;
    }


    for(i=st+1;i<l;i++)
        if(exps[i]==')')
        {
            en=i;
            break;
        }

        string a(exps.begin()+st+1,exps.begin()+en);
        if(!assembler(a))
            return 'x';

        exps[st]=a[0];
        exps.erase(exps.begin()+st+1,exps.begin()+en+1);

    }


    if(!assembler(exps))
        return 'x';

    return exps[0];
}


bool CalcI::assembler(string &a)
{//cout<<a<<'\t';
    int l=a.size(),j;
string var,fexps;
for(int i=0;i<l;i++)
{
   if(a[i]>='A'&&a[i]<='Z'||a[i]>='a'&&a[i]<='z')
    var.push_back(a[i]);
   else if(var.size()&&a[i]>='0' && a[i]<='9')
   var.push_back(a[i]);
   else
   {    if(var.size())
       for(j=0 ;j<varargs.size();j++)
        if(var==varargs[j])
        {fexps+=values[j];
        break;
        }

        var.clear();
        if(a[i]=='.' || a[i]=='+' || a[i]=='^' || a[i]==39 || a[i]=='1' || a[i]=='0')
        fexps.push_back(a[i]);
        else return false;

   }
}//cout<<fexps;
   for(j=0 ;j<varargs.size();j++)
        if(var==varargs[j])
        {fexps.push_back(values[j]);
        break;
        }
        //if(j==varargs.size())
        //return false;
        //cout<<fexps<<'\t';
        a[0]=calc(fexps);
        //cout<<a[0]<<endl;

return true;
}

char CalcI::calc(string fexps)
{//cout<<fexps<<'\t';
    int opr;
    for(int i=1;i<fexps.size();i++)
if(fexps[i]==39)
{fexps[i-1]=(fexps[i-1]=='0')?'1':'0';
fexps.erase(fexps.begin()+i);}

 for(int i=1;i<fexps.size()-1;i++)
if(fexps[i]=='^')
{fexps[i-1]=(fexps[i-1]!=fexps[i+1])? '1':'0';
fexps.erase(i,2);
i--;}


 for(int i=1;i<fexps.size()-1;i++)
if(fexps[i]=='.')
{fexps[i-1]=(fexps[i-1]=='1'&&fexps[i+1]=='1')?'1':'0';
fexps.erase(i,2);
i--;}


 for(int i=1;i<fexps.size()-1;i++)
if(fexps[i]=='+')
{fexps[i-1]=(fexps[i-1]=='1' || fexps[i+1]=='1')? '1':'0';
fexps.erase(i,2);
i--;}


return fexps[0];
}
