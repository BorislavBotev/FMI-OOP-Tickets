#ifndef BOOKINGSCOMMAND_HPP_INCLUDED
#define BOOKINGSCOMMAND_HPP_INCLUDED
#include "Command.hpp"
class BookingsCommand:public Command
{
    char*name;
    char*date;
    void parseInput();
public:
    void execute(Archive&database);
    BookingsCommand(char*input,int index);
    ~BookingsCommand();
};

#endif
