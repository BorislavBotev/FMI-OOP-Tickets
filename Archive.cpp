#include "Archive.hpp"
void Archive::createHalls()
{
    halls=new Hall*[COUNT_HALLS];
    for(int i=0; i<COUNT_HALLS; i++)
    {
        halls[i]=new Hall(i+1,i*10,i+5);
    }
}
