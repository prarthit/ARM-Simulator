
#include<iostream>
#include<sstream>
using namespace std;

int main()
{
    int instruc_size,i,j;
cin>>instruc_size;
stringstream ss;
string h = "hello";
ss.str(h);
ss.seekp(0);
ss<<"prarthit"<<ss.str();
cout<<ss.str()<<endl;
for(i=1;i<instruc_size+4;i++)
                {
                    j = i;
                    for(int count3 = 1;count3<instruc_size;count3++)
                    {
                        if(j<1)
                        {
                            count3 = instruc_size;
                        }
                        else if(j>5)
                            cout<<"  ";
                        else
                        {
                            cout<<j<<" ";
                        }
                        j--;
                    }
                    cout<<endl;
                }
}
