#ifndef BUYCOMMAND_HPP_INCLUDED
#define BUYCOMMAND_HPP_INCLUDED
#include "Command.hpp"
class BuyCommand:public Command
{
    char*name;
    char*date;
    int row;
    int seat;
    void parseInput();
public:
    void execute(Archive&database);
    BuyCommand(char*input,int index);
    ~BuyCommand();
};


#endif
