#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>



using std::vector;

class Instance
{
private:
  int K, Q, amount;
  
  class Order
  {
  private:
    int i, x, y, q, e, l, d;
  public:
    Order(vector<int> ord_vec);
    int get_i();
    int get_x();
    int get_y();
    int get_q();
    int get_e();
    int get_l();
    int get_d();
  };
  
  vector<Order> orders;
public:
  bool import_data(char* file_name, int _amount); //import data from file 
  int nearest(int customer_number); //return nearest customer number
  void show(); //show data in object
};

#endif // INSTANCE_H
