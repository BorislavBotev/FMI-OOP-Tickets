#include "SaveCommand.hpp"

SaveCommand::SaveCommand(char*input,int index):Command(input,index) {}

void SaveCommand::parseInput()
{
    if(getInput()[getIndex()]!='\0')
    {
        throw MyException("Invalid command-Did you mean save");
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
    database.save();
}

