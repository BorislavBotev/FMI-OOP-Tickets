#ifndef OPENCOMMAND_HPP_INCLUDED
#define OPENCOMMAND_HPP_INCLUDED
#include "Command.hpp"
class OpenCommand:public Command
{
    char*file;
     void parseInput();
public:
    void execute(Archive&database);
    OpenCommand(char*input,int index);
    ~OpenCommand();

};


#endif
