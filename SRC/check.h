#ifndef CHECK_H_
#define CHECK_H_

//these are global variables so to use them i have made them extern
extern int memory[1500],error_c,r[16],cmp[3];
extern istringstream ss;
extern string reg_names[16];
extern vector<string> instructions,labels_vec;
extern int latency[20],num_clkcycl,num_instruc,total_instruc,instruc_size,clockcycle;
extern string IFfull_instr,IDfull_instr,EXEfull_instr,MEMfull_instr,WBfull_instr;

void checkSyn(string);              //this is for checking the syntax of command like ldr mov add sub etc. it wont execute them
bool check_reg(string);             //it checks the given string is a register or not like r0,r1,r2,...

void mov_c(string);                 //for checking mov and ldr and str syntax
void add_c(string);                 //for checking add,sub,mul syntax
void b_c();                         //for checking b,bl,bne,bge,ble syntax

bool check_integer(string );		//checks #16 is true or not
bool check_addr(string);			//checks if [r5] is true or not
bool check_label(string);			//checks if abcdef is true or not
void checkExe(string);              //this is same as checkSyn but it will just execute the commands ldr,add,str...

#endif // check_h_
