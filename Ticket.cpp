#include "Ticket.hpp"
Ticket::~Ticket()
{
    delete[]name;
    delete[]date;
    delete[]note;
}
Ticket::Ticket()
{
    name=NULL;
    date=NULL;
    note=NULL;
}
Ticket::Ticket(char*name,char*date,int row,int seat,char*note,bool b)
{
    if(name && date && note)
    {
        createString(this->name,name);
        createString(this->date,date);
        createString(this->note,note);
        this->row=row;
        this->seat=seat;
        isBought=b;
    }
}
std::ostream& operator<<(std::ostream& os, Ticket &t)
{
    return os<<"Row:"<<t.getRow()<<"\nSeat"<<t.getSeat()<<"\nNote:"<<t.getNote();
}
