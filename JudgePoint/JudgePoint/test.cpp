#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
	int x=1;
	int y=2;
	int a,b; 
	for(int i=0;i<5;i++){
		a=x++;
		b=y++;
		cout<<a<<" "<<b<<endl;
	}
	return 0;
}