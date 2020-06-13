#include "Ticket.hpp"
Ticket::~Ticket()
{
    delete[]name;
    delete[]date;
    delete[]note;
}
