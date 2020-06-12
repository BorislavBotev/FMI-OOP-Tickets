#include "GlobalFunctions.hpp"
void createString(char*&des,const char*src)
{
    des=new char[strlen(src)+1];
    strcpy(des,src);
}

char* extractWordFromString(const char*input,int& startingIndex)
{
    char*name=NULL;
    int start=startingIndex;
    if(!input || strlen(input)==0)
    {
        return NULL;
    }
    while(input[startingIndex]>='a' && input[startingIndex]<='z')
    {
        startingIndex++;
    }
    if(startingIndex-start==0)
    {
        return NULL;
    }
    createSubString(name,input,start,(startingIndex-1));
    return name;
}
void createSubString(char*&name,const char*input,int start,int finish)
{
    int length=finish-start+1;
    name=new char[length+1];
    int i=0;
    for(; i<length; i++)
    {
        name[i]=input[start++];
    }
    name[i]='\0';
}
