#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace DTLib
{

template < typename T >
class CircleList: public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    Node* last() const
    {
        return this->position(this->m_length-1)->next;
    }

    void lastToFirst() const
    {
        last()->next = this->m_header.next;
    }

    int mod(int i) const
    {
        return (this->m_length == 0) ? 0 : (i % (this->m_length));
    }
public:
    bool insert(int i, const T& e)
    {
        i = i % (this->m_length + 1);

        bool ret = LinkList<T>::insert(i, e);

        if(i == 0)
        {
            lastToFirst();
        }

        return ret;
    }

    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        if(i == 0)
        {
            Node* toDel = this->m_header.next;

            if(toDel != NULL)
            {
                this->m_header.next = toDel->next;
                this->m_length--;

                if(this->m_length > 0)
                {
                    lastToFirst();

                    if(this->m_current == toDel)
                    {
                        this->m_current = toDel->next;
                    }
                }
                else
                {
                    this->m_header.next = NULL;
                    this->m_current = NULL;
                }

                this->destroy(toDel);
            }
        }
        else
        {
            ret = LinkList<T>::remove(i);
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        return LinkList<T>::get(mod(i), e);
    }

    T get(int i) const
    {
        return LinkList<T>::get(mod(i));
    }

    int find(const T& e) const
    {
        int ret = -1;

        Node* current = this->m_header.next;

        for(int i=0; i<this->m_length; i++)
        {
            if(current->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                current = current->next;
            }
        }

        return ret;
    }

    void clear()
    {
        while(this->m_length > 1)
        {
            remove(1);
        }

        if(this->m_length == 1)
        {
            remove(0);
        }
    }

    bool end() const
    {
        return ( (this->m_length == 0) || (this->m_current == NULL) );
    }

    bool move(int i, int step=1)
    {
        return LinkList<T>::move(mod(i), step);
    }

    ~CircleList()
    {
        clear();
    }
};

}

#endif // CIRCLELIST_H










