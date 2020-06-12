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
public:
    Hall(int id,int rows,int seats);
};

#endif
