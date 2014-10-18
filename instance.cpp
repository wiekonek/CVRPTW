#include "instance.h"
#include <iostream>
#include <fstream>

using std::fstream;
using std::cout;

int convr(char cchar[], int *depth, int which)
{
  int result;
  (cchar[which + 1] != '\0') ? result = (convr(cchar, depth, which+1) + ((cchar[which] - '0') * (*depth) )) : result = (cchar[which] - '0');
  (*depth) *=  10;
  return result;
}

int convert(char cchar[])
{
  int depth = 1;
  return convr(cchar, &depth, 0);
}

bool Instance::import_data(char* file_name)
{
  int what = 1, index = 0;
  bool plus = false;
  char c, buf[10];
  fstream fp (file_name);
  vector <int> tmp(6,0);
  

  if(!fp)
    return false;
  
  while(fp.good())
  {
    
    c = fp.get(); 
      
    if(what == 5 && c != '\ ')
    {
      fp.seekg(-1, std::ios_base::cur); 
      fp.getline(buf, 10, '\ ');
      K = convert(buf);
      plus = true;
    }

    if(what == 6 && c != '\ ')
    {
      fp.seekg(-1, std::ios_base::cur); 
      fp.getline(buf, 10, '\r');
      Q = convert(buf);
      plus = true;
    }

      
    if(what > 10 && c != '\ ')
    {
      fp.seekg(-1, std::ios_base::cur); 
      fp.getline(buf, 10, '\ ');
     
      cout<<buf<<"\n";
      tmp[index++] = convert(buf);
     

      
      if(index == 6)
      {
	for(int i = 0; i < tmp.size(); i++)
	  cout<<tmp[i]<<" ";
	cout<<"\n";
	
	orders.push_back(tmp);
	index = 0;
      }
    }
    

    
    if(c == '\n' || plus)
    {
      what++;
      plus = false;
    }
  }
  



  fp.close();
  return true;
}

void Instance::show()
{
  cout<<"Instance: \nK = "<< K <<"\nQ = "<< Q << "\n";
  for(int i = 0; i < orders.size(); i++)
  {
    for(int j = 0; j < orders[i].size(); j++)
      cout<<orders[i][j]<<"\t";
    cout<<"\n"; 
  }
}

