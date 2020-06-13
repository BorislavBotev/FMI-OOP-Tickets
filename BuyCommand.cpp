#include "BuyCommand.hpp"
BuyCommand::BuyCommand(char*input,int i):Command(input,i)
{
    name=NULL;
    date=NULL;
}
BuyCommand::~BuyCommand()
{
    delete[]name;
    delete[]date;
}
void  BuyCommand::parseInput()
{
    const char*arr=getInput();
    int index=getIndex();
    validEventSeatInput(name,date,row,seat,arr,index);
      if(arr[index]!='\0')
    {
        throw MyException("Invalid syntax");
    }
}
void BuyCommand::execute(Archive& database)
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
        database.buyTicket(n,d,row,seat);
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

