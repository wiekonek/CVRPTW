#include <iostream>
#include "instance.h"
#include "text.h"

using std::cout;
using std::cin;

int main(int argc, char **argv) {
  
    cout<<"-= CVRPTW =-\n";

    if(argc < 3)
      return 0;
    
    Instance *test = new Instance();
    Text *file_name = new Text(argv[1]);

    test->import_data(argv[2], file_name->to_int());
    test->show();
    
    delete test;
    delete file_name;
    cout<<"-= KONIEC  =-\n";
    return 0;
}
