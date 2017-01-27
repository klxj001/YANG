#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
  char *filePath = "D:\\aaa.txt";
  ifstream file;
  file.open(filePath,ios::in);

  if(!file.is_open())

        return 0;

    
       std::string strLine;
       while(getline(file,strLine))
       {

            if(strLine.empty())
                continue;

            cout<<strLine <<endl;              
       }
       
       

}