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
#include "topfivefun.h"

void add_exec(string what)
{
    int reg1,sec,chm;

    if(IDnEXE.second_r!=-1)
        sec = IDnEXE.second_val;
    else
        sec = 0;

    if(IDnEXE.third_r!=-1)
        chm = IDnEXE.third_val;
    else
        chm = IDnEXE.offset;

        if(what=="add" || what=="mov")
            {reg1=sec+chm;    num_clkcycl += latency[0];}
        else if(what=="sub")
            {reg1=sec-chm;    num_clkcycl += latency[1];}
        else if(what=="ldr" || what=="str" )
            {chm = IDnEXE.offset; reg1=(sec/4)+chm;}
        else //multiply
            {reg1=sec*chm;    num_clkcycl += latency[2];}

    IDnEXE.result = reg1;

    //disp_reg();
}


void bl_exec(string what)
{
    if(what=="bl")
        r[reg_id("lr")] = r[reg_id("pc")];

    int counter = 0;
    int addr = 0;
    string label,h;

    char *temp;

    label = IDnEXE.label;

    while(addr<(instructions.size()-1) && counter==0)
        {
            ss.clear();

            ss.str(instructions[addr]);
            getline(ss,h,'\n');

            temp = strtok (&h[0],":");
            chrtostr(&h,temp);

            if(h==label)
            {
                if(what=="b")
                {
                    counter++;
                    r[reg_id("pc")] = addr;
                    num_clkcycl += latency[6];
                }
                else if(what=="bne")
                {
                    if((cmp[0]==1 || cmp[2]==1) && cmp[1]==0)
                    {
                        counter++;
                        r[reg_id("pc")] = addr;
                        num_clkcycl += latency[8];
                    }
                    else
                    {
                        num_clkcycl += latency[8];
                        counter++;
                    }
                }
                else if(what=="bge")
                {
                    if((cmp[1]==1 || cmp[2]==1) && cmp[0]==0)
                    {
                        counter++;
                        r[reg_id("pc")] = addr;
                        num_clkcycl += latency[9];
                    }
                    else
                    {
                        num_clkcycl += latency[9];
                        counter++;
                    }
                }
                else if(what=="bgt")
                {
                    if((cmp[1]==0 && cmp[0]==0) && cmp[2]==1)
                    {
                        counter++;
                        r[reg_id("pc")] = addr;
                        num_clkcycl += latency[9];
                    }
                    else
                    {
                        num_clkcycl += latency[9];
                        counter++;
                    }
                }
                else if(what=="blt")
                {
                    if((cmp[1]==0 && cmp[2]==0) && cmp[0]==1)
                    {
                        counter++;
                        r[reg_id("pc")] = addr;
                        num_clkcycl += latency[9];
                    }
                    else
                    {
                        num_clkcycl += latency[9];
                        counter++;
                    }
                }
                else if(what=="beq")
                {
                    if((cmp[0]==0 && cmp[2]==0) && cmp[1]==1)
                    {
                        counter++;
                        r[reg_id("pc")] = addr;
                        num_clkcycl += latency[9];
                    }
                    else
                    {
                        num_clkcycl += latency[9];
                        counter++;
                    }
                }
                else if(what=="ble")
                {
                    if((cmp[0]==1 || cmp[1]==1) && cmp[2]==0)
                    {
                        counter++;
                        r[reg_id("pc")] = addr;
                        num_clkcycl += latency[10];
                    }
                    else
                    {
                        num_clkcycl += latency[10];
                        counter++;
                    }
                }
                else if(what=="bl")
                {
                    counter++;
                    r[reg_id("pc")] = addr;
                    num_clkcycl += latency[7];
                }
            }

            addr++;
        }
        disp_reg();
}


void compare_exec()
{
    num_clkcycl += latency[11];

    int sec,chm;

    sec=IDnEXE.second_val;

    if(IDnEXE.third_r!=-1)
        chm=IDnEXE.third_val;
    else
        chm=IDnEXE.offset;

    if(sec>chm)
    {
        cmp[0] = 0;
        cmp[1] = 0;
        cmp[2] = 1;
    }
    else if(sec<chm)
    {
        cmp[0] = 1;
        cmp[1] = 0;
        cmp[2] = 0;
    }
    else
    {
        cmp[0] = 0;
        cmp[1] = 1;
        cmp[2] = 0;
    }
    //disp_reg();
}


void ldr_exec(string what)
{
    int reg1;

    if(what=="ldr")
    {
        reg1=EXEnMEM.wb_register;
        cout<<"Memory "<<EXEnMEM.result<<" : "<<memory[EXEnMEM.result]<<endl;
        MEMnWB.result = memory[EXEnMEM.result];
        num_clkcycl += latency[4];
    }
    else if(what=="str")
    {
        reg1=EXEnMEM.third_r;
        cout<<"Memory "<<EXEnMEM.result<<" : "<<memory[EXEnMEM.result]<<endl;
        memory[EXEnMEM.result] = EXEnMEM.third_val;
        cout<<"Memory "<<EXEnMEM.result<<" : "<<memory[EXEnMEM.result]<<endl;
        num_clkcycl += latency[5];
        MEMnWB.result = r[reg1];
    }

    //disp_reg();
}
