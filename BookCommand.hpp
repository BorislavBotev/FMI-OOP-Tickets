#ifndef BOOKCOMMAND_HPP_INCLUDED
#define BOOKCOMMAND_HPP_INCLUDED
#include "Command.hpp"
class BookCommand:public Command
{
    char*name;
    char*date;
    char*note;
    int row;
    int seat;
    void parseInput();
public:
    void execute(Archive&database);
    BookCommand(char*input,int index);
    ~BookCommand();
};

#endif // BOOKCOMMAND_HPP_INCLUDED
