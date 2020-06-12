#ifndef MYEXCEPTION_HPP_INCLUDED
#define MYEXCEPTION_HPP_INCLUDED
#include "exception"
#include <cstring>
class MyException:public std::exception
{
    char message[200];
public:
    MyException(const char*text)
    {
        strcpy(message,text);
    }
    const char * what () const throw ()
    {
        return message;
    }
};
#endif
