#ifndef TICKET_HPP_INCLUDED
#define TICKET_HPP_INCLUDED
#include <cstring>
#include "GlobalFunctions.hpp"
class Ticket
{
    char*name;
    char*date;
    int row;
    int seat;
    char*note;
    bool isBought;
public:
    Ticket(char*name,char*date,int row,int seat,char*note,bool isBought);
    Ticket();
    ~Ticket();
    char*getName()const
    {
        return name;
    }
    char* getDate()const
    {
        return date;
    }
    int getRow()const
    {
        return row;
    }
    int getSeat()const
    {
        return seat;
    }
    char*getNote()const
    {
        return note;
    }
    bool getIsBought()const
    {
        return isBought;
    }
};
std::ostream& operator<<(std::ostream& os, Ticket &t)


#endif // TICKET_HPP_INCLUDED
