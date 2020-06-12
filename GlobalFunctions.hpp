#ifndef GLOBALFUNCTIONS_HPP_INCLUDED
#define GLOBALFUNCTIONS_HPP_INCLUDED
#include <cstring>
void createString(char*&des,const char*src);
char* extractWordFromString(const char*input,int& startingIndex);
void createSubString(char*&name,const char*input,int start,int finish);
template <typename T>
void deleteArray(T**arr,int size)
{
    for(int i=0; i<size; i++)
    {
        delete arr[i];
    }
    delete[] arr;
}

template <typename T>
void resizeArray(T**&arr,int size,int& capacity)
{
    capacity=capacity*2;
    T**newArray=new T*[capacity];
    for(int i=0; i<size; i++)
    {
        newArray[i]=arr[i];
    }
    delete[] arr;
    arr=newArray;
}


#endif // GLOBALFUNCTIONS_HPP_INCLUDED
