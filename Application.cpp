#include "Application.hpp"
Application::Application()
{
    command=NULL;
    archive=new Archive();
    isFileUploaded=false;
}
Application::~Application()
{
    delete command;
    delete archive;
}

void Application::run()
{
    archive->createHalls();
    char input[100]= {""};
    while(strcmp(input,"exit")!=0)
    {
        std::cout<<"Please write command"<<std::endl;
        std::cin.getline(input,100);
        int index=0;
        try
        {
            command=getCorrectCommand(input,index);
        }
        catch(MyException e)
        {
            std::cout<<e.what()<<std::endl;
            delete command;
            continue;
        }
        if(command==NULL)
        {
            std::cout<<"Invalid command entered"<<std::endl;
        }
        else
        {
            try
            {
                command->execute(*archive);
                isFileUploaded=true; //if a command executes (no matter which one) the file is uploaded
            }
            catch(MyException e)
            {
                std::cout<<e.what()<<std::endl;
            }
        }
        delete command;
    }
}
Command* Application::getCorrectCommand(char*arr,int& index)
{
    char*commandName=extractWordFromString(arr,index);
    if(!isFileUploaded && strcmp(commandName,"open")!=0)
    {
        delete[]commandName;
        throw MyException("First open a file");
    }
    if(strcmp(commandName,"open")==0)
    {
        if(isFileUploaded)
        {
            throw MyException("First close the current file ");
        }
        return new OpenCommand(arr,index);
    }
    else
    {
        return NULL;
    }
}

