#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED
#include <iostream>
#include <cstring>
#include "Command.hpp"
#include "Archive.hpp"
#include "MyException.hpp"
#include "GlobalFunctions.hpp"
#include "OpenCommand.hpp"
class Application
{
    Command* command;
    Archive*archive;
    bool isFileOpened;

    Command* getCorrectCommand(char*arr,int& index);

public:
    Application();
    ~Application();
    void run();

};


#endif // APPLICATION_HPP_INCLUDED
