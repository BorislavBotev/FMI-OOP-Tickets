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
    Ticket(char*name,char*date,int row,int seat,char*note,bool isBought){}
};

#endif // TICKET_HPP_INCLUDED
