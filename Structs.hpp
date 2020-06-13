#ifndef STRUCTS_HPP_INCLUDED
#define STRUCTS_HPP_INCLUDED
#include <cstring>
struct FileEvent
{
    char name[50];
    char date[11];
    int tickets;
    FileEvent(char*n,char*d,int t)
    {
        strcpy(name,n);
        strcpy(date,d);
        tickets=t;
    }
    FileEvent(){}
};
struct FileTicket
{
    int row;
    int seat;
    char name[50];
    char date[11];
    char note[20];
    bool isBought;
    FileTicket(char*n,char*d,char*nt,int r,int s,bool b)
    {
        strcpy(name,n);
        strcpy(date,d);
        strcpy(note,nt);
        row=r;
        seat=s;
        isBought=b;
    }
    FileTicket() {}

};
struct FileHall
{
    int id;
    int rows;
    int seats;
    int events;
    FileHall (int id,int rows,int seats,int events=0)
    {
        this->id=id;
        this->rows=rows;
        this->  seats=seats;
        this-> events=events;
    }
    FileHall() {}

};


#endif // STRUCTS_HPP_INCLUDED
