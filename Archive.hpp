#ifndef ARCHIVE_HPP_INCLUDED
#define ARCHIVE_HPP_INCLUDED
#include "Hall.hpp"
#include "GlobalFunctions.hpp"
#include "MyException.hpp"
#include <fstream>
#include "Structs.hpp"
#include "Event.hpp"
const int COUNT_HALLS=5;
const int IDENTIFICATION=-123;
const char DATABASE_NAME[1][10]= {"db"};
class Archive
{
    //Hall* currentHall;
    Hall**halls;
    int hallsSize;
    int hallsCapacity;
    void addHallFromFile(int id,int rows,int seats,int eventsCount);
    void viewAllSeatsInEvent(Event& e,int r,int c);
    Event& getEventByNameAndDate(char*name,char*date,int& r,int&c);
    Event& getEventByNameAndDate(char*name,char*date);
    void hallsEventsSoldTicketsInfo(Hall&h,char*date1,char*date2);



public:
    Archive();
    ~Archive();
    void createInitialHalls();
    void openFile(char*file);
    void printHalls();
    void save(char*file);
    void viewFreeSeats(char*name,char*date);
    void bookTicket(char*name,char*date,char*note,int row,int seat);
    void unbookTicket(char*name,char*date,int row,int seat);
    void buyTicket(char*name,char*date,int row,int seat);
    void bookingsInfo(char*name,char*date);
    void addEvent(char*name,char*date,int id);
    void report(int hallId,char*date1,char*date2);



};


#endif // ARCHIVE_HPP_INCLUDED
