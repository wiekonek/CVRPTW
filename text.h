#ifndef TEXT_H
#define TEXT_H

class Text
{
private:
    char *temp;
    int convr(char cchar[], int *depth, int which);
public:
    Text();
    Text(char *tmp);
    char* get_ptr();
    int to_int();
    
};

#endif // TEXT_H
