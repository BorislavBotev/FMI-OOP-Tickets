#ifndef UNBOOKCOMMAND_HPP_INCLUDED
#define UNBOOKCOMMAND_HPP_INCLUDED
#include "Command.hpp"
class UnbookCommand:public Command
{
    char*name;
    char*date;
    int row;
    int seat;
    void parseInput();
public:
    void execute(Archive&database);
    UnbookCommand(char*input,int index);
    ~UnbookCommand();
};


#endif // UNBOOKCOMMAND_HPP_INCLUDED
