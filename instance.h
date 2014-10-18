#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>



using std::vector;

class Instance
{
private:
  int K, Q;
  vector< vector<int> > orders;
public:
  bool import_data(char* file_name, int amount);
  void show();
};

#endif // INSTANCE_H
