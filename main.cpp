#include <iostream>
#include "instance.h"
#include "text.h"

using std::cout;
using std::cin;

int main(int argc, char **argv) {
  
    cout<<"-= CVRPTW =-\n";

    if(argc < 3)
      return 0;
    
    Text *amount = new Text(argv[1]);
    Instance *test = new Instance(argv[2], amount->to_int());
    

    test->show();
    
    int klient = 5;
     cout<< "Najbliżej klienta nr " << klient << " jest klient nr " << test->nearest(klient) << "\n";
    
    delete test;
    delete amount;
    cout<<"-= KONIEC  =-\n";
    return 0;
}
