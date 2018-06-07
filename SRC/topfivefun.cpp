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

void IF()
{
    ss.clear();

    if(check_branchStall())
        return;

    instruc_size++;

    if((instructions[(r[reg_id("pc")])] == "") || check_label(instructions[(r[15])]))
        r[15]++;

    total_instruc++;
    IFfull_instr = instructions[(r[reg_id("pc")])];
    ss.str(instructions[(r[reg_id("pc")])]);
    r[15]++;

}

void ID()
{
    string instruc;
    ss>>instruc;

    IDnEXE.instruc_type = instruc;
    IDfull_instr = IFfull_instr;
    IFfull_instr = "";

    if(instruc=="add")
        add_decode();

    else if(instruc=="sub")
        add_decode();

    else if(instruc=="mul")
        add_decode();

    else if(instruc=="mov")
        mv_decode();

    else if(instruc=="cmp")
        cmp_decode();

    else if(instruc=="ldr")
        ldr_decode(instruc);

    else if(instruc=="str")
        ldr_decode(instruc);

    else if(instruc=="b")
        branch_decode();

    else if(instruc=="bl")
        branch_decode();

    else if(instruc=="ble")
        branch_decode();

    else if(instruc=="bge")
        branch_decode();

    else if(instruc=="bne")
        branch_decode();

    else if(instruc=="bgt")
        branch_decode();

    else if(instruc=="blt")
        branch_decode();

    else if(instruc=="beq")
        branch_decode();

    else if(instruc=="stall")
        reset_pipe();

    else if(instruc=="swi")
        swi_exit();

    check_forwarding();
}

void EXE()
{
    checkExe(IDnEXE.instruc_type);

    EXEfull_instr = IDfull_instr;
    IDfull_instr = "";

    EXEnMEM.label = IDnEXE.label;
    EXEnMEM.result = IDnEXE.result;
    EXEnMEM.second_r = IDnEXE.second_r;
    EXEnMEM.third_r = IDnEXE.third_r;
    EXEnMEM.second_val = IDnEXE.second_val;
    EXEnMEM.third_val = IDnEXE.third_val;
    EXEnMEM.wb_register = IDnEXE.wb_register;
    EXEnMEM.offset = IDnEXE.offset;
    EXEnMEM.instruc_type = IDnEXE.instruc_type;
}

void MEM()
{
    MEMfull_instr = EXEfull_instr;
    EXEfull_instr = "";

    if(EXEnMEM.instruc_type == "ldr" || EXEnMEM.instruc_type == "str")
    {
        ldr_exec(EXEnMEM.instruc_type);
        disp_reg();
    }
    else{MEMnWB.result = EXEnMEM.result;}

    MEMnWB.label = EXEnMEM.label;
    MEMnWB.second_r = EXEnMEM.second_r;
    MEMnWB.third_r = EXEnMEM.third_r;
    MEMnWB.wb_register = EXEnMEM.wb_register;
    MEMnWB.second_val = EXEnMEM.second_val;
    MEMnWB.third_val = EXEnMEM.third_val;
    MEMnWB.offset = EXEnMEM.offset;
    MEMnWB.instruc_type = EXEnMEM.instruc_type;
}

void WB()
{
    WBfull_instr = MEMfull_instr;
    MEMfull_instr = "";

    if(MEMnWB.instruc_type == "add" || MEMnWB.instruc_type == "sub" || MEMnWB.instruc_type == "mul" || MEMnWB.instruc_type == "mov" || MEMnWB.instruc_type == "ldr")
    {
        r[MEMnWB.wb_register] = MEMnWB.result;
        disp_reg();
    }
    else if(MEMnWB.instruc_type == "swi")
    {
        cout<<"Total number of clock cycles : "<<num_clkcycl<<endl;
        cout<<"Total number of instructions : "<<total_instruc<<endl;
        cout<<"Average instructions per cycle : "<<(float)total_instruc/(float)clockcycle<<endl;
        cout<<"Average cycles per instruction : "<<(float)clockcycle/(float)total_instruc<<endl;
        exit(0);
    }
}











