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
    try
    {
        archive->createInitialHalls();
    }
    catch(MyException e)
    {
        std::cout<<e.what()<<std::endl;
        return;
    }
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
        catch(CloseException e)
        {
            continue;
        }
        catch(ExitException e)
        {
            std::cout<<"Exit"<<std::endl;
            return;
        }

        catch(MyException e)
        {
            std::cout<<e.what()<<std::endl;
            delete command;
            command=NULL;
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
        command=NULL;
    }
}
Command* Application::getCorrectCommand(char*arr,int& index)
{
    char*commandName=extractWordFromString(arr,index);
    if(strcmp(commandName,"open")==0)
    {
        if(isFileUploaded)
        {
            delete []commandName;
            throw MyException("First close the current file ");
        }
        return new OpenCommand(arr,index);
    }
    else if(strcmp(commandName,"close")==0)
    {
        if(arr[index]!='\0')
        {
            delete []commandName;
            throw MyException("Maybe you wanted to write close");
        }
        if(!isFileUploaded)
        {
            delete []commandName;
            throw MyException("There is no opened file");
        }
        archive->close();
        isFileUploaded=false;
        throw CloseException();
    }
    else if(strcmp(commandName,"exit")==0)
    {
        if(arr[index]!='\0')
        {
            delete []commandName;
            throw MyException("Maybe you wanted to write exit");
        }
        throw ExitException();
    }
    else if(!isFileUploaded)
    {
        delete[]commandName;
        throw MyException("First open a file");
    }
    else
    {
        return NULL;
    }
}

