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
  
  for(int i = 0; i < served.size() - 1; i++)
    served[i] = false;
  
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

bool Instance::is_ok()
{
  double distance;
  double service, deadline = orders[0]->get_due_date();
  for(int i = 0; i < orders.size(); i++) {
    distance = orders[0]->distance_to(i, orders);
    service = orders[i]->get_service_duration();
    if( 2*distance + service > deadline )
      return false;
    if((double)orders[i]->get_ready_time() + service > deadline)
      return false;
  }
  return true;
}


int Instance::nearest ( int customer_number, int vehicle_capacity ) {
    int next_customer = 0;
    double dist, current_dist, ready_time, time_gap, current_cost, cost = pow ( 10.0, 10.0 );
    double deadline = orders[0]->get_due_date();
    for ( int i = 1; i < orders.size(); i++ ) {
      current_dist = orders[customer_number]->distance_to ( i, orders );
      ready_time = orders[i]->get_ready_time();
      time + current_dist < ready_time ? time_gap = ready_time - (time + current_dist) : time_gap = 0;
      current_cost = current_dist + time_gap;
      
      if ( !served[i]  && i != customer_number  && vehicle_capacity >= orders[i]->get_demand() && current_cost < cost &&
	  time + current_dist <= (double)orders[i]->get_due_date() &&
	  time + current_cost + (double)orders[i]->get_service_duration() + (double)orders[i]->distance_to(0, orders) <= deadline) {
	  cost = current_cost;
	  next_customer = i;
      }
    }
    return next_customer;
}


double Instance::itinerary(vector<int> &route)
{
  int vehicle_capacity = Q, current_cust, next_cust = 0;
  
  time = 0;
  served[0] = 0;
  
  route.resize(0);
  route.push_back(0);
  
  do
  {
    current_cust = next_cust;
    next_cust = nearest(current_cust, vehicle_capacity);
    route.push_back(next_cust);
    
    served[next_cust] = true; 
    time += orders[current_cust]->distance_to(next_cust, orders);
    if(time < orders[next_cust]->get_ready_time())
      time = orders[next_cust]->get_ready_time();
    time += orders[next_cust]->get_service_duration();
    vehicle_capacity -= orders[next_cust]->get_demand();
    
  } while(next_cust);
  
  return time;
}


void Instance::solve()
{
  double cost = 0, check = 0;
  int iti_num = 0;
  vector<int> route;
  std::ofstream output;
  output.open(("OUTPUT_"+file_name).c_str(), std::ios::out | std::ios::trunc);
  
  if(!is_ok()) {
    output << -1 << "\n";
    return;
  }
  
  output << "                                                  \n";
  
  do {
    cost += itinerary(route);
    iti_num++;
    for(int i = 1; i < route.size() - 1; i++)
      output << route[i] << " ";
    output << "\n";
    
  } while(!all_served());
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

double Instance::Order::distance_to(int next_customer, vector<Order*> list)
{
    return sqrt((x-list[next_customer]->get_x())*(x-list[next_customer]->get_x())+(y-list[next_customer]->get_y())*(y-list[next_customer]->get_y()));
}