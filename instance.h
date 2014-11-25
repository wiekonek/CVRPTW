#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>



using std::vector;

class Instance
{
private:
  std::string file_name;
  int K, Q;
  double time;
  vector<bool> served;
  
  class Order
  {
  private:
    int i, x, y, q, e, l, d;
    
  public: 
    Order(vector<int>);
    int get_customer_number();
    int get_x();
    int get_y();
    int get_demand();
    int get_ready_time();
    int get_due_date();
    int get_service_duration();
    
    double distance_to(int, vector<Order*>);  		//return distance to next_customer
  };
  
  vector<Order*> orders; 				//list of orders
  
  bool is_ok();						//return true if instance can be solved 
  int nearest(int start_cust, int vehicle_capacity);	//return nearest customer number
  bool all_served();					//return true if all customers are served
  double  itinerary(vector<int> &route);			//found one itinerary
  
public:
  Instance(char* file_name, int K); 			//import data from file
  ~Instance();						//delete Instance
  
  void show(); 						//show data
  void solve();						//solve problem, save output data to file OUTPUT_*.txt
};

#endif // INSTANCE_H
