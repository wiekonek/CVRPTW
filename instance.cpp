#include "instance.h"

#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>


using std::cout;
using std::vector;

// Instance

Instance::Instance(char* file_name, int amount)
{
  std::ifstream fp;
  std::string text;
  vector <int> tmp(7,0);
  Order *order;
  this->file_name = file_name;
  fp.open(file_name);


  for(int i = 0; i < 4; i++)
    fp >> text;

  fp >> K >> Q;


  for(int i = 0; i < 12; i++)
    fp >> text;
  
  if(!amount)
  {
    while(fp.good())
    {
    for(int j = 0; j < 7; j++)
      fp >> tmp[j];
    order = new Order(tmp);
    orders.push_back(order);
    }
    orders.pop_back();
  }
  else
  {
   for(int i = 0; i <= amount && fp.good(); i++)
    {
    for(int j = 0; j < 7; j++)
      fp >> tmp[j];
    order = new Order(tmp);
    orders.push_back(order);
    }
  }
  
  served.resize(orders.size());
//   ready.resize(orders.size());
  
  for(int i = 0; i < served.size() - 1; i++)
  {
    served[i] = false;
//     ready[i] = false;
  }
  
  fp.close();
}

Instance::~Instance()
{
  for(int i = orders.size()-1; i >= 0; i--)
    delete orders[i];
}

void Instance::show()
{
  cout<<"Instance: \nK = "<< K <<"\nQ = "<< Q << "\n";
  cout<<"CUS NUM\tX\tY\tDEMAND\tREADY T\tDUE DATE\tSER DURAT\n";
  for(int i = 0; i < orders.size(); i++)
    cout<<orders[i]->get_customer_number()<<"\t"<<orders[i]->get_x()<<"\t"<<orders[i]->get_y()<<"\t"<<orders[i]->get_demand()<<"\t"<<orders[i]->get_ready_time()<<"\t"<<orders[i]->get_due_date()<<"\t"<<orders[i]->get_service_duration()<<"\n";
  
  for(int i = 0; i < served.size(); i++)
    cout<< i << " : " << served[i] << "\n";
  
  
}

bool Instance::all_served()
{
  for(int i = 1; i < served.size(); i++)
    if(!served[i])
      return false;
    return true;
}



int Instance::nearest ( int customer_number, int vehicle_capacity ) {
    int next_customer = 0;
    float dist = pow ( 10.0, 5.0 ), current_dist;

    for ( int i = 1; i < orders.size(); i++ ) {
      current_dist = orders[customer_number]->distance_to ( i, orders );
      if ( !served[i]  && i != customer_number  && vehicle_capacity >= orders[i]->get_demand() && current_dist < dist &&
	time + current_dist + orders[i]->get_service_duration() <= orders[i]->get_due_date()) {
	  dist = current_dist;
	  next_customer = i;
      }
    }
    return next_customer;
}


float Instance::itinerary(vector<int> &route)
{
  time = 0;
  float start = 0;
  int vehicle_capacity = Q, current_cust, next_cust = 0, tmp_cust, tmp_service_duration, deadline; 
  vector<bool> tmp = served;
  served[0] = 0;
  route.resize(0);
  route.push_back(0);

  while(true)
  {
    current_cust = next_cust;
    tmp_cust = nearest(current_cust, vehicle_capacity);
    tmp_service_duration = orders[current_cust]->get_service_duration();
    deadline = orders[0]->get_due_date();
    if(time + orders[tmp_cust]->distance_to(0, orders) + tmp_service_duration + orders[next_cust]->get_service_duration()<= deadline)
      next_cust = tmp_cust;
    else if(time + orders[current_cust]->distance_to(0, orders) + tmp_service_duration <= deadline)
      next_cust = 0;
    else
      return -1;
    route.push_back(next_cust);
    served[next_cust] = true; 
    
    time += orders[current_cust]->distance_to(next_cust, orders);
    if(time < orders[next_cust]->get_ready_time())
      time = orders[next_cust]->get_ready_time();
    time += orders[next_cust]->get_service_duration();

    
    vehicle_capacity -= orders[next_cust]->get_demand();
//     cout << "c1: " << current_cust << " c2: " << next_cust << " capa: " << vehicle_capacity << " time: " << time << "\n";
    if(!next_cust)
      return time-start;
  }
  
}


void Instance::solve()
{
  int control = 0;
  double cost = 0, check = 0;
  int iti_num = 0;
  vector<int> route;
  std::ofstream output;
  output.open(("OUTPUT_"+file_name).c_str());
  
  output << "                                                  \n";
  
  while(!all_served())
  {
    check = itinerary(route);
//     cout<<"\n";
    if(check == -1)
    {
      output.seekp(0);
      output << -1;
      return;
    }
      
    cost += check;
    iti_num++;
    for(int i = 0; i < route.size(); i++)
      output << route[i] << " ";
    output << "\n";
    if(control++ >= served.size())
      return;
  }

  output.seekp(0);
  output << iti_num << " " << std::setiosflags(std::ios::fixed) << std::setprecision(5) << cost;
  
  output.close();
  
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




