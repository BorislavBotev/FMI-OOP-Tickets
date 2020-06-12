#ifndef STRUCTS_HPP_INCLUDED
#define STRUCTS_HPP_INCLUDED
struct FileEvent
{
    char name[50];
    char date[11];
    int tickets;

};
struct FileTicket
{
    int row;
    int seat;
    char name[50];
    char date[11];
    char note[20];
    bool isBought;
};
/*struct Hall
{
    int eventsCount;
    int rows;
    int seats;
    FileEvent;
    Ticket tickets[rows][seats];
};*/


#endif // STRUCTS_HPP_INCLUDED
