#include "OpenCommand.hpp"
OpenCommand::OpenCommand(char*input,int index):Command(input,index)
{
    file=NULL;
}

OpenCommand::~OpenCommand()
{
    delete[] file;
}
void OpenCommand::execute(Archive& database)
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
    database.openFile(file);
}
void OpenCommand::parseInput()
{
    const char*input=getInput();
    int index=getIndex();
    if(strlen(input)==0)
    {
        throw MyException("Write files name");
    }
    index++;
    while(input[index]!='\0' && input[index]!=' ')
    {
        index++;
    }
    if(input[index]!='\0')
    {
        throw MyException("There can't be space in the files name");
    }
    createSubString(file,input,getIndex()+1,index-1);
    if(!file)
    {
        throw MyException("Couldn't copy the input");
    }

}

