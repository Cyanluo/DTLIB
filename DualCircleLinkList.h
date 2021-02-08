#ifndef DUALCIRCLELINKLIST_H
#define DUALCIRCLELINKLIST_H

#include "DualLinklist.h"
#include "LinuxList.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class DualCircleLinkList: public DualLinkList<T>
{
protected:
    struct Node: public Object
    {
        list_head m_list_head;
        T value;
    };

    list_head m_list_head;
    list_head* m_current;

    list_head* position(int i) const
    {
        list_head* ret = const_cast<list_head*>(&m_list_head);

        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }

    int mod(int i) const
    {
        return ((this->m_length == 0) ? 0 : (i % this->m_length));
    }

public:
    DualCircleLinkList()
    {
        this->m_current = NULL;
        this->m_length = 0;
        this->m_step = 1;

        INIT_LIST_HEAD(&m_list_head);
    }

    bool insert(const T& e)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = true;

        i = i % (this->m_length + 1);

        ret &= (0 <= i) && (i <= this->m_length);

        if(ret)
        {
            list_head* current = position(i)->next;

            Node* node = new Node;

            if(node != NULL)
            {
                node->value = e;

                list_add_tail(&node->m_list_head, current);

                this->m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemonyException, "no memary to insert element...");
            }
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        ret &= ((0 <= i) && (i < this->m_length));

        if(ret)
        {
            list_head* toDel = position(i)->next;

            if(toDel == m_current)
            {
                m_current = toDel->next;
            }

            list_del(toDel);

            delete list_entry(toDel, Node, m_list_head);

            this->m_length--;
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = true;

        i = mod(i);

        ret &= ( (0 <= i) && (i < this->m_length) );

        if(ret)
        {
            list_entry(position(i)->next, Node, m_list_head)->value = e;
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = true;

        i = mod(i);

        ret &= ( (0 <= i) && (i < this->m_length) );

        if(ret)
        {
            e = list_entry(position(i)->next, Node, m_list_head)->value;
        }

        return ret;
    }

    T get(int i) const
    {
        T temp;

        if(get(i, temp))
        {
            return temp;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
        }

        return temp;
    }

    int find(const T& e) const
    {
        int ret = -1;
        int i = 0;

        list_head* slider;

        list_for_each(slider, &m_list_head)
        {
            if(list_entry(slider, Node, m_list_head)->value == e)
            {
                ret = i;
                break;
            }

            i++;
        }

        return ret;
    }

    bool move(int i, int step=1)
    {
        bool ret = true;

        i = mod(i);

        ret &= ((0<=i) && (i<this->m_length) && (step>0));

        if(ret)
        {
            m_current = position(i)->next;
            this->m_step = step;
        }

        return ret;
    }

    bool end() const
    {
        return (m_current == NULL) || (this->m_length == 0);
    }

    T current() const
    {
        if(!end())
        {
            return list_entry(m_current, Node, m_list_head)->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "no value in current position...");
        }
    }

    bool next()
    {
        int i = 0;

        while( (i<this->m_step) && (!end()) )
        {
            if(m_current != &m_list_head)
            {
                m_current = m_current->next;
                i++;
            }
            else
            {
                m_current = m_current->next;
            }

            if(m_current == &m_list_head)
            {
                m_current = m_current->next;
            }
        }

        return i == this->m_step;
    }

    bool pre()
    {
        int i = 0;

        while( (i<this->m_step) && (!end()) )
        {
            if(m_current != &m_list_head)
            {
                m_current = m_current->prev;
                i++;
            }
            else
            {
                m_current = m_current->prev;
            }

            if(m_current == &m_list_head)
            {
                m_current = m_current->prev;
            }
        }

        return i == this->m_step;
    }

    void clear()
    {
        while(this->m_length > 0)
        {
            remove(0);
        }
    }

    int length() const
    {
        return this->m_length;
    }

    ~DualCircleLinkList()
    {
        clear();
    }
};

}

#endif // DUALCIRCLELINKLIST_H
