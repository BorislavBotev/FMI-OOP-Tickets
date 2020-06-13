#include "BookCommand.hpp"
BookCommand::BookCommand(char*input,int i):Command(input,i)
{
    name=NULL;
    date=NULL;
    note=NULL;
}
BookCommand::~BookCommand()
{
    delete[]name;
    delete[]date;
    delete[]note;
}

void  BookCommand::parseInput()
{
    const char*arr=getInput();
    int index=getIndex();
    validEventSeatInput(name,date,row,seat,arr,index);
    if(arr[index++]!=' ')
    {
       // delete[]date;
        //delete[]name;
        throw MyException("Invalid syntax");
    }
    note=extractStringWithNoSPaces(arr,index);
    if(!note || arr[index]!='\0')
    {
       // delete[]date;
       // delete[]name;
        throw MyException("Invalid note");
    }
}


void BookCommand::execute(Archive& database)
{
    try
    {
        parseInput();
    }
    catch(MyException e)
    {
        std::cout<<e.what()<<std::endl;
        return;
    }
    char*n=NULL;
    char*d=NULL;
    char*no=NULL;
    createString(n,name);
    createString(d,date);
    createString(no,note);
    try
    {
        database.bookTicket(n,d,no,row,seat);
        delete[]n;
        delete[]d;
        delete[]no;
    }
    catch(MyException e)
    {
               delete[]n;
        delete[]d;
        delete[]no;
        throw e;
    }

}
