#ifndef topfivefun_h_
#define topfivefun_h_

#include<iostream>
using namespace std;

class pipeline_reg
{
public:
    int wb_register,second_r,third_r,result,offset;
    int second_val,third_val;
    string label,instruc_type; //for branch type of instruction to store the label
};

extern pipeline_reg IDnEXE,EXEnMEM,MEMnWB;

void add_decode();
void branch_decode();
void cmp_decode();
void ldr_decode(string);
void mv_decode();
void check_forwarding();
void display_pipes();
bool check_branchStall();
void reset_pipe();
void swi_exit();

void IF();
void ID();
void EXE();
void MEM();
void WB();

#endif // topfivefun_h_
