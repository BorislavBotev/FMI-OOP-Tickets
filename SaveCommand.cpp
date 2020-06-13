#include "SaveCommand.hpp"

SaveCommand::SaveCommand(char*input,int index):Command(input,index)
{
    file=NULL;
}

SaveCommand::~SaveCommand()
{
    delete[]file;
}
void SaveCommand::parseInput()
{
    char*arr=getInput();
    int index=getIndex();
    if(arr[index]=='\0')
    {
        return;
    }
    if(arr[index++]!=' ')
    {
        throw MyException("Invalid syntax");
    }
    file=extractStringWithNoSPaces(arr,index);
    if(!file || arr[index]!='\0')
    {
        throw MyException("Invalid filename");
    }
}
void SaveCommand::execute(Archive&database)
{
    try
    {
        parseInput();
    }
    catch(MyException e)
    {
        std::cout<<e.what()<<std::endl;
        return;
    }
    database.save(file);
}

