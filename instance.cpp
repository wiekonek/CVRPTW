#include "instance.h"
#include "text.h"
#include <iostream>
#include <fstream>

using std::fstream;
using std::cout;



bool Instance::import_data(char* file_name, int amount)
{
  int what = 1, index = 0;
  bool plus = false;
  char c;
  fstream fp (file_name);
  vector <int> tmp(6,0);
  K = amount;
 
  
  Text *buff = new Text();

  if(!fp.good())
    return false;

  while(fp.good())
  {

    c = fp.get();

    if(what == 5 && c != ' ')
    {
      fp.seekg(-1, std::ios_base::cur);
      fp.getline(buff->get_ptr(), 10, ' ');
      if(!amount)
	K = buff->to_int();
      plus = true;
    }

    if(what == 6 && c != ' ')
    {
      fp.seekg(-1, std::ios_base::cur);
      fp.getline(buff->get_ptr(), 10, '\r');
      Q = buff->to_int();
      plus = true;
    }


    if(what > 10 && what <= K+10 && c != ' ')
    {
      fp.seekg(-1, std::ios_base::cur);
      fp.getline(buff->get_ptr(), 10, ' ');

      if(index++ > 1)
	tmp[index-3] = buff->to_int();

      if(index == 8)
      {
	orders.push_back(tmp);

	index = 0;
	what++;
      }
    }



    if(c == '\n'|| plus)
    {
      what++;
      plus = false;
    }
  }

  delete buff;
  fp.close();
  return true;
}

void Instance::show()
{
  cout<<"Instance: \nK = "<< K <<"\nQ = "<< Q << "\n";
  for(int i = 0; i < orders.size(); i++)
  {
    cout<<i<<":\t";
    for(int j = 0; j < orders[i].size(); j++)
      cout<<orders[i][j]<<"\t";
    cout<<"\n";
  }
}

