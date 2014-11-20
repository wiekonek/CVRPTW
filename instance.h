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
  float time;
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
    
    float distance_to(int, vector<Order*>);  		//return distance to next_customer
  };
  
  vector<Order*> orders; 				//list of orders
  
  int nearest(int start_cust, int vehicle_capacity);	//return nearest customer number additionaly check demand size < vehicle_capacity
  bool all_served();					//return true if all customers are served
  float  itinerary(vector<int> &route);			//found one itinerary, vehicle return to base when loading isn't enough to deliver anymore order
  
public:
  Instance(char* file_name, int K); 			//import data from file
  ~Instance();						//delete Instance
  void show(); 						//show data
  void solve();						//solve problem, save data to file OUTPUT_*.txt
};

#endif // INSTANCE_H
