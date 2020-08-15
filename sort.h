#ifndef SORT_H
#define SORT_H

#include "Object.h"

namespace DTLib
{

class Sort:public Object
{
    Sort();
    Sort(const Sort& obj);
    const Sort& operator = (const Sort& obj);

    template <typename T>
    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }
public:
    template <typename T>
    static void Setect(T array[], int len, bool min2max=true)
    {
        for(int i=0; i<len; i++)
        {
            int flag = i;
            for(int j=i+1; j<len; j++)
            {
                if(min2max ? (array[flag] > array[j]) : (array[flag] < array[j]))
                {
                    flag = j;
                }
            }

            if(flag != i)
            {
                Swap(array[flag], array[i]);
            }
        }
    }

    template < typename T >
    static void Insert(T array[], int len, bool min2max=true)
    {
        for(int i=1; i<len; i++)
        {
            T e = array[i];
            int p = i;

            for(int j=i-1; j>=0 && (min2max ? e>array[j] : e<array[j]); j--)
            {
                array[j+1] = array[j];
                p = j;
            }

            array[p] = e;
        }
    }
};

}

#endif // SORT_H








