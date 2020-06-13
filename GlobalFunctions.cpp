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
    if(startingIndex==start)
    {
        return NULL;
    }
    createSubString(name,input,start,(startingIndex-1));
    return name;
}
char* extractStringWithNoSPaces(const char*input,int& startingIndex)
{
    char*name=NULL;
    int start=startingIndex;
    if(!input || strlen(input)==0)
    {
        return NULL;
    }
    while(input[startingIndex]!=' ')
    {
        startingIndex++;
    }
    if(startingIndex==start)
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
int extractNumberFromString(const char*arr,int& startingIndex)
{
    int number=0;
    while(arr[startingIndex]>='0' && arr[startingIndex<='9'])
    {
        number*=10;
        number+=(arr[startingIndex]-'0');
        startingIndex++;
    }
    return number;
}
bool isValidDateFormat(const char*date)
{
    if(!date)
    {
        return false;
    }
    int year=0,month=0,day=0,index=0;
    if(date[index]==0)
    {
        return false;
    }
    year=extractNumberFromString(date,index);
    if(year==0 || date[index++]!='-')
    {
        return false;
    }
    month=extractNumberFromString(date,index);
    if(month==0 || month>12 || (month<10 && date[index-2]!='0' && date[index-3]!='-') || (month>=10 && date[index-3]!='-') || date[index++]!='-')
    {
        return false;
    }
    day=extractNumberFromString(date,index);
    if(date[index]!='\0' || day==0 || day>31 || (day<10 && date[index-2]!='0' && date[index-3]!='-') || (day>=10 && date[index-3]!='-'))
    {
        return false;
    }
    if((month==4 || month==6 || month==9 || month==11) && day==31)
    {
        return false;
    }
    if(month==2 && (day>=28 || (day==27 && year%4==0)))
    {
        return false;
    }
    return true;
}
