#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "instance.h"
#include "text.h"

#define MAX_TIME 180000 //3 min

using std::cout;
using std::cin;

int main ( int argc, char **argv ) {
    pid_t pID;
    int status = -1;
    Text *amount = new Text ( argv[1] );
    Instance *test = new Instance ( argv[2], amount->to_int() );
    vector<int> temp;

    cout<<"-=  CVRPTW  =-\n";

    if ( argc < 3 ) {
        \
        cout<<"Arguments fault!!!\n1 arg - amount\n2+ arg - file name\n";
        return 0;
        }

    pID = fork();
    if ( !pID )
        test->solve();
    else {
        while ( std::clock() <= MAX_TIME ) {
            if ( !wait ( &status ) )
                break;
            };

        if ( !status )
            cout<<"Success!\n";
        else {
            cout<<"Time's up! :c\n";
            kill ( pID, 9 );
            }
        delete test;
        delete amount;
        cout<<"-= END =-\n";
        }

    return 0;
    }
