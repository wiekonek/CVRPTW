#include "instance.h"
#include "text.h"
#include <math.h>
#include <iostream>
#include <fstream>

using std::fstream;
using std::cout;


// Instance

Instance::Instance(char* file_name, int amount)
{
  int what = 1, index = 0;
  bool plus = false;
  char c;
  fstream fp (file_name);
  vector <int> tmp(7,0);
  Order *order;
  served.resize(amount);
  
  for(int i = 0; i < served.size() - 1; i++)
    served[i] = false;
  
  Text *buff = new Text();



  while(fp.good())
  {

    c = fp.get();

    if(what == 5 && c != ' ')
    {
      fp.seekg(-1, std::ios_base::cur);
      fp.getline(buff->get_ptr(), 10, ' ');
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


    if(what > 10 && what <= amount+10 && c != ' ')
    {
      fp.seekg(-1, std::ios_base::cur);
      fp.getline(buff->get_ptr(), 10, ' ');
      
      if(index++ > 0)
	  tmp[index - 2] = buff->to_int();
 
      if(index == 8)
      {
// 	cout<<tmp.size()<<": ";
// 	for(int i = 0; i <= tmp.size() - 1; i++)
// 	  cout<<tmp[i]<<"  ";
// 	cout<<"\n";
	
	order = new Order(tmp);
	orders.push_back(order);
	
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
}

Instance::~Instance()
{
  for(int i = 0; i < orders.size()-1; i++)
    delete orders[i];
}

void Instance::show()
{
  cout<<"Instance: \nK = "<< K <<"\nQ = "<< Q << "\n";
  cout<<"CUS NUM\tX\tY\tDEMAND\tREADY T\tDUE DATE\tSER DURAT\n";
  for(int i = 0; i < orders.size(); i++)
    cout<<orders[i]->get_customer_number()<<"\t"<<orders[i]->get_x()<<"\t"<<orders[i]->get_y()<<"\t"<<orders[i]->get_demand()<<"\t"<<orders[i]->get_ready_time()<<"\t"<<orders[i]->get_due_date()<<"\t"<<orders[i]->get_service_duration()<<"\n";
}

int Instance::nearest(int customer_number)
{
  //x = orders[customer_number][1]; y = orders[customer_number][2];
  int next_customer = 1;
  float dist = pow(10.0, 5.0);
  
  for(int i = 1; i <= orders.size()-1; i++)
    if(i != customer_number && orders[customer_number]->distance_to(i, orders) < dist)
    {
      dist = orders[customer_number]->distance_to(i, orders);
      next_customer = i;
    }
  
  return next_customer;
}

int Instance::smallest_order()
{
  int smallest = pow(10, 5);
  
  for(int i = 0; i <= served.size(); i++){
    if(!served[i] && orders[i]->get_demand() < smallest)
      smallest = orders[i]->get_demand();
  }
  
  return smallest;
}


float Instance::itinerary(int start_cust)
{
  float distance = 0;
  int vehicle_capacity = Q, current_cust, next_cust = start_cust; 
 
  while(vehicle_capacity >= smallest_order())
  {
    current_cust = next_cust;
    distance += orders[current_cust]->distance_to(nearest(current_cust), orders);
    served[current_cust] = true;
    next_cust = nearest(current_cust);
  }
  
  
  return distance;
}


//           ORDER

Instance::Order::Order(vector<int> vec): i(vec[0]), x(vec[1]), y(vec[2]), q(vec[3]), e(vec[4]), l(vec[5]), d(vec[6]) {
}

int Instance::Order::get_customer_number() {
    return i;
}

int Instance::Order::get_x() {
    return x;
}

int Instance::Order::get_y() {
    return y;
}

int Instance::Order::get_demand() {
    return q;
}

int Instance::Order::get_ready_time() {
    return e;
}

int Instance::Order::get_due_date() {
    return l;
}

int Instance::Order::get_service_duration() {
    return d;
}

float Instance::Order::distance_to(int next_customer, vector<Order*> list)
{
    return sqrt(pow(x-list[next_customer]->get_x() ,2)+pow(y-list[next_customer]->get_y() ,2));
}




