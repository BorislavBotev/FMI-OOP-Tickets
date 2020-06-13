#ifndef REPORTCOMMAND_HPP_INCLUDED
#define REPORTCOMMAND_HPP_INCLUDED
#include "Command.hpp"
class ReportCommand:public Command
{
    char*name;
    char*date1;
    char*date2;
    void parseInput();
public:
    void execute(Archive&database);
    ReportCommand(char*input,int index);
    ~ReportCommand();
};


#endif // REPORTCOMMAND_HPP_INCLUDED
