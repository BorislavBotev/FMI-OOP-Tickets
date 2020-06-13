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
    void addTicket(Ticket&ticket);
 void removeTicket(int id);
 void bookedTicketsInfo();


    Event(char*name,char*date);
    ~Event();
    char* getName()const;
char* getDate()const;
int getTicketsSize() const;
 Ticket** getTickets()const;





};


#endif // EVENT_HPP_INCLUDED
