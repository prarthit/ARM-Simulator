#ifndef executes_h_
#define executes_h_

void add_exec(string);				//to execute the add,sub,mul instructions parameters are instructions
void bl_exec(string);				//to execute the bl,b,bne,bge instructions parameters are instructions
void mov_exec();					//to execute the mov instruction
void ldr_exec(string);				//to execute the ldr,str instructions parameters are instructions
void compare_exec();				//to execute the compare instruction

#endif
