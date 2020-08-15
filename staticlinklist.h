#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "linklist.h"

namespace DTLib
{

template < typename T, int N>
class StaticLinkList:public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    struct SNode:public Node
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void)size;
            return loc;
        }
    };

    char m_space[N * sizeof (SNode)];
    char m_used[N];

    Node* create()
    {
        SNode* ret = NULL;

        for(int i=0; i<N; i++)
        {
            if(!m_used[i])
            {
                SNode* space = reinterpret_cast<SNode*>(m_space);

                ret = space + i;

                ret = new(ret)SNode();

                m_used[i] = 1;

                break;
            }
        }

        return ret;
    }

    void destory(Node* pn)
    {
        SNode* psn = dynamic_cast<SNode*>(pn);
        SNode* space = reinterpret_cast<SNode*>(m_space);

        for(int i=0; i<N; i++)
        {
            if(psn == (space + i))
            {
                m_used[i] = 0;

                psn->~SNode();

                break;
            }
        }
    }
public:
    StaticLinkList()
    {
        for(int i=0; i<N; i++)
        {
            m_used[i] = 0;
        }
    }

    ~StaticLinkList()
    {
        this->clear();
    }
};

}

#endif // STATICLINKLIST_H
