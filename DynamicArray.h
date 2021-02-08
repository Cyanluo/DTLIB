#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class DynamicArray:public Array<T>
{
protected:
    int m_length;

    T* copy(T* array, int len, int newlen)
    {
        T* ret = new T[newlen];

        if(ret != NULL)
        {
            int clen = newlen < len ? newlen : len;

            for(int i=0; i<clen; i++)
            {
                ret[i] = array[i];
            }
        }

        return ret;
    }

    void update(T* array, int length)
    {
        if(array != NULL)
        {
            T* temp = this->m_array;

            this->m_array = array;
            m_length = length;

            delete [] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemonyException, "No memory to create DynamicArray object...");
        }
    }

    void init(T* array, int length)
    {
        if(array != NULL)
        {
            this->m_array = array;
            m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemonyException, "No memory to create DynamicArray object...");
        }
    }
public:
    DynamicArray(int capacity = 0)
    {
        init(new T[capacity], capacity);
    }

    DynamicArray(const DynamicArray<T>& obj)
    {
        init(copy(obj.m_array, obj.length(), obj.length()), obj.length());
    }

    int length() const
    {
        return m_length;
    }

    DynamicArray<T>& operator =(const DynamicArray<T>& obj)
    {
        if(&obj != this)
        {
            update(copy(obj.m_array, obj.length(), obj.length()), obj.length());
        }

        return  *this;
    }

    void resize(int capacity)
    {
        update(copy(this->m_array, m_length, capacity), capacity);
    }

    ~DynamicArray()
    {
        delete [] this->m_array;
    }
};

}

#endif // DYNAMICARRAY_H
