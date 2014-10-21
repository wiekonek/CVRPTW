#include "instance.h"
#include "text.h"
#include <iostream>
#include <fstream>

using std::fstream;
using std::cout;


// Instance

bool Instance::import_data(char* file_name, int _amount)
{
  int what = 1, index = 0, customer_number = 1;
  bool plus = false;
  char c;
  fstream fp (file_name);
  vector <int> tmp(7,0);
  amount = _amount;
  Order *order;
  
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
      cout<<buff->get_ptr()<<std::endl;
      Q = buff->to_int();
      plus = true;
    }


    if(what > 10 && what <= amount+10 && c != ' ')
    {
      fp.seekg(-1, std::ios_base::cur);
      fp.getline(buff->get_ptr(), 10, ' ');
      
      if(index++ > 0)
	  tmp[index - 2] = buff->to_int();
 
      if(index == 8)
      {
	cout<<tmp.size()<<": ";
	for(int i = 0; i <= tmp.size() - 1; i++)
	  cout<<tmp[i]<<"  ";
	cout<<"\n";
	order = new Order(tmp);
	orders.push_back(*order);
	delete order;
	
	index = 0;
	plus = true;
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

int Instance::nearest(int customer_number)
{
  int ncn; //x = orders[customer_number][1]; y = orders[customer_number][2];
  
  for(int i = 1; i <= amount; i++) {
    
  }
  
  
  return ncn;
}


void Instance::show()
{
  cout<<"Instance: \nK = "<< K <<"\nQ = "<< Q << "\n";
  cout<<"CUS NUM\tX\tY\tDEMAND\tREADY T\tDUE DATE\tSER DURAT\n";
  for(int i = 0; i < orders.size(); i++)
    cout<<orders[i].get_i()<<"\t"<<orders[i].get_x()<<"\t"<<orders[i].get_y()<<"\t"<<orders[i].get_q()<<"\t"<<orders[i].get_e()<<"\t"<<orders[i].get_l()<<"\t"<<orders[i].get_d()<<"\n";
}






//           ORDER

Instance::Order::Order(vector< int > vec): i(vec[0]), x(vec[1]), y(vec[2]), q(vec[3]), e(vec[4]), l(vec[5]), d(vec[6]) {
}

int Instance::Order::get_i() {
    return i;
}

int Instance::Order::get_x() {
    return x;
}

int Instance::Order::get_y() {
    return y;
}

int Instance::Order::get_q() {
    return q;
}

int Instance::Order::get_e() {
    return e;
}

int Instance::Order::get_l() {
    return l;
}

int Instance::Order::get_d() {
    return d;
}



