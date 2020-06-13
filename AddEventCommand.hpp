#ifndef ADDEVENTCOMMAND_HPP_INCLUDED
#define ADDEVENTCOMMAND_HPP_INCLUDED
#include "Command.hpp"
class AddEventCommand:public Command
{
    char*date;
    char*name;
    int hall;
    void parseInput();
public:
    void execute(Archive&database);
    AddEventCommand(char*input,int index);
    ~AddEventCommand();
};


#endif // ADDEVENTCOMMAND_HPP_INCLUDED
