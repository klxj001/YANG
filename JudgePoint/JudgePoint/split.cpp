#include <iostream.h>
#include <string>
#include <vector>
using namespace std;
struct Point 
{ 
	double x, y; 
}; 
vector<string> split(string str,string pattern)
{
    string::size_type pos;
    vector<string> result;
    str+=pattern;
    int size=str.size();

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
           string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}
int main(int argc, char *argv[])
{
	
    /*
char s[] = "12,22";
    const char *d = ",";
    char *p;
    p = strtok(s,d);
  
    while(p)
    {
        printf("%s\n",p);
        p=strtok(NULL,d);
    }*/
   
  vector<string>result=split("12,22",",");
  for(int i=0; i<result.size(); i++)
    {
        cout<<result[i]<<endl;
    }   
    return 0;
}