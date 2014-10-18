#include <iostream>
#include "instance.h"
#include "functions.h"

using std::cout;
using std::cin;

int main(int argc, char **argv) {
    cout<<"-= CVRPTW =-\n";
    Instance test;
    test.import_data(argv[2], convert(argv[1]));
    
    test.show();
    
    cout<<"-= KONIEC  =-\n";
    return 0;
}
