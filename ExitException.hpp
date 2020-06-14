#ifndef EXITEXCEPTION_HPP_INCLUDED
#define EXITEXCEPTION_HPP_INCLUDED
#include <exception>
#include <cstring>
class ExitException:public std::exception
{
    char message[200];
public:
    ExitException(const char*text)
    {
        strcpy(message,text);
    }
    ExitException(){}
    const char * what () const throw ()
    {
        return message;
    }
};


#endif // EXITEXCEPTION_HPP_INCLUDED
