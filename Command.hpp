#ifndef COMMAND_HPP_INCLUDED
#define COMMAND_HPP_INCLUDED
#include "GlobalFunctions.hpp"
#include "Archive.hpp"
#include "MyException.hpp"
class Command
{
    char*input;;
    int readingIndex;
public:
    Command(char*i,int indexx);
    virtual void execute(Archive&database)=0;
    virtual ~Command();
    char* getInput()const;
    int getIndex();

};

#endif // COMMAND_HPP_INCLUDED
