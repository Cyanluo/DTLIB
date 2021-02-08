#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"
#include "Exception.h"

namespace DTLib
{

template <typename T>
class DynamicList:public SeqList<T>
{
protected:
    int m_capacity;
public:
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];

        if(this->m_array != NULL)
        {
            this->m_capacity = capacity;
            this->m_length = 0;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemonyException, "no enough memory to create array...");
        }
    }

    void resize(int size)
    {
        if(size != this->capacity())
        {
            T* array = new T[size];

            if(array != NULL)
            {
                int len = size < this->m_length ? size : this->m_length;

                for(int i=0; i<len; i++)
                {
                    array[i] = this->m_array[i];
                }

                T* temp = this->m_array;  // 保证异常安全

                this->m_array = array;
                this->m_length = len;
                this->m_capacity = size;

                delete [] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemonyException, "no enough memory to create array...");
            }
        }
    }

    int capacity() const
    {
        return this->m_capacity;
    }

    ~DynamicList()
    {
        delete [] this->m_array;
    }
};

}

#endif // DYNAMICLIST_H
