#include "Archive.hpp"
Archive::Archive()
{
    //currentHall=NULL;
    hallsSize=0;
    hallsCapacity=5;
    halls=new Hall*[hallsCapacity];
}
Archive::~Archive()
{
    // delete currentHall;
    deleteArray(halls,COUNT_HALLS);
}
void Archive::createInitialHalls()
{
    std::ofstream os("db",std::ios::binary);
    if(!os.is_open())
    {
        throw MyException("Can not download db");
    }
    int id=IDENTIFICATION;
    int countHalls=COUNT_HALLS;
    os.write((char const*)&id,sizeof(int));
    os.write((char const*)&countHalls,sizeof(int));
    for(int i=1; i<=COUNT_HALLS; i++)
    {
        FileHall h(i,10*i,5+i);
        os.write((char const*)&h,sizeof(FileHall));
    }
    os.close();
    std::cout<<"Successfully made DB"<<std::endl;
}
void Archive::openFile(char*file)
{
    if(!file || strlen(file)==0)
    {
        throw MyException("Invalid file provided");
    }
    std::cout<<file<<std::endl;
    std::ifstream is(file,std::ios::binary);
    if(is.bad())
    {
        is.close();
        throw MyException("Can not open file");
    }
    int identification=0;
    is.read((char*)&identification,sizeof(int));

        std::cout<<"ID:"<<identification<<std::endl;
        if(identification!=IDENTIFICATION)
        {
            is.close();
            throw MyException("This file is not from our database");
        }
    int hallsCount=0;
    is.read((char*)&hallsCount,sizeof(int));
                std::cout<<"Halls:"<<hallsCount<<std::endl;
    for(int j=0; j<hallsCount; j++)
    {
        int id=0,eventsCount=0,rows=0,seats=0;
        is.read((char*)&id,sizeof(int));
        is.read((char*)&rows,sizeof(int));
        is.read((char*)&seats,sizeof(int));
        is.read((char*)&eventsCount,sizeof(int));
        std::cout<<id<<rows<<seats<<eventsCount<<std::endl;
        addHallFromFile(id,rows,seats,eventsCount);
        for(int i=0; i<eventsCount; i++)
        {
            FileEvent* e=NULL;
            is.read((char*)e,(sizeof(FileEvent)));
            if(e==NULL)
            {
                is.close();
                throw MyException("Can not read event");
            }
            if(e->tickets==0)
            {
                continue;
            }
            FileTicket*t=new FileTicket[e->tickets];
            is.read((char*)t,(sizeof(FileTicket)*e->tickets));
            Event*event=new Event(e->name,e->date);
            for(int i=0; i<e->tickets; i++)
            {
                event->addTicketFromFile(t[i]);
            }
            halls[hallsSize-1]->addEventFromFile(*event);
        }
    }
    std::cout<<"File with name:"<<file<<" has been uploaded"<<std::endl;
}
void Archive::addHallFromFile(int id,int rows,int seats,int eventsCount)
{
    if(hallsSize==hallsCapacity)
    {
        resizeArray(halls,hallsSize,hallsCapacity);
    }
    halls[hallsSize++]=new Hall(id,rows,seats,eventsCount);
}

void Archive::printHalls()
{
    for(int i=0;i<hallsSize;i++)
    {
        std::cout<<*halls[i]<<std::endl;
    }
}

