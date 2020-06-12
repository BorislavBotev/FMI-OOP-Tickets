#ifndef HALL_HPP_INCLUDED
#define HALL_HPP_INCLUDED
#include "Event.hpp"
class Hall
{
    int id;
    int rows;
    int seats;
   // std::ofstream& os;
    Event**events;
    int eventsSize;
    int eventsCapacity;
public:
    Hall(int id,int rows,int seats);
    Hall(int id,int rows,int seats,int eventsCount);
    void addEventFromFile(Event&event);


};

#endif
