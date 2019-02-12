#include "conversions.h"

int decimal(char *input,int input_base,int &result)
{
    int samples[10];

    if(get_samples(input,16,samples)==FALSE)
        return FALSE;

    result=0;
    for(int i=0; i<strlen(input); i++)
        result=result+samples[i]*pow(input_base,strlen(input)-i-1);
    return TRUE;
}

int base_n(int input,char *result,int result_base,int width)
{char a[width+1];
    if(result_base>16)
        return FALSE;


    int l;
    if(input!=0)
    l=log(input)/log(result_base)+1;
    else l=0;
    if(l>width)
    return FALSE;

    for(int i=0,temp; i<l; i++)
    {
        temp=input%result_base;
        if(temp>9)
            a[l-i-1]=temp-10+65;
        else
            a[l-i-1]=temp+48;
        input=input/result_base;

    }
    a[l]='\0';

   set_bitwidth(a,width,result);
    return TRUE;
}

int get_samples(char *input,int input_base,int *samples)
{
    for(int i=0; input[i]!='\0'; i++)
    {
        if(input[i]>='0'&&input[i]<='9'&&input[i]<input_base)
            samples[i]=input[i]%48;
        else if(input[i]>='A'&&input[i]<=input_base-10+64)
            samples[i]=input[i]%65+10;
        else return FALSE;
    }
    return TRUE;
}

void set_bitwidth(char *input,int width,char *result )
{
    if(width>strlen(input))
    {
        int i;
        for(i=0; i<width-strlen(input); i++)
            result[i]='0';
        result[i]='\0';
        strcat(result,input);
    }
    else strcpy(result,input);
}
