#include <iostream>
#include "instance.h"

using std::cout;
using std::cin;

int main(int argc, char **argv) {
    cout<<"-= CVRPTW =-\n";
    Instance test;
    test.import_data(argv[1]);
    
    test.show();
    
    cout<<"-=  END   =-\n";
    return 0;
}
