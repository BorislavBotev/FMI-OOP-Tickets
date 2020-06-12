#include "Event.hpp"
Event::Event(char*name,char*date)
{
    if(!name && strlen(name)!=0)
    {
        createString(this->name,name);
    }
    this->date=date;
    //ASFAAAASF
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


void Event::addTicketFromFile(FileTicket&t)
{
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
