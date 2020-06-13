#ifndef ARCHIVE_HPP_INCLUDED
#define ARCHIVE_HPP_INCLUDED
#include "Hall.hpp"
#include "GlobalFunctions.hpp"
#include "MyException.hpp"
#include <fstream>
#include "Structs.hpp"
const int COUNT_HALLS=5;
const int IDENTIFICATION=-123;
const char DATABASE_NAME[1][10]={"db"};
class Archive
{
    //Hall* currentHall;
    Hall**halls;
    int hallsSize;
    int hallsCapacity;
    void addHallFromFile(int id,int rows,int seats,int eventsCount);
    Event& getEventByNameAndDate(char*name,char*date,int& r,int&c);

public:
    Archive();
    ~Archive();
    void createInitialHalls();
    void openFile(char*file);
    void close();
    void printHalls();
    void save();
            void viewFreeSeats(char*name,char*date);



void addEvent(char*name,char*date,int id);



};


#endif // ARCHIVE_HPP_INCLUDED
