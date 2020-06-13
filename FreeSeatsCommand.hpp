#ifndef FREESEATSCOMMAND_HPP_INCLUDED
#define FREESEATSCOMMAND_HPP_INCLUDED
#include "Command.hpp"
class FreeSeatsCommand:public Command
{
    char*name;
    char*date;
    void parseInput();
public:
    void execute(Archive&database);
    FreeSeatsCommand(char*input,int index);
    ~FreeSeatsCommand();
};


#endif // FREESEATSCOMMAND_HPP_INCLUDED
