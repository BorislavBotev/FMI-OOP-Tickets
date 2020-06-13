#include "AddEventCommand.hpp"
AddEventCommand::AddEventCommand(char*input,int index):Command(input,index)
{
    date=NULL;
    name=NULL;
    hall=0;
}
AddEventCommand::~AddEventCommand()
{
    delete[]date;
    delete[]name;
}
void AddEventCommand::execute(Archive&database)
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
    createString(n,name);
    char*d=NULL;
    createString(d,date);
    try
    {
            std::cout<<n<<d<<hall<<std::endl;

        database.addEvent(n,d,hall);
    }
    catch(MyException e)
    {
        delete[]n;
        delete[]d;
        throw e;
    }
    delete[]n;
    delete[]d;
}
void AddEventCommand::parseInput()
{
    char*arr=getInput();
    int startingIndex=getIndex();
    if(arr[startingIndex++]!=' ')
    {
        throw MyException("Invalid syntax");
    }
    date=extractStringWithNoSPaces(arr,startingIndex);
    if(!date || !isValidDateFormat(date))
    {
        throw MyException("Make sure date is in YYYY-MM-DD format");
    }
    if(arr[startingIndex++]!=' ')
    {
        delete[]date;
        throw MyException("Invalid syntax");
    }
    name=extractStringWithNoSPaces(arr,startingIndex);
    if(!name)
    {
        throw MyException("Make sure the name is only one word");
    }
    if(arr[startingIndex++]!=' ')
    {
        delete[]date;
        delete[]name;
        throw MyException("Invalid syntax");
    }
    hall=extractNumberFromString(arr,startingIndex);
    if(hall==0 || arr[startingIndex]!='\0')
    {
        delete[]date;
        delete[]name;
        throw MyException("Invalid id");
    }
}
