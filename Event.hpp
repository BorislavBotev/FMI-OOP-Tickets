#ifndef EVENT_HPP_INCLUDED
#define EVENT_HPP_INCLUDED
#include <iostream>
#include "Ticket.hpp"
#include "Structs.hpp"
class Event
{
    char*name;
    char*date;
    Ticket**tickets;
    int ticketsSize;
    int ticketsCapacity;
public:
    void addTicketFromFile(FileTicket&t);
    Event(char*name,char*date);
    ~Event();

};


#endif // EVENT_HPP_INCLUDED
