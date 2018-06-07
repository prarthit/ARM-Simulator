#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<vector>
#include<stdlib.h>

using namespace std;

#include "small.h"
#include "check.h"

void latency_fun()
{
    stringstream ss1;
    int itmp;
    ifstream inn1;
    string xyz,xyz1,line;
    char *temp;
    inn1.open("latency.txt");
    if (inn1.is_open())
    {
        while(!inn1.eof())
        {
            getline(inn1,line,'\n');
            temp = strtok (&line[0],"=");
            chrtostr(&xyz,temp);
            removespace(&xyz);
            cout<<xyz<<endl;

            temp = strtok (NULL,"");
            chrtostr(&xyz1,temp);
            removespace(&xyz1);
            ss1.str(xyz1);
            ss1>>itmp;

            if(xyz != "")
            {
                if(xyz=="add")
                    latency[0] = itmp;

                else if(xyz=="sub")
                    latency[1] = itmp;

                else if(xyz=="mul")
                    latency[2] = itmp;

                else if(xyz=="mov")
                    latency[3] = itmp;

                else if(xyz=="ldr")
                    latency[4] = itmp;

                else if(xyz=="str")
                    latency[5] = itmp;

                else if(xyz=="b")
                    latency[6] = itmp;

                else if(xyz=="bl")
                    latency[7] = itmp;

                else if(xyz=="bne")
                    latency[8] = itmp;

                else if(xyz=="bge")
                    latency[9] = itmp;

                else if(xyz=="ble")
                    latency[10] = itmp;

                else if(xyz=="cmp")
                    latency[11] = itmp;

                else if(xyz=="ldr_pseudo")
                    latency[12] = itmp;

                else if(xyz=="str_pseudo")
                    latency[13] = itmp;

                else
                    {cout<<"Wrong instruction(use ldr,add,sub,mov etc.)"<<endl;}
            }
        }
    }

    else
        cout<<"latency.txt file doesn't exist"<<endl;

}



/*
ADD = 0
SUB = 1
MUL = 2
MOV = 3
LDR = 4
STR = 5
B = 6
BL = 7
BNE = 8
BGE = 9
BLE = 10
CMP = 11
ldr_pseudo = 12
str_pseudo = 13
*/
