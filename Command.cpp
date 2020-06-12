#include "Command.hpp"
Command::Command(char*i,int index)
{
    if(i)
    {
        createString(input,i);
    }
    readingIndex=index;
}
Command::~Command()
{
    delete[]input;
}
char* Command::getInput() const
{
    return input;
}
int Command::getIndex()
{
    return readingIndex;
}
