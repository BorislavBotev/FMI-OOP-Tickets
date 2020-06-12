#include <iostream>

#include "Application.hpp"
int main()
{
    Application*app=new Application();
    app->run();
    delete app;
}
