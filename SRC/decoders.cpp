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

void add_decode()
{
    string full_line,comp_1,comp_2,comp_3,comps;
    int reg1,reg2,chm;

    char *temp;

    getline(ss,full_line,'\n');

    temp = strtok (&full_line[0],",");
    chrtostr(&comp_1,temp);
    removespace(&comp_1);

    temp = strtok (NULL,",");
    chrtostr(&comp_2,temp);
    removespace(&comp_2);

    temp = strtok (NULL,"");
    chrtostr(&comp_3,temp);
    removespace(&comp_3);

    reg1=reg_id(comp_1);
    reg2=reg_id(comp_2);

    if (check_reg(comp_3))
    {
        IDnEXE.third_r = reg_id(comp_3);
        IDnEXE.third_val = r[IDnEXE.third_r];
        IDnEXE.offset = 0;
    }
    else
    {
        comps = &comp_3[1];
        stringstream tonum(comps);
        tonum>>chm;

        IDnEXE.third_r = -1;
        IDnEXE.third_val = -1;
        IDnEXE.offset = chm;
    }

    IDnEXE.wb_register = reg1;
    IDnEXE.second_r = reg2;
    IDnEXE.label = "";
    IDnEXE.result = 0;

    IDnEXE.second_val = r[reg2];
}

void branch_decode()
{
    string full_line,label,h;          //eg b label

    char *temp;

    getline(ss,full_line,'\n');

    temp = strtok (&full_line[0],"");
    chrtostr(&label,temp);
    removespace(&label);

    IDnEXE.label = label;
    IDnEXE.wb_register = -1;
    IDnEXE.second_r = -1;
    IDnEXE.third_r = -1;
    IDnEXE.second_val = -1;
    IDnEXE.third_val = -1;
    IDnEXE.result = 0;
}

void mv_decode()
{
    string full_line,comp_1,comp_2,comps;
    int reg1,reg2,cons;

    char *temp;

    getline(ss,full_line,'\n');

    temp = strtok (&full_line[0],",");
    chrtostr(&comp_1,temp);
    removespace(&comp_1);

    temp = strtok (NULL,",");
    chrtostr(&comp_2,temp);
    removespace(&comp_2);

    reg1=reg_id(comp_1);

    if (check_reg(comp_2))
    {
        reg2=reg_id(comp_2);
        IDnEXE.third_r = reg2;
        IDnEXE.third_val = r[reg2];
    }
    else
    {
        comps = &comp_2[1];
        stringstream tonum(comps);
        tonum>>cons;

        IDnEXE.offset = cons;
        IDnEXE.third_r = -1;
        IDnEXE.third_val = -1;
    }

    IDnEXE.wb_register = reg1;
    IDnEXE.label = "";
    IDnEXE.result = 0;
    IDnEXE.second_r = -1;
    IDnEXE.second_val = -1;
}

void cmp_decode()
{
    string full_line,comp_1,comp_2,comps;
    int reg1,reg2,chm;
    char *temp;

    getline(ss,full_line,'\n');

    temp = strtok (&full_line[0],",");
    chrtostr(&comp_1,temp);
    removespace(&comp_1);

    temp = strtok (NULL,",");
    chrtostr(&comp_2,temp);
    removespace(&comp_2);

    reg1=reg_id(comp_1);

    if (check_reg(comp_2))
    {
        reg2=reg_id(comp_2);
        IDnEXE.third_r = reg2;
        IDnEXE.third_val = r[reg2];
        IDnEXE.offset = 0;
    }
    else
    {
        comps = &comp_2[1];
        stringstream tonum(comps);
        tonum>>chm;
        IDnEXE.offset = chm;
        IDnEXE.third_r = -1;
        IDnEXE.third_val = -1;
    }

    IDnEXE.second_r = reg1;
    IDnEXE.second_val = r[reg1];
    IDnEXE.label = "";
    IDnEXE.wb_register = -1;
    IDnEXE.result = 0;
}

void ldr_decode(string what)
{
    string full_line,s,tmp2,reg_1,reg_2;
    int reg1,reg2,itmp2;

    char *temp;

    getline(ss,full_line,'\n');

    temp = strtok (&full_line[0],",");
    chrtostr(&reg_1,temp);
    removespace(&reg_1);

    temp = strtok (NULL,"");
    chrtostr(&s,temp);
    removespace(&s);

        if(s.length()>4)
            {
                temp = strtok (&s[1],",]");
                chrtostr(&reg_2,temp);
                removespace(&reg_2);

                temp = strtok (NULL,"]");
                chrtostr(&tmp2,temp);
                removespace(&tmp2);
            }
           else
           {
                reg_2=s.substr(1,2);
                tmp2="";
           }

            reg1=reg_id(reg_1);
            reg2=reg_id(reg_2);

            if(check_reg(reg_2) && check_integer(tmp2))
            {
                tmp2=tmp2.substr(1,tmp2.length()-1);
                stringstream ss1(tmp2);
                ss1>>itmp2;
            }

            else if(check_reg(reg_2) && tmp2=="")
            {
                itmp2 = 0;
            }

    if(what=="ldr")
    {
        IDnEXE.wb_register = reg1;
        IDnEXE.third_r = -1;
        IDnEXE.third_val = -1;
    }
    else
    {
        IDnEXE.wb_register = -1;
        IDnEXE.third_r = reg1;
        IDnEXE.third_val = r[reg1];
    }

    IDnEXE.second_r = reg2;
    IDnEXE.second_val = r[reg2];
    IDnEXE.offset = itmp2/4;
    IDnEXE.label = "";
    IDnEXE.result = 0;
}

void check_forwarding()
{
    if(IDnEXE.second_r == EXEnMEM.wb_register)
    {
        if(EXEnMEM.instruc_type=="ldr")
        {
            r[15]--;
            IDnEXE.instruc_type="stall ";
            IDfull_instr = "stall ";
            reset_pipe();
            total_instruc--;
        }
        else
        {
            IDnEXE.second_val = EXEnMEM.result;
        }
    }

    if(IDnEXE.second_r == MEMnWB.wb_register)
    {
        IDnEXE.second_val = MEMnWB.result;
    }

    if(IDnEXE.third_r == EXEnMEM.wb_register)
    {
        if(EXEnMEM.instruc_type=="ldr")
        {
            r[15]--;
            IDnEXE.instruc_type="stall ";
            IDfull_instr = "stall ";
            reset_pipe();
            total_instruc--;
        }
        else
        {
            IDnEXE.third_val = EXEnMEM.result;
        }
    }

    if(IDnEXE.third_r == MEMnWB.wb_register)
    {
        IDnEXE.third_val = MEMnWB.result;
    }
}

bool check_branchStall()
{
    if(IDnEXE.instruc_type == "b" || IDnEXE.instruc_type == "bl" || IDnEXE.instruc_type == "ble" || IDnEXE.instruc_type == "bne" || IDnEXE.instruc_type == "beq" || IDnEXE.instruc_type == "bgt" || IDnEXE.instruc_type == "blt" || IDnEXE.instruc_type == "bge" || IDnEXE.instruc_type == "cmp")
    {
        IFfull_instr = "stall ";
        ss.str("stall ");
        instruc_size++;
        return true;
    }
    else if(EXEnMEM.instruc_type == "b" || EXEnMEM.instruc_type == "bl" || EXEnMEM.instruc_type == "ble" || EXEnMEM.instruc_type == "bne" || EXEnMEM.instruc_type == "beq" || EXEnMEM.instruc_type == "bgt" || EXEnMEM.instruc_type == "blt" || EXEnMEM.instruc_type == "bge" || EXEnMEM.instruc_type == "cmp")
    {
        IFfull_instr = "stall ";
        ss.str("stall ");
        instruc_size++;
        return true;
    }
    else if(IDnEXE.wb_register==15 || EXEnMEM.wb_register==15 || MEMnWB.wb_register==15)
    {
        IFfull_instr = "stall ";
        ss.str("stall ");
        instruc_size++;
        return true;
    }
    else
        return false;
}

void reset_pipe()
{
    IDnEXE.label = "";
    IDnEXE.result = -1;
    IDnEXE.second_r = -1;
    IDnEXE.third_r = -1;
    IDnEXE.second_val = -1;
    IDnEXE.third_val = -1;
    IDnEXE.wb_register = -1;
    IDnEXE.offset = -1;
    IDnEXE.instruc_type = "stall ";
}

void swi_exit()
{
    if(r[15]<=instructions.size()-1)
        instruc_size--;
    IDnEXE.label = "";
    IDnEXE.result = -1;
    IDnEXE.second_r = -1;
    IDnEXE.third_r = -1;
    IDnEXE.second_val = -1;
    IDnEXE.third_val = -1;
    IDnEXE.wb_register = -1;
    IDnEXE.offset = -1;
    IDnEXE.instruc_type = "swi";
}

void display_pipes()
{
    clockcycle++;
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"Clock cycle : "<<clockcycle<<endl<<endl;
    cout<<"IF  : "<<IFfull_instr<<endl;
    cout<<"ID  : "<<IDfull_instr<<endl;
    cout<<"EXE : "<<EXEfull_instr<<endl;
    cout<<"MEM : "<<MEMfull_instr<<endl;
    cout<<"WB  : "<<WBfull_instr<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;

}
