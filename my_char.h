#ifndef MY_CHAR
#define MY_CHAR

#include <vector>



using std::vector;

class my_char
{
private:
    char *temp;
public:
    my_char(char *_temp);
    int convr(char cchar[], int *depth, int which);
    int convert(char cchar[]);

};

#endif // INSTANCE
