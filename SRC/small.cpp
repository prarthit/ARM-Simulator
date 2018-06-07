#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<vector>
#include<stdlib.h>

using namespace std;

#include "check.h"
#include "executes.h"
#include "small.h"

int reg_id(string s)
{
    int rindex;
    int k=1;
    int l;
    int a[2];
    for(int x=0;x<2;x++)
    {
        a[x]=0;
    }

    if(s=="pc")
        return 15;

    if(s=="lr")
        return 14;

    while(k<s.length())
    {
        l=s[k];

        a[k-1]=l-48;
        k++;
    }

    if(s.length()>=3)
        rindex=10*a[0]+a[1];
    else
        rindex=a[0];

    return rindex;
}


void chrtostr(string *s,char *c)
{
    if(c!=NULL)
        *s = string(c);
    else
        *s = "";
}


void removespace(string *s)
{
    if((*s)!="")
    {
        string line = *s;
        string newp = *s;

        int j=0;

        for(int i = 0; i < line.size();i++)
        {
            if (line[i] != ' ')
            {
                newp[j] = line[i];
                j++;
                if(i<line.size()-2 && line[i+1]==' ')
                {
                    newp[j] = line[i+1];
                    i++;
                    j++;
                }
            }
        }

        newp.resize(j);

        *s = newp;
    }

}


void disp_reg()
{
    cout<<"****************************************************************"<<endl;
    for(int i=0;i<16;i++)
    {
        cout<<"R"<<i<<" = "<<r[i]<<endl;
    }

    cout<<"****************************************************************"<<endl;
}

