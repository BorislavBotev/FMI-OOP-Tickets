#include "ReportCommand.hpp"
ReportCommand::ReportCommand(char*input,int i):Command(input,i)
{
    hall=-1;
    date1=NULL;
    date2=NULL;
}
ReportCommand::~ReportCommand()
{
    delete[]date1;
    delete[]date2;
}
void ReportCommand::parseInput()
{
    char*arr=getInput();
    int index=getIndex();
    if(arr[index++]!=' ')
    {
        throw MyException("Invalid syntax");
    }
    date1=extractStringWithNoSPaces(arr,index);
    if(!date1 || !isValidDateFormat(date1))
    {
        throw MyException("Invalid date");
    }
    if(arr[index++]!=' ')
    {
        throw MyException("Invalid syntax");
    }
    date2=extractStringWithNoSPaces(arr,index);
    if(!date2 || !isValidDateFormat(date2))
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
    hall=extractNumberFromString(arr,index);
    if(hall==-1 || arr[index]!='\0')
    {
        throw MyException("Invalid hall");
    }
}
void ReportCommand::execute(Archive& database)
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
    char*d1=NULL;
    char*d2=NULL;
    createString(d1,date1);
    createString(d2,date2);
    try
    {
        database.report(hall,d1,d2);
        delete[]d1;
        delete[]d2;
    }
    catch(MyException e)
    {
        delete[]d1;
        delete[]d2;
        throw e;
    }

}
