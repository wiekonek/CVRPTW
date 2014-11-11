#include <iostream>
#include "instance.h"
#include "text.h"

using std::cout;
using std::cin;

int main(int argc, char **argv) {
    cout<<"-= CVRPTW =-\n\n";

    if(argc < 3)
      return 0;
    
    Text *amount = new Text(argv[1]);
    Instance *test = new Instance(argv[2], amount->to_int());
    
    vector<int> temp;
     
    test->solve();
     
    delete test;
    delete amount;
    
    cout<<"\n-= END =-\n";
    
    
    return 0;
}
