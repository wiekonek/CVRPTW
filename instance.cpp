#include "instance.h"
#include "functions.h"
#include <iostream>
#include <fstream>

using std::fstream;
using std::cout;



bool Instance::import_data(char* file_name, int amount)
{
  int what = 1, index = 0;
  bool plus = false;
  char c, buf[10];
  fstream fp (file_name);
  vector <int> tmp(6,0);
  K = amount;

  if(!fp.good())
    return false;

  while(fp.good())
  {

    c = fp.get();

    if(what == 5 && c != ' ')
    {
      fp.seekg(-1, std::ios_base::cur);
      fp.getline(buf, 10, ' ');
      if(!amount)
	K = convert(buf);
      plus = true;
    }

    if(what == 6 && c != ' ')
    {
      fp.seekg(-1, std::ios_base::cur);
      fp.getline(buf, 10, '\r');
      Q = convert(buf);
      plus = true;
    }


    if(what > 10 && what <= K+10 && c != ' ')
    {
      fp.seekg(-1, std::ios_base::cur);
      fp.getline(buf, 10, ' ');

      if(index++ > 1)
	tmp[index-3] = convert(buf);

      if(index == 8)
      {
	orders.push_back(tmp);

	index = 0;
	what++;
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
    cout<<i<<":\t";
    for(int j = 0; j < orders[i].size(); j++)
      cout<<orders[i][j]<<"\t";
    cout<<"\n";
  }
}

