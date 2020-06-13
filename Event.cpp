#include "Event.hpp"
Event::Event(char*name,char*date)
{
    createString(this->name,name);
    createString(this->date,date);
    tickets=NULL;
    ticketsSize=0;
    ticketsCapacity=5;

}
Event::~Event()
{
    delete[]name;
    delete[]date;
    deleteArray(tickets,ticketsSize);
    delete[]tickets;
}
char* Event::getName()const
{
    return name;
}
char* Event::getDate()const
{
    return date;
}
int Event::getTicketsSize() const
{
    return ticketsSize;
}
Ticket** Event:: getTickets() const
{
    return tickets;
}


void Event::addTicketFromFile(FileTicket&t)
{
    std::cout<<"sddgdfg"<<std::endl;
    if(strcmp(t.name,name)!=0 || strcmp(t.date,date)!=0)
    {
        std::cout<<"Ticket "<< t.name<<" doesn;t belong to "<<name<<" "<<date<<std::endl;
        return;
    }
    if(ticketsSize==ticketsCapacity)
    {
        resizeArray(tickets,ticketsSize,ticketsCapacity);
    }
    tickets[ticketsSize++]=new Ticket(t.name,t.date,t.row,t.seat,t.note,t.isBought);
}
