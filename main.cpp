#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "instance.h"
#include "text.h"

#define MAX_TIME 300000000 //5 min

using std::cout;
using std::cin;

int main ( int argc, char **argv ) {


    if ( argc < 3 ) {
      cout<<"\nNalezy podac przynajmniej dwa argumenty:\n\
      pierwszy  - ilosc odbiorcow (0 dla wykorzystania wszystkich odbiorcow);\n\
      nastpene  - nazwy plikow z instancjami problemu.\n\n";
      return 0;
    }
    
    std::fstream tmp_file;
    for(int i = 2; i < argc-2; i++) {
      tmp_file.open(argv[i]);
      if(!tmp_file.good()) {
	cout<<"Niewlasciwe argumenty.\n";
	return 0;
      }
      tmp_file.close();
    }
    
//     cout<<"\nPoprawne argumenty. Rozpoczynam...\n";
        
    pid_t pID;
    time_t start;
    int status = -1;
    Text *amount = new Text ( argv[1] );
    std::vector <Instance*> test(argc-2);
    
    for(int i = 2; i < argc; i++)
      test[i-2] = new Instance ( argv[i], amount->to_int() );

    pID = fork();
    if ( pID ) {
      for(int i = 0; i < test.size(); i++) {
	start = std::clock();
	test[i]->solve();
// 	cout<<"Zakonczono rozwiazywac instancje z pliku: "<<argv[i+2]<<" w czasie: "<<std::clock()-start<<"ms.\n";
      }
    } else {  
      while ( std::clock() <= MAX_TIME );
    }

    if(!pID){
      kill(getppid(), 9);
//       cout<<"Przekroczono czas 5min!\n";
    } else {
      kill(pID, 9);
    }
      
      for(int i = 0; i < test.size(); i++)
	delete test[i];
      delete amount;
//       cout<<"Koniec pracy. Zasoby zwolnione.\n\n";

return 0;
}
