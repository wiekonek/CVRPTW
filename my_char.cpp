#include "instance.h"
#include "functions.h"
#include <iostream>
#include <fstream>

using std::fstream;
using std::cout;

my_char::my_char(char *_temp)
{
    temp = _temp;
}

int my_char::convr(char cchar[], int *depth, int which)
{
    int result;
    (cchar[which + 1] != '\0') ? result = (convr(cchar, depth, which+1) + ((cchar[which] - '0') * (*depth) )) : result = (cchar[which] - '0');
    (*depth) *=  10;
    return result;
}

int my_char::convert(char cchar[])
{
    int depth = 1;
    return convr(cchar, &depth, 0);
}
