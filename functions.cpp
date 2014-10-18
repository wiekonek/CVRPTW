#include "functions.h"

int convr(char cchar[], int *depth, int which)
{
  int result;
  (cchar[which + 1] != '\0') ? result = (convr(cchar, depth, which+1) + ((cchar[which] - '0') * (*depth) )) : result = (cchar[which] - '0');
  (*depth) *=  10;
  return result;
}

int convert(char cchar[])
{
  int depth = 1;
  return convr(cchar, &depth, 0);
}