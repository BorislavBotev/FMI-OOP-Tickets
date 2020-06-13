#include "BookingsCommand.hpp"
BookingsCommand::BookingsCommand(char*input,int i):Command(input,i)
{
    name=NULL;
    date=NULL;
}
BookingsCommand::~BookingsCommand()
{
    delete[]name;
    delete[]date;
}
void BookingsCommand::parseInput()
{
    char*arr=getInput();
    int index=getIndex();
    if(arr[index]=='\0')
    {
        return;
    }
    if(arr[index++]!=' ')
    {
        throw MyException("Invalid syntax");
    }
    date=extractStringWithNoSPaces(arr,index);
    if(!date || !isValidDateFormat(date))
    {
        throw MyException("Invalid date");
    }
    if(arr[index]=='\0')
    {
        return;
    }
    if(arr[index++]!=' ')
    {
        throw MyException("Invalid syntax");
    }
    name=extractStringWithNoSPaces(arr,index);
    if(!name)
    {
        throw MyException("Invalid name");
    }
    if(arr[index]!='\0')
    {
        throw MyException("Invalid syntax");
    }
}
void BookingsCommand::execute(Archive& database)
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
    if(name)
    {
        createString(n,name);
    }
    if(date)
    {
        createString(d,date);
    }
    try
    {
        database.bookingsInfo(n,d);
        delete[]n;
        delete[]d;
    }
    catch(MyException e)
    {
        delete[]n;
        delete[]d;
        throw e;
    }

}

