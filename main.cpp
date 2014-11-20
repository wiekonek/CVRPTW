#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "instance.h"
#include "text.h"

#define MAX_TIME 300000 //5 min

using std::cout;
using std::cin;

int main ( int argc, char **argv ) {


    if ( argc < 3 ) {
      cout<<"\nNalezy podac przynajmniej dwa argumenty:\n\
      pierwszy  - ilosc odbiorcow (0 dla wykorzystania wszystkich odbiorcow);\n\
      nastpene  - nazwy plikow z instancjami problemu.\n\n";
      return 0;
    }
        
    cout<<"\nDo pracy...\n";
        
    pid_t pID;
    int status = -1;
    Text *amount = new Text ( argv[1] );
    std::vector <Instance*> test(argc-2); 
    for(int i = 2; i < argc; i++)
      test[i-2] = new Instance ( argv[i], amount->to_int() );

    pID = fork();
    if ( !pID )
      for(int i = 0; i < test.size(); i++) {
	  test[i]->solve();
	  cout<<"Zakonczono rozwiazywac instancje problemu z pliku: "<<argv[i+2]<<"\n";
	}
    else {
      while ( std::clock() <= MAX_TIME ) {
	if ( !wait ( &status ) )
	break;
      };

      if ( !status )
	cout<<"Koniec pracy! :)\nOpowiedzi znajduja sie w plikach ./OUTPUT_*.txt\n\n";
      else {
	cout<<"Przekroczono czas 5 min! :(\n\n";
	kill ( pID, 9 );
      }
      
      for(int i = 0; i < test.size(); i++)
	delete test[i];
      delete amount;
    }

return 0;
}
