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

void checkSyn(string instruc)
{
    if(instruc != "")
    {
        if(instruc=="add")
            add_c(instruc);

        else if(instruc=="sub")
            add_c(instruc);

        else if(instruc=="mul")
            add_c(instruc);

        else if(instruc=="mov")
            mov_c(instruc);

        else if(instruc=="ldr")
            mov_c(instruc);

        else if(instruc=="str")
            mov_c(instruc);

        else if(instruc=="b")
            b_c();

        else if(instruc=="bl")
            b_c();

        else if(instruc=="ble")
            b_c();

        else if(instruc=="bge")
            b_c();

        else if(instruc=="bne")
            b_c();

        else if(instruc=="bgt")
            b_c();

        else if(instruc=="blt")
            b_c();

        else if(instruc=="beq")
            b_c();

        else if(instruc=="cmp")
            mov_c("mov");

        else if(check_label(instruc))
        {}

        else
            {cout<<"Wrong instruction(use ldr,add,sub,mov etc.)"<<endl;  error_c++;}
    }
}


void checkExe(string instruc)
{
    if(instruc=="add")
        add_exec(instruc);

    else if(instruc=="sub")
        add_exec(instruc);

    else if(instruc=="mul")
        add_exec(instruc);

    else if(instruc=="mov")
        add_exec(instruc);

    else if(instruc=="cmp")
        compare_exec();

    else if(instruc=="ldr")
        add_exec(instruc);

    else if(instruc=="str")
        add_exec(instruc);

    else if(instruc=="b")
        bl_exec(instruc);

    else if(instruc=="bl")
        bl_exec(instruc);

    else if(instruc=="ble")
        bl_exec(instruc);

    else if(instruc=="bge")
        bl_exec(instruc);

    else if(instruc=="bne")
        bl_exec(instruc);

    else if(instruc=="bgt")
        bl_exec(instruc);

    else if(instruc=="blt")
        bl_exec(instruc);

    else if(instruc=="beq")
        bl_exec(instruc);

    else if(instruc=="swi")
        {}
    else{}
}

bool check_reg(string reg)
{
    if(reg != "")
    {
        for(int i=0;i<16;i++)
        {
            if(reg==reg_names[i] || reg=="pc" || reg=="lr")
            return true;
        }

        return false;
    }

    else
        return false;
}


bool check_integer(string s)
{
    if(s != "")
    {
        int num_digits=1;
        int single_num;

        if(s[0]=='#')
        {
            while(num_digits < s.length())
            {
                single_num=s[num_digits];

                if ((single_num <=57 && single_num >=48))
                    num_digits++;
                else
                    return false;
            }

            return true;
        }

        else
            return false;
    }

    else
        return false;
}

bool check_label(string s)
{
    if(s != "")
    {
        int num_chars=0;
        int single_char;

          while(num_chars < s.length())
          {
              single_char=s[num_chars];

              if ((single_char <=90 && single_char >=65) || (single_char <=122 && single_char >=97) || single_char==58)
                num_chars++;

              else
                return false;
          }

        return true;
    }

    else
        return false;
}


bool check_addr(string s)
{
    string tmp,tmp2,reg_from,reg_to;
    int num_chars=1;
    int single_char,itmp2;
    char *temp;

    if(s != "")
    {
        if((s[0]=='[')&&(s[s.length()-1]==']'))
        {
           if(s.length()>4)
            {
                temp = strtok (&s[1],",]");
                chrtostr(&tmp,temp);
                removespace(&tmp);

                temp = strtok (NULL,"]");
                chrtostr(&tmp2,temp);
                removespace(&tmp2);
            }
           else
            {
                tmp=s.substr(1,2);
                tmp2="";
            }

            if(check_reg(tmp) && check_integer(tmp2))
            {
                stringstream ss1;
                ss1.str(tmp2.substr(1,tmp2.length()));
                ss1>>itmp2;

                if((itmp2%4)!= 0)
                    return false;

                if(r[reg_id(tmp)]>1499 || (r[reg_id(tmp)]+(itmp2/4))>1499)
                    return false;
                else
                    return true;
            }

            else if(check_reg(tmp) && tmp2=="")
            {
                if(r[reg_id(tmp)]>(sizeof(memory)/4)-1)
                    return false;
                else
                    return true;
            }
        }

        else
            return false;
    }

    else
        return false;
}

void mov_c(string what)
{
    string full_line,reg_to,reg_from,comma;         //eg mov reg_to,reg_from
    char *temp;

    getline(ss,full_line,'\n');

    temp = strtok (&full_line[0],",");
    chrtostr(&reg_to,temp);
    removespace(&reg_to);

    if(check_reg(reg_to))
    {
            temp = strtok (NULL,"");
            chrtostr(&reg_from,temp);
            removespace(&reg_from);

            if(what=="mov")
            {
                if(check_reg(reg_to)==false && check_integer(reg_from)==false)
                    {cout<<"        Wrong mov inputs #try something like \"mov r0,r1 or mov r2,#5\""<<endl;    error_c++;}
            }

            else if(what=="ldr" || what=="str")
            {
                if(check_addr(reg_from)==false)
                {
                    cout<<"        Wrong "<<what<<" inputs #try something like \""<<what<<" r0,[r1]\""<<endl;
                    error_c++;
                }
            }
    }

    else
        {cout<<"        Wrong inputs #try something using registers"<<endl;    error_c++;}

}


void add_c(string what)
{
    string full_line,reg_in,reg_a,reg_b;          //eg add reg_in,reg_a,reg_b

    char *temp;

    getline(ss,full_line,'\n');

    temp = strtok (&full_line[0],",");
    chrtostr(&reg_in,temp);
    removespace(&reg_in);

    if (check_reg(reg_in))
    {
        temp = strtok (NULL,",");
        chrtostr(&reg_a,temp);
        removespace(&reg_a);

        if (check_reg(reg_a))
        {
            temp = strtok (NULL,"");
            chrtostr(&reg_b,temp);
            removespace(&reg_b);

//            if (check_reg(reg_b))
//                {}
//            else if(check_integer(reg_b) && what!="mul")
//                {}
            if(check_reg(reg_b)==false && (check_integer(reg_b)==false || what=="mul"))
                {cout<<"        Wrong add inputs #try something like \""<<what<<" r0,r1,r2\""<<endl;    error_c++;}
        }

        else
            {cout<<"        Wrong add inputs #try something like \""<<what<<" r0,r1,r2\""<<endl;    error_c++;}
    }

    else
        {cout<<"        Wrong add inputs #try something like \""<<what<<" r0,r1,r2\""<<endl;    error_c++;}
}

void b_c()
{
    string full_line,label,h;          //eg b label

    char *temp;

    int counter = 0;
    int addr = 0;

    getline(ss,full_line,'\n');

    temp = strtok (&full_line[0],"");
    chrtostr(&label,temp);
    removespace(&label);

    if(check_label(label))
    {
        while(addr<instructions.size()-1)
        {
            ss.clear();

            ss.str(instructions[addr]);
            getline(ss,h,'\n');

            temp = strtok (&h[0],":");
            chrtostr(&h,temp);

            if (h==label && counter!=0)
            {
                cout<<"        Error in "<<addr+1<<"th INS : Same name of labels"<<endl;
                counter++;
            }
            else if(h==label && counter==0)
                counter++;

            addr++;
        }

        if(counter==0)
            {cout<<"        Branch \""<<label<<"\" not found"<<endl; error_c++;}
        else if(counter==1)
            {}
        else
            {cout<<"        Branch conflicts *many labels with same name"<<endl;  error_c++;}
    }

    else
        {cout<<"        Wrong branch inputs #try something like \"b/bne/ble/bge/bl xyz\""<<endl;    error_c++;}
}


