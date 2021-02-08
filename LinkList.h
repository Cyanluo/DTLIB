#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Object.h"
#include "Exception.h"

namespace DTLib
{

template < typename T >
class LinkList:public List<T>
{
protected:
    struct Node:public Object
    {
        T value;
        Node* next;
    };

    mutable struct:public Object
    {
        char reserve[sizeof (T)];
        Node* next;
    }m_header;

    int m_length;

    Node* m_current;

    int m_step;

    Node* position(int i)const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);

        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }

        return ret;
    }

    virtual Node* create()
    {
        return new Node;
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
    }
public:
    LinkList()
    {
        m_header.next = NULL;
        m_current = NULL;
        m_length = 0;
        m_step = 1;
    }

    bool insert(const T& e)
    {
        return insert(m_length, e);
    }

    bool insert(int i, const T& e)
    {
        bool ret = ( (0 <= i) && (i <= m_length) );

        if(ret)
        {
            Node* node = create();

            if(node != NULL)
            {
                node->value = e;

                Node* current = position(i);

                node->next = current->next;

                current->next = node;

                m_length++;
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
        bool ret = ( (0 <= i) && (i < m_length) );

        if(ret)
        {
            Node* current = position(i);

            Node* toDel = current->next;

            if( m_current == toDel )
            {
                m_current = toDel->next;
            }

            current->next = toDel->next;

            m_length--;

            destroy(toDel);
        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = ( (0 <= i) && (i < m_length) );

        if(ret)
        {
            position(i)->next->value = e;
        }

        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = ( (0 <= i) && (i < m_length) );

        if(ret)
        {
            e = position(i)->next->value;
        }

        return ret;
    }

    virtual T get(int i) const
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

        Node* current = m_header.next;

        while(current)
        {
            if(current->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                current = current->next;
                i++;
            }
        }

        return ret;
    }

    virtual bool move(int i, int step=1)
    {
        bool ret = ((0<=i) && (i<m_length) && (step>0));

        if(ret)
        {
            m_current = position(i)->next;
            m_step = step;
        }

        return ret;
    }

    virtual bool end()
    {
        return (m_current == NULL);
    }

    T current()
    {
        if(!end())
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "no value in current position...");
        }
    }

    virtual bool next()
    {
        int i = 0;

        while((!end()) && i<m_step)
        {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        Node* current = reinterpret_cast<Node*>(&m_header);

        while(current->next)
        {
            Node* toDel = current->next;

            if( m_current == toDel )
            {
                m_current = toDel->next;
            }

            current->next = toDel->next;

            m_length--;

            destroy(toDel);
        }
    }

    ~LinkList()
    {
        clear();
    }
};

}

#endif // LINKLIST_H
