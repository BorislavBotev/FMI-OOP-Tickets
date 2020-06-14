#include "Archive.hpp"
Archive::Archive()
{
    hallsSize=0;
    hallsCapacity=5;
    halls=new Hall*[hallsCapacity];
}
Archive::~Archive()
{
    deleteArray(halls,hallsSize);
    delete[]halls;
}
void Archive::createInitialHalls()
{
    std::ifstream is(DATABASE_NAME[0],std::ios::binary);
    int id=0;
    is.read((char*)&id,sizeof(int));
    if(id==IDENTIFICATION)
    {
        is.close();
        return;
    }
    std::ofstream os(DATABASE_NAME[0],std::ios::binary);
    if(!os.is_open())
    {
        throw MyException("Can not download db");
    }
    id=IDENTIFICATION;
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
    std::ifstream is(file,std::ios::binary);
    if(is.bad())
    {
        is.close();
        throw MyException("Can not open file");
    }
    int identification=0;
    is.read((char*)&identification,sizeof(int));
    if(identification!=IDENTIFICATION)
    {
        is.close();
        throw MyException("This file is not from our database");
    }
    int hallsCount;
    is.read((char*)&hallsCount,sizeof(int));
    for(int j=0; j<hallsCount; j++)
    {
        int id=0,eventsCount=0,rows=0,seats=0;
        is.read((char*)&id,sizeof(int));
        is.read((char*)&rows,sizeof(int));
        is.read((char*)&seats,sizeof(int));
        is.read((char*)&eventsCount,sizeof(int));
        addHallFromFile(id,rows,seats,eventsCount);
        for(int i=0; i<eventsCount; i++)
        {
            FileEvent* e=new FileEvent();
            is.read((char*)e,(sizeof(FileEvent)));
            if(e==NULL)
            {
                is.close();
                throw MyException("Can not read event");
            }

            Event*event=new Event(e->name,e->date);
            if(e->tickets>0)
            {
                FileTicket*t=new FileTicket[e->tickets];
                is.read((char*)t,(sizeof(FileTicket)*e->tickets));
                for(int k=0; k<e->tickets; k++)
                {
                    event->addTicketFromFile(t[k]);
                }
            }
            halls[hallsSize-1]->addEventFromFile(*event);
            delete e;
        }
    }
    printHalls();
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
void Archive::save(char*file)
{
    if(hallsSize==0)
    {
        std::cout<<"There are no halls-nothing to save"<<std::endl;
    }
    std::ofstream os;
    if(!file)
    {
        os.open(DATABASE_NAME[0],std::ios::binary);
    }
    else
    {
        os.open(file,std::ios::binary);
    }
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
    viewAllSeatsInEvent(*e,r,c);
}

void Archive::viewAllSeatsInEvent(Event& e,int r,int c)
{
    char arr[r][c];
    std::cout<<"E-empty,S-Sold,B-Booked"<<std::endl;
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            arr[i][j]='E';
        }
    }
    Ticket**t=e.getTickets();
    for(int i=0; i<e.getTicketsSize(); i++)
    {
        if(t[i]->getIsBought())
        {
            arr[t[i]->getRow()-1][t[i]->getSeat()-1]='S';
        }
        else
        {
            arr[t[i]->getRow()-1][t[i]->getSeat()-1]='B';
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
void Archive::bookTicket(char*name,char*date,char*note,int row,int seat)
{
    if(!name || !date || !note)
    {
        throw MyException("Null pointer");
    }
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
    if(row<1 || row>r|| seat<1 || seat>c)
    {
        throw MyException("There is no such seat in this hall");
    }
    for(int i=0; i<e->getTicketsSize(); i++)
    {
        if(e->getTickets()[i]->getRow()==row && e->getTickets()[i]->getSeat()==0)
        {
            throw MyException("This seat is already taken i am sorry");
        }
    }
    Ticket*ticket=new Ticket(name,date,row,seat,note,false);
    e->addTicket(*ticket);
    std::cout<<"Successfully booked ticket"<<std::endl;
}
void Archive::buyTicket(char*name,char*date,int row,int seat)
{
    if(!name || !date)
    {
        throw MyException("Null pointer");
    }
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
    if(row<1 || row>r|| seat<1 || seat>c)
    {
        throw MyException("There is no such seat in this hall");
    }
    for(int i=0; i<e->getTicketsSize(); i++)
    {
        if(e->getTickets()[i]->getRow()==row && e->getTickets()[i]->getSeat()==0)
        {
            throw MyException("This seat is already taken i am sorry");
        }
    }
    Ticket*ticket=new Ticket(name,date,row,seat,"",true);
    e->addTicket(*ticket);
    std::cout<<"Successfully bought ticket"<<std::endl;
}
void Archive::unbookTicket(char*name,char*date,int row,int seat)
{
    if(!name || !date)
    {
        throw MyException("NULL pointer given");
    }
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
    if(row<1 || row>r|| seat<1 || seat>c)
    {
        throw MyException("There is no such seat in this hall");
    }
    for(int i=0; i<e->getTicketsSize(); i++)
    {
        if(e->getTickets()[i]->getRow()==row && e->getTickets()[i]->getSeat()==seat)
        {
            e->removeTicket(i);
            std::cout<<"Succesfully unbooked ticket for "<<name<<" "<<date<<" "<<row<<"-"<<seat<<std::endl;
            return;
        }
    }
    throw MyException("There is no ticket booked or bought for this seat");
}
void Archive::bookingsInfo(char*name,char*date)
{
    if(name && date)
    {
        Event*e=&getEventByNameAndDate(name,date);
        e->bookedTicketsInfo();
        return;
    }
    if(!name && date)
    {
        std::cout<<"The events on date "<<date<<" are:"<<std::endl;
        for(int i=0; i<hallsSize; i++)
        {
            Event**events=halls[i]->getEvents();
            for(int j=0; j<halls[i]->getEventsSize(); j++)
            {
                if(strcmp(events[j]->getDate(),date)==0)
                {
                    events[j]->bookedTicketsInfo();
                }
            }
        }
    }
    else
    {
        for(int i=0; i<hallsSize; i++)
        {
            std::cout<<"Hall:"<<halls[i]->getId()<<std::endl;
            Event**events=halls[i]->getEvents();
            for(int j=0; j<halls[i]->getEventsSize(); j++)
            {

                events[j]->bookedTicketsInfo();
            }
        }
    }
}

void Archive::report(int hallId,char*date1,char*date2)
{
    if(!date1 || !date2)
    {
        throw MyException("Null pointer");
    }
    if(!isValidPeriod(date1,date2))
    {
        throw MyException("Please make sure the second date is afetr the first one");
    }
    if(hallId==-1)
    {
        for(int i=0; i<hallsSize; i++)
        {
            hallsEventsSoldTicketsInfo(*halls[i],date1,date2);
        }
    }
    else
    {
        for(int i=0; i<hallsSize; i++)
        {
            if(halls[i]->getId()==hallId)
            {
                hallsEventsSoldTicketsInfo(*halls[i],date1,date2);
                return;
            }
        }
        throw MyException("There is no such hall");
    }
}
void Archive::hallsEventsSoldTicketsInfo(Hall&h,char*date1,char*date2)
{
    for(int i=0; i<h.getEventsSize(); i++)
    {
        if(isValidPeriod(date1,h.getEvents()[i]->getDate()) && isValidPeriod(h.getEvents()[i]->getDate(),date2))
        {
            std::cout<<h.getEvents()[i]->getName()<<" - "<<h.getEvents()[i]->getSoldTicketsCount()<<" tickets were sold"<<std::endl;
        }
    }
}

Event& Archive::getEventByNameAndDate(char*name,char*date,int& r,int&c)
{
    for(int i=0; i<hallsSize; i++)
    {
        Event**e=halls[i]->getEvents();
        for(int j=0; j<halls[i]->getEventsSize(); j++)
        {
            if(strcmp(name,e[j]->getName())==0 && strcmp(date,e[j]->getDate())==0)
            {
                r=halls[i]->getRows();
                c=halls[i]->getSeats();
                return *e[j];
            }
        }
    }
    throw MyException("There is no such event");
}
Event& Archive::getEventByNameAndDate(char*name,char*date)
{
    for(int i=0; i<hallsSize; i++)
    {
        Event**e=halls[i]->getEvents();
        for(int j=0; j<halls[i]->getEventsSize(); j++)
        {
            if(strcmp(name,e[j]->getName())==0 && strcmp(date,e[j]->getDate())==0)
            {
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


