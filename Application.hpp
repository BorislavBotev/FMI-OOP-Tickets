#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED
#include <iostream>
#include <cstring>
#include "Command.hpp"
#include "Archive.hpp"
#include "MyException.hpp"
#include "GlobalFunctions.hpp"
#include "OpenCommand.hpp"
#include "CloseException.hpp"
#include "ExitException.hpp"
#include "SaveCommand.hpp"
#include "AddEventCommand.hpp"
#include "FreeSeatsCommand.hpp"
#include "BookCommand.hpp"
#include "UnbookCommand.hpp"
#include "BuyCommand.hpp"
#include "BookingsCommand.hpp"
#include "ReportCommand.hpp"

class Application
{
    Command* command;
    Archive*archive;
    bool isFileUploaded;
    Command* getCorrectCommand(char*arr,int& index);

public:
    Application();
    ~Application();
    void run();

};


#endif // APPLICATION_HPP_INCLUDED
