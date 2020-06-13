#include "Event.hpp"
Event::Event(char*name,char*date)
{
    createString(this->name,name);
    createString(this->date,date);
    ticketsSize=0;
    ticketsCapacity=5;
    tickets=new Ticket*[ticketsCapacity];
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
void Event::addTicket(Ticket&ticket)
{
    if(ticketsSize==ticketsCapacity)
    {
        resizeArray(tickets,ticketsSize,ticketsCapacity);
    }
    tickets[ticketsSize++]=&ticket;
}
void Event::removeTicket(int id)
{
    if(tickets[id]==NULL)
    {
        throw MyException("Null pointer at ticket id");
    }
    delete tickets[id];
    for(int index=id; index<ticketsSize-1; index++)
    {
        tickets[index]=tickets[index+1];
    }
    ticketsSize--;
}
void Event::bookedTicketsInfo()
{

    std::cout<<"Event "<<name<<" on "<<date<<std::endl;
    for(int i=0;i<ticketsSize;i++)
    {
        if(!tickets[i]->getIsBought()){
        std::cout<<"Ticket: "<<*tickets[i]<<std::endl;
        }
    }
}
int Event::getSoldTicketsCount()
{
    int count=0;
    for(int i=0;i<ticketsSize;i++)
    {
        if(tickets[i]->getIsBought())
        {
            count++;
        }
    }
    return count;
}

