#include "text.h"


Text::Text(){
  temp = new char();
}

Text::Text(char * tmp): temp(tmp){
}


char* Text::get_ptr()
{
    return temp;
}

int Text::convr(char cchar[], int *depth, int which)
{
    int result;
    (cchar[which + 1] != '\0') ? result = (convr(cchar, depth, which+1) + ((cchar[which] - '0') * (*depth) )) : result = (cchar[which] - '0');
    (*depth) *=  10;
    return result;
}

int Text::to_int()
{
    int depth = 1;
    return convr(temp, &depth, 0);
}
