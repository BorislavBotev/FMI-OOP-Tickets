#ifndef EXITEXCEPTION_HPP_INCLUDED
#define EXITEXCEPTION_HPP_INCLUDED
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
