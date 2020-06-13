#ifndef SAVECOMMAND_HPP_INCLUDED
#define SAVECOMMAND_HPP_INCLUDED
#include "Command.hpp"
class SaveCommand:public Command
{

    void parseInput();
public:
    void execute(Archive&database);
    SaveCommand(char*input,int index);
};

#endif // SAVECOMMAND_HPP_INCLUDED
