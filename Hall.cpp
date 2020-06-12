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
}

