#include <iostream>
#include <cstdlib>
using namespace std;

int function(int a[6])
{
	if(a[0]>=a[1] or a[2]==0 or ( a[3]%a[2]!=0  and  a[4]%a[2]!=0 and a[5]%a[2]!=0) )
		return  (a[0]-a[1]);
		else return ((a[1]-a[0]) + a[3]%a[2] + a[4]%a[2]+ a[5]%a[2]);

}

int main(int argc, char **argv)
{
	if(argc<7) 
	{
		cout<<"Incorrect number of parameters! There must be 6 parameters!"<<endl;
		return 0;
	}
	int arg[6];
	for(int i=0; i<6; i++)
	{
		arg[i]=atoi(argv[i+1]);
	}
	cout<<function(arg)<<endl;	
	
	return 0;
}
