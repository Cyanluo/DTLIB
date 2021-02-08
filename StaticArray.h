#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Array.h"

namespace DTLib
{

template < typename T, int N >
class StaticArray:public Array<T>
{
protected:
    int m_length;
    T m_space[N];
public:
    StaticArray()
    {
        this->m_array = m_space;
        m_length = N;
    }

    StaticArray(const StaticArray<T, N>& obj)
    {
        this->m_array = m_space;

        for(int i=0; i<obj.length(); i++)
        {
            m_space[i] = obj.m_space[i];
        }
    }

    int length() const
    {
        return N;
    }

    StaticArray<T, N>& operator =(const StaticArray<T, N>& obj)
    {
        if(&obj != this)
        {
            for(int i=0; i<obj.length(); i++)
            {
                m_space[i] = obj.m_space[i];
            }
        }

        return  *this;
    }
};

}

#endif // STATICARRAY_H
