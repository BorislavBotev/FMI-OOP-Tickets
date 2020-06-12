#ifndef CLOSEEXCEPTION_HPP_INCLUDED
#define CLOSEEXCEPTION_HPP_INCLUDED
class CloseException:public std::exception
{
    char message[200];
public:
    CloseException(const char*text)
    {
        strcpy(message,text);
    }
    CloseException(){}
    const char * what () const throw ()
    {
        return message;
    }
};


#endif // CLOSEEXCEPTION_HPP_INCLUDED
