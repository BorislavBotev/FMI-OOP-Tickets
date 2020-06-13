#include "FreeSeatsCommand.hpp"
FreeSeatsCommand::FreeSeatsCommand(char*input,int index):Command(input,index)
{
    name=NULL;
    date=NULL;
}
FreeSeatsCommand::~FreeSeatsCommand()
{
    delete[]name;
    delete[]date;
}

void FreeSeatsCommand::parseInput()
{
    char*arr=getInput();
    int startingIndex=getIndex();
    if(arr[startingIndex++]!=' ')
    {
        throw MyException("Invalid syntax-one space between words");
    }
    date=extractStringWithNoSPaces(arr,startingIndex);
    if(!date || !isValidDateFormat(date))
    {
        delete[]date;
        throw MyException("Invalid date format");
    }
    if(arr[startingIndex++]!=' ')
    {
        delete[]date;
        throw MyException("Invalid syntax-one space between words");
    }
    name=extractStringWithNoSPaces(arr,startingIndex);
    if(!name || arr[startingIndex]!='\0')
    {
        std::cout<<(int)arr[startingIndex]<<std::endl;
        delete[]date;
        delete[]name;
        throw MyException("Invalid name");
    }
}
void FreeSeatsCommand::execute(Archive&database)
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
    createString(n,name);
    createString(d,date);
    try
    {
        database.viewFreeSeats(n,d);
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
