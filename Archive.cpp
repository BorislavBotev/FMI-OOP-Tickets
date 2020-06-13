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
    deleteArray(halls,hallsSize);
    delete[]halls;
}
void Archive::createInitialHalls()
{
    std::ofstream os(DATABASE_NAME[0],std::ios::binary);
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
    int hallsCount;
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
        std::cout<<"HELLOOOOOOOOO"<<std::endl;
        for(int i=0; i<eventsCount; i++)
        {
            FileEvent* e;
            is.read((char*)e,(sizeof(FileEvent)));
            std::cout<<e->name<<e->date<<e->tickets<<std::endl;
            if(e==NULL)
            {
                is.close();
                throw MyException("Can not read event");
            }
            std::cout<<"Excuse me"<<std::endl;

            Event*event=new Event(e->name,e->date);
            std::cout<<"afasfa"<<std::endl;

            if(e->tickets>0)
            {
                FileTicket*t=new FileTicket[e->tickets];
                is.read((char*)t,(sizeof(FileTicket)*e->tickets));
                for(int k=0; k<e->tickets; k++)
                {
                    event->addTicketFromFile(t[k]);
                }
            }
            std::cout<<hallsSize-1<<std::endl;
            halls[hallsSize-1]->addEventFromFile(*event);

        }
    }
    std::cout<<"File with name:"<<file<<" has been uploaded"<<std::endl;
    is.close();
}
void Archive::addHallFromFile(int id,int rows,int seats,int eventsCount)
{
    if(hallsSize==hallsCapacity)
    {
        resizeArray(halls,hallsSize,hallsCapacity);
    }
    halls[hallsSize]=new Hall(id,rows,seats,eventsCount);
    hallsSize++;
    std::cout<<"Hallsize:"<<hallsSize<<std::endl;
}
void Archive::addEvent(char*name,char*date,int id)
{
    if(!name || !date)
    {
        throw MyException("Null pointer given");
    }
    int i=0;
    for(; i<hallsSize; i++)
    {
        if(halls[i]->getId()==id)
        {
            break;
        }
    }
    if(i>=hallsSize)
    {
        throw MyException("The hall you entered doesn't exist");
    }
    if(!halls[i]->isDateFree(date))
    {
        throw MyException("It is already booked");
    }
    Event*e=new Event(name,date);
    halls[i]->addEventFromFile(*e);
}
void Archive::save()
{
    if(hallsSize==0)
    {
        std::cout<<"There are no halls-nothing to save"<<std::endl;
    }
    std::ofstream os(DATABASE_NAME[0],std::ios::binary);
    if(!os.is_open())
    {
        throw MyException("Can not open db for in order to save");
    }
    int id=IDENTIFICATION;
    int countHalls=COUNT_HALLS;
    os.write((char const*)&id,sizeof(int));
    os.write((char const*)&countHalls,sizeof(int));
    for(int i=0; i<hallsSize; i++)
    {
        FileHall h(halls[i]->getId(),halls[i]->getRows(),halls[i]->getSeats(),halls[i]->getEventsSize());
        os.write((char const*)&h,sizeof(FileHall));
        for(int j=0; j<halls[i]->getEventsSize(); j++)
        {
            Event**ev=halls[i]->getEvents();
            FileEvent e(ev[j]->getName(),ev[j]->getDate(),ev[j]->getTicketsSize());
            std::cout<<"Event "<<ev[j]->getName()<<ev[j]->getDate()<<ev[j]->getTicketsSize()<<std::endl;
            os.write((char const*)&e,sizeof(FileEvent));
            for(int k=0; k<ev[j]->getTicketsSize(); k++)
            {
                Ticket*t=ev[j]->getTickets()[k];
                FileTicket fT(t->getName(),t->getDate(),t->getNote(),t->getRow(),t->getSeat(),t->getIsBought());
                os.write((char const*)&fT,sizeof(FileTicket));
            }
        }
    }
    os.close();
    std::cout<<"Successfully made changes to "<<DATABASE_NAME[0]<<std::endl;
}
void Archive::viewFreeSeats(char*name,char*date)
{
    std::cout<<"have fun";
    if(!name || !date)
    {
        throw MyException("Null pointer");
    };
    Event*e=NULL;
    int r=0,c=0;
    try
    {
        e=&getEventByNameAndDate(name,date,r,c);
    }
    catch(MyException e)
    {
        std::cout<<e.what()<<std::endl;
        return;
    }
    char arr[r][c];
    std::cout<<"E-empty,S-Sold,B-Booked"<<std::endl;
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            arr[i][j]='E';
        }
    }
    Ticket**t=e->getTickets();
    for(int i=0; i<e->getTicketsSize(); i++)
    {
        if(t[i]->getIsBought())
        {
            arr[t[i]->getRow()][t[i]->getSeat()]='S';
        }
        else
        {
            arr[t[i]->getRow()][t[i]->getSeat()]='B';
        }
    }
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            std::cout<<arr[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}
Event& Archive::getEventByNameAndDate(char*name,char*date,int& r,int&c)
{
    for(int i=0; i<hallsSize; i++)
    {
        Event**e=halls[i]->getEvents();
        for(int j=0; j<halls[i]->getEventsSize(); j++)
        {
            if(strcmp(name,e[j]->getName())==0 && strcmp(date,e[j]->getDate()))
            {
                r=halls[i]->getRows();
                c=halls[i]->getSeats();
                return *e[j];
            }
        }
    }
    throw MyException("There is no such event");
}


void Archive::printHalls()
{
    for(int i=0; i<hallsSize; i++)
    {
        std::cout<<*halls[i]<<std::endl;
    }
}
void Archive::close()
{
    /* deleteArray(halls,hallsSize);
     delete[]halls;
     hallsSize=0;
     hallsCapacity=5;
     std::cout<<"Sucessfully closed file"<<std::endl;*/
}

