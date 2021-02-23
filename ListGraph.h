#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Object.h"
#include "Graph.h"
#include "LinkList.h"
#include "DynamicArray.h"

namespace DTLib
{

template < typename V, typename E >
class ListGraph: public Graph<V, E>
{
protected:
    struct Vertex: public Object
    {
        V* data;
        LinkList< Edge<E> > edge;

        Vertex()
        {
            data = NULL;
        }
    };

    LinkList<Vertex*> m_list;
public:
    ListGraph(unsigned int n = 0)
    {
        for(unsigned int i=0; i<n; i++)
        {
            addVertex();
        }
    }

    int addVertex()
    {
        int ret = -1;

        Vertex* v = new Vertex();

        if(v != NULL)
        {
            m_list.insert(v);

            ret = m_list.length() - 1;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemonyException, "no memory to create new veertex...");
        }

        return ret;
    }

    int addVertex(const V& value)
    {
        int ret = addVertex();

        if(ret >= 0)
        {
            setVertex(ret, value);
        }

        return ret;
    }

    bool setVertex(int i, const V& value)
    {
        bool ret = (0 <= i) && (i < vCount());

        if(ret)
        {
            Vertex* v = m_list.get(i);

            V* data = v->data;

            if(data == NULL)
            {
                data = new V;
            }

            if(data != NULL)
            {
                *data = value;

                v->data = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemonyException, "no memory to create new veertex data...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "invalid parameter i...");
        }

        return ret;
    }

    V getVertex(int i)
    {
        V ret;

        if( !getVertex(i, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "invalid parameter i...");
        }

        return ret;
    }

    bool getVertex(int i, V& value)
    {
        bool ret = (0 <= i) && (i < vCount());

        if( ret )
        {
            Vertex* v = m_list.get(i);

            if(v->data != NULL)
            {
                value = *(v->data);
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "no value assigned to this vertex...");
        }

        return ret;
    }

    void removeVertex()
    {
        if( m_list.length() > 0 )
        {
            int index = m_list.length() - 1;
            Vertex* toDel = m_list.get(index);

            m_list.remove(index);

            for(int i=(m_list.move(0), 0); !m_list.end(); m_list.next(), i++)
            {
                int pos = m_list.current()->edge.find(Edge<E>(i, index));

                if(pos >= 0)
                {
                    m_list.current()->edge.remove(pos);
                }
            }

            delete toDel->data;
            delete toDel;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No vertex in current graph ...");
        }
    }

    SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* ret;

        if( (0 <= i) && (i <= vCount()) )
        {
            Vertex* v = m_list.get(i);

            ret = new DynamicArray<int>(v->edge.length());

            if(ret != NULL)
            {
                for(int i=(v->edge.move(0), 0); !v->edge.end(); v->edge.next(), i++)
                {
                    ret->set(i, v->edge.current().e);
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemonyException, "No memory to create return object ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Invalid parameter i ...");
        }

        return ret;
    }

    bool isAdjacent(int i, int j)
    {
        return (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) && (m_list.get(i)->edge.find(Edge<E>(i, j)) >= 0);
    }

    E getEdge(int i, int j)
    {
        E ret;

        if( !getEdge(i, j, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "Invalid parameter Edge<i, j> ...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E& value)
    {
        bool ret = (0 <= i) && (i <= vCount()) && \
                   (0 <= j) && (j <= vCount());

        if(ret)
        {
            Vertex* v = m_list.get(i);

            int pos = v->edge.find(Edge<E>(i, j));

            if(pos >= 0)
            {
                value = v->edge.get(pos).data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "Do not have this edge ...");
            }
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)
    {
        bool ret = (0 <= i) && (i <= vCount()) && \
                   (0 <= j) && (j <= vCount());

        if(ret)
        {
            Vertex* v = m_list.get(i);

            int pos = v->edge.find(Edge<E>(i, j));

            if(pos >= 0)
            {
                v->edge.set(pos, Edge<E>(i, j, value));
            }
            else
            {
                v->edge.insert(0, Edge<E>(i, j, value));
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Invalid parameter Edge<i, j> ...");
        }

        return ret;
    }

    bool removeEdge(int i, int j)
    {
        bool ret = (0 <= i) && (i <= vCount()) && \
                   (0 <= j) && (j <= vCount());

        if(ret)
        {
            Vertex* v = m_list.get(i);

            int pos = v->edge.find(Edge<E>(i, j));

            if(pos >= 0)
            {
                v->edge.remove(pos);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No such edge in this graph ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Invalid parameter Edge<i, j> ...");
        }

        return ret;
    }

    int vCount()
    {
        return m_list.length();
    }

    int eCount()
    {
        int ret = 0;

        for(m_list.move(0); !m_list.end(); m_list.next())
        {
            ret += m_list.current()->edge.length();
        }

        return ret;
    }

    int OD(int i)
    {
        int ret = 0;

        if( (0 <= i) && (i <= vCount()) )
        {
            ret = m_list.get(i)->edge.length();
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Invalid parameter i ...");
        }

        return ret;
    }

    int ID(int i)
    {
        int ret = 0;

        if( (0 <= i) && (i <= vCount()) )
        {
            for(int j=(m_list.move(0), 0); !m_list.end(); m_list.next(), j++)
            {
                int pos = m_list.current()->edge.find(Edge<E>(j, i));

                if(pos >= 0)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Invalid parameter i ...");
        }

        return ret;
    }

    ~ListGraph()
    {
        if( m_list.length() > 0 )
        {
            Vertex* toDel = m_list.get(0);

            m_list.remove(0);

            delete toDel->data;
            delete toDel;
        }
    }
};

}

#endif // LISTGRAPH_H
