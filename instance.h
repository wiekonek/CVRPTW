#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>



using std::vector;

class Instance
{
private:
  int K, Q;
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
  
  int smallest_order();					//return size of the smallest remainning order	
  
public:
  Instance(char* file_name, int K); 			//import data from file
  ~Instance();						//delete Instance
  int nearest(int start_cust); 			//return nearest customer number
  float  itinerary(int customer_number);		//found one itinerary, vehicle return to base when loading isn't enough to deliver anymore order, start from customer_number
  void show(); 						//show data in object
};

#endif // INSTANCE_H
