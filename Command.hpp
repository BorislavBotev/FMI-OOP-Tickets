#ifndef COMMAND_HPP_INCLUDED
#define COMMAND_HPP_INCLUDED
class Command
{
public:
    virtual void execute()=0;
    virtual ~Command();

};

#endif // COMMAND_HPP_INCLUDED
