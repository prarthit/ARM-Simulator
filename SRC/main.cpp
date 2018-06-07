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

int r[16];                          //holds the values of registers
string reg_names[16];               //holds the names of registers for comparing r0,r1,r,2,r3...
vector<string> instructions;        //this is a array which will store all instructions line by line at each index
vector<string> labels_vec;			//this will store labels
int cmp[3];
//            cmp[0] = Negative;  for <  0-false 1-true
//            cmp[1] = Zero;	  for =
//            cmp[2] = Carry;     for >
int error_c=0;                      //error counter - counts no of errors

int memory[1500];					//array of memory used in ldr and str instructions
//Memory starts with indexing as 0 then you may consider it as
//int type and add #4 while loading or storing

istringstream ss;

int total_instruc = 0;
int num_clkcycl = 0,clockcycle = 0;
int num_instruc = 1;                //num_instruc is a variable denoting instruction
int instruc_size;


ifstream inn;

int latency[20];

void latency_fun();

pipeline_reg IDnEXE,EXEnMEM,MEMnWB;

string IFfull_instr,IDfull_instr,EXEfull_instr,MEMfull_instr,WBfull_instr;

/* At top level our program first reads the input file stores it into the array and checks if the syntax of instructions is
correct or not. If it has any errors it'll show it but won't execute the program until all errors are removed.
If there are no errors then it'll execute the program and show the values of registers after each instruction.
Our memory has only space of 100 elements so use it carefully.
Use ldr like this ldr rdest,r[address_of_memory]
same goes for str

We have also provided the input file for doing sum from 1 to 5 the final answer will be stored in r4. */

int main()
{
    inn.open("input.txt");

    string instruc_bits,rs,line,rnum;

    rs="r";

    //this loop is for saving names of registers in registers array
    for(int i=0;i<16;i++)
    {
        if(i>9)
        {
            rnum = char(i+38);                  //ascii value conversion and stuff
            reg_names[i] = rs+'1'+rnum;         //for r10 r11 r12 ...
        }
        else
        {
            rnum = char(i+48);
            reg_names[i] = rs+rnum;
        }
        r[i] = 0;
    }


    for(int i=0;i<99;i++)
    {
        memory[i] = 0;                          //initialized memory with 0
    }

    latency_fun();


    if(inn.is_open())
    {
        while(!inn.eof())
        {
            getline(inn,line,'\n');             //storing all the lines in a vector so that can be used by program counter, branch and other instructions
            instructions.push_back(line);
        }

        while(r[15]<instructions.size()-1)      //run a loop for just checking and reading and parsing shows error if any
        {
            ss.clear();                         //clear the stream before using it

            if(instructions[(r[reg_id("pc")])] == "")
            {
                cout<<"--------------------------------------------------"<<endl;
            }
            else
            {
                cout<<"INS "<<num_instruc<<" : "<<instructions[r[15]]<<endl;
                ss.str(instructions[(r[reg_id("pc")])]);
                ss>>instruc_bits;               //take the first word of line and send it for checking
                checkSyn(instruc_bits);
                num_instruc++;
            }

            r[15]++;                            //checked the syntax of a line now go to next line
        }

        if(error_c == 0)
        {
            r[15] = 0;

            instruc_size = 1;   //if errors are 0 run loop once again but now for executing
            int j,temp;

            for(int i=1;i<=instruc_size+4;i++)
            {
                j = i;
                if(j>5)
                    j=5;

                //if(clockcycle>19)
                  //  return 1;

                if(r[15]>=instructions.size()-1)
                    {instruc_size--; r[15]--;}

                for(int count3 = i-j+1 ;count3<=instruc_size;count3++)
                {
                    switch(j)
                    {
                        case 1 : IF();  break;
                        case 2 : ID();  break;
                        case 3 : EXE(); break;
                        case 4 : MEM(); break;
                        case 5 : WB();  break;

                        default : count3 = instruc_size+1;   //doing count3 equal to instruc size +1 to break out of the loop
                                  break;
                    }
                    j--;
                }

                display_pipes();
            }
        }

        else                                    //else print the errors
        {
            cout<<"No of errors : "<<error_c<<endl;
            cout<<"End of Program"<<endl;
        }
    }

    else
    {
        cout<<"Sorry file not opened"<<endl;
    }

    inn.close();

    return 0;
}

//--------------------------------------------------------------------------------------------------------

