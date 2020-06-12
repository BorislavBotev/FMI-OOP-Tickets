#ifndef ARCHIVE_HPP_INCLUDED
#define ARCHIVE_HPP_INCLUDED
#include "Hall.hpp"
#include "GlobalFunctions.hpp"
#include "MyException.hpp"
#include <fstream>
#include "Structs.hpp"
const int COUNT_HALLS=5;
const int IDENTIFICATION=-123;
class Archive
{
    //Hall* currentHall;
    Hall**halls;
    int hallsSize;
    int hallsCapacity;
        void addHallFromFile(int id,int rows,int seats,int eventsCount);

public:
    Archive();
    ~Archive();
    void createHalls();
    void openFile(char*file);


};


#endif // ARCHIVE_HPP_INCLUDED
