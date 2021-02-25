#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include "Array.h"

namespace DTLib
{

class Sort:public Object
{
    Sort();
    Sort(const Sort& obj);
    const Sort& operator = (const Sort& obj);

    template < typename T >
    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }

    template < typename T >
    static void Merge(T array[], T helper[], int begin, int end, bool min2max)
    {
        if(begin == end)
        {
            return;
        }
        else
        {
            int mid = (begin + end)/2;

            Merge(array, helper, begin, mid, min2max);
            Merge(array, helper, mid+1, end, min2max);

            Merge(array, helper, begin, mid, end, min2max);
        }
    }

    template< typename T >
    static void Merge(T array[], T helper[], int begin, int mid, int end, bool min2max=false)
    {
        int i = begin;
        int j = mid + 1;
        int p = begin;

        while((i <= mid) && (j <= end))
        {
            if(min2max ? array[i] > array[j] : array[i] < array[j])
            {
                helper[p++] = array[i++];
            }
            else
            {
                helper[p++] = array[j++];
            }
        }

        while(i <= mid)
        {
            helper[p++] = array[i++];
        }

        while(j <= end)
        {
            helper[p++] = array[j++];
        }

        for(int i=begin; i<=end; i++)
        {
            array[i] = helper[i];
        }
    }

    template < typename T >
    static int Partition(T array[], int begin, int end, bool min2max)
    {
        T py = array[begin];

        while(begin < end)
        {
            while((begin < end) && (min2max ? array[end] < py : array[end] > py))
            {
                end--;
            }

            Swap(array[begin], array[end]);

            while((begin < end) && (min2max ? array[begin] >= py : array[begin] <= py))
            {
                begin++;
            }

            Swap(array[begin], array[end]);
        }

        array[begin] = py;

        return begin;
    }

    template< typename T >
    static void Quick(T array[], int begin, int end, bool min2max)
    {
        if(begin < end)
        {
            int py = Partition(array, begin, end, min2max);

            Quick(array, begin, py-1, min2max);

            Quick(array, py+1, end, min2max);
        }
    }
public:
    template < typename T >
    static void Select(T array[], int len, bool min2max=false)
    {
        for(int i=0; i<len; i++)
        {
            int flag = i;
            for(int j=i+1; j<len; j++)
            {
                if(min2max ? (array[flag] < array[j]) : (array[flag] > array[j]))
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
    static void Select(Array<T>& array, bool min2max=false)
    {
        Select(array.array(), array.length(), min2max);
    }

    template < typename T >
    static void Insert(T array[], int len, bool min2max)
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

    template < typename T >
    static void Insert(Array<T>& array, bool min2max=false)
    {
        Insert(array.array(), array.length(), min2max);
    }

    template < typename T >
    static void Bubble(T array[], int len, bool min2max=false)
    {
        bool exchange = true;

        for(int i=0; i<len && exchange; i++)
        {
            exchange = false;

            for(int j=len-1; j>i ; j--)
            {
                if(min2max ? array[j]>array[j-1] : array[j]<array[j-1])
                {
                    Swap(array[j], array[j-1]);

                    exchange = true;
                }
            }
        }
    }

    template < typename T >
    static void Bubble(Array<T>& array, bool min2max=false)
    {
        Bubble(array.array(), array.length(), min2max);
    }

    template < typename T >
    static void Shell(T array[], int len, bool min2max=false)
    {
        int d = len;

        do
        {
            d = d / 3 + 1;

            for(int i=d; i<len; i+=d)
            {
                T e = array[i];
                int p = i;

                for(int j=i-d; j>=0 && (min2max ? e>array[j] : e<array[j]); j-=d)
                {
                    array[j+d] = array[j];
                    p = j;
                }

                array[p] = e;
            }

        }while(d > 1);

    }

    template < typename T >
    static void Shell(Array<T>& array, bool min2max=false)
    {
        Shell(array.array(), array.length(), min2max);
    }

    template< typename T >
    static void Merge(T array[], int len, bool min2max=false)
    {
        T* helper = new T[len];

        if(helper)
        {
            Merge(array, helper, 0, len-1, min2max);
        }

        delete [] helper;
    }

    template < typename T >
    static void Merge(Array<T>& array, bool min2max=false)
    {
        Merge(array.array(), array.length(), min2max);
    }

    template< typename T >
    static void Quick(T array[], int len, bool min2max=false)
    {
        Quick(array, 0, len-1, min2max);
    }

    template < typename T >
    static void Quick(Array<T>& array, bool min2max=false)
    {
        Quick(array.array(), array.length(), min2max);
    }
};

}

#endif // SORT_H








