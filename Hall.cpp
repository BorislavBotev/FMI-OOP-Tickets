#include "Hall.hpp"
Hall:: Hall(int id,int rows,int seats)
{
    this->id=id;
    this->rows=rows;
    this->seats=seats;
    // os=NULL;
    events=NULL;
    eventsSize=0;
    eventsCapacity=5;
}
Hall::~Hall()
{
    deleteArray(events,eventsSize);
    delete[]events;
}
Hall:: Hall(int id,int rows,int seats,int eventsCount)
{
    this->id=id;
    this->rows=rows;
    this->seats=seats;
    // os=NULL;
    eventsSize=0;
    eventsCapacity=eventsCount;
    events=new Event*[eventsCapacity];
}
void Hall::addEventFromFile(Event&event)
{
    if(eventsSize==eventsCapacity)
    {
        resizeArray(events,eventsSize,eventsCapacity);
    }
    events[eventsSize++]=&event;
    std::cout<<event.getName()<<std::endl;
}
int Hall::getId()
{
    return id;
}
int Hall::getRows()
{
    return rows;
}
int Hall::getSeats()
{
    return seats;
}
int Hall::getEventsSize()
{
    return eventsSize;
}
 Event** Hall::getEvents()const
{
    return events;
}
bool Hall::isDateFree(char*date)
{
    if(!date)
    {
        return false;
    }
    for(int i=0;i<eventsSize;i++)
    {
        if(strcmp(events[i]->getDate(),date)==0)
        {
            return false;
        }
    }
    return true;
}


std::ostream& operator<<(std::ostream& os, Hall &h)
{
    return os<<"Hall number:"<<h.getId()<<" with "<<h.getRows()<<" rows and "<<h.getSeats()<<" seats and "<<h.getEventsSize()<<" tickets sold so far";
}
