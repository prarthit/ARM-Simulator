#ifndef small_h_
#define small_h_

void removespace(string *);         //as the name suggests it removes spaces from a string
void chrtostr(string *,char *);		//convert character array to string
int reg_id(string);					//to get the index of register for eg r13 will return 13
void disp_reg();					//to display the value of registers

#endif
