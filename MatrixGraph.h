#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"
#include "DynamicArray.h"

namespace DTLib
{

template < int N, typename V, typename E >
class MatrixGraph: public Graph<V, E>
{
protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_eCount;
public:
    MatrixGraph()
    {
        for(int i=0; i<vCount(); i++)
        {
            m_vertexes[i] = NULL;

            for(int j=0; j<vCount(); j++)
            {
                m_edges[i][j] = NULL;
            }
        }
    }

    V getVertex(int i)
    {
        V ret;

        if( !getVertex(i, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "no vertex in current index...");
        }

        return ret;
    }

    bool getVertex(int i, V& value)
    {
        bool ret = (0 <= i) && (i < vCount());

        if(ret)
        {
            if(m_vertexes[i] != NULL)
            {
                value = *(m_vertexes[i]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "no value assigned to this vertex...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "invalid parmeter i to get vertex...");
        }

        return ret;
    }

    bool setVertex(int i, const V& value)
    {
        bool ret = (0 <= i) && (i < vCount());

        if(ret)
        {
            V* data = m_vertexes[i];

            if(data == NULL)
            {
                data = new V();

                if(data == NULL)
                {
                    THROW_EXCEPTION(NoEnoughMemonyException, "no enough memory to create vertex...");
                }
                else
                {
                    *data = value;

                    m_vertexes[i] = data;
                }
            }
            else
            {
                *data = value;
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "invalid parmeter i to set vertex...");
        }

        return ret;
    }

    SharedPointer< Array<int> > getAdjacent(int i)
    {
        DynamicArray<int>* ret = NULL;
        int n = 0;

        if( (0 <= i) && (i < vCount()) )
        {
            for(int j=0; j<vCount(); j++)
            {
                if(m_edges[i][j] != NULL)
                {
                    n++;
                }
            }

            ret = new DynamicArray<int>(n);

            if(ret != NULL)
            {
                for(int m=0, k=0; m<vCount(); m++)
                {
                    if(m_edges[i][m] != NULL)
                    {
                        ret->set(k++, m);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemonyException, "no enough to create reture array...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "invalid parmeter i to get adjacent...");
        }

        return ret;
    }

    bool isAdjacent(int i, int j)
    {
        return (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) && (m_edges[i][j] != NULL);
    }

    E getEdge(int i, int j)
    {
        E ret;

        if( !getEdge(i, j, ret) )
        {
            THROW_EXCEPTION(InvalidParameterException, "invalid parmeter <i, j>...");
        }

        return ret;
    }

    bool getEdge(int i, int j, E& value)
    {
        bool ret = (0 <= i) && (i < vCount()) && \
                   (0 <= j) && (j < vCount());

        if(ret)
        {
            if(m_edges[i][j] != NULL)
            {
                value = *(m_edges[i][j]);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "no value assigned to this edge...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "invalid parmeter <i, j>...");
        }

        return ret;
    }

    bool setEdge(int i, int j, const E& value)
    {
        bool ret = (0 <= i) && (i < vCount()) && \
                   (0 <= j) && (j < vCount());

        if(ret)
        {
            E* data = m_edges[i][j];

            if(data != NULL)
            {
                *data = value;
            }
            else
            {
                data = new E();

                if(data != NULL)
                {
                    *data = value;

                    m_edges[i][j] = data;

                    m_eCount++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemonyException, "no enough to create edge...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "invalid parmeter <i, j>...");
        }

        return ret;
    }

    bool removeEdge(int i, int j)
    {
        bool ret = (0 <= i) && (i < vCount()) && \
                   (0 <= j) && (j < vCount());

        if(ret)
        {
            E* toDel = m_edges[i][j];

            m_edges[i][j] = NULL;

            m_eCount--;

            delete toDel;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "invalid parmeter <i, j>...");
        }

        return ret;
    }

    int vCount()
    {
        return N;
    }

    int eCount()
    {
        return m_eCount;
    }

    int OD(int i)
    {
        int ret = 0;

        if( (0 <= i) && (i < vCount()) )
        {
            for(int j=0; j<vCount(); j++)
            {
                if( m_edges[i][j] != NULL )
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "invalid parmeter i...");
        }

        return ret;
    }

    int ID(int i)
    {
        int ret = 0;

        if( (0 <= i) && (i < vCount()) )
        {
            for(int j=0; j<vCount(); j++)
            {
                if( m_edges[j][i] != NULL )
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "invalid parmeter i...");
        }

        return ret;
    }

    ~MatrixGraph()
    {
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<N; j++)
            {
                delete m_edges[i][j];
            }

            delete m_vertexes[i];
        }
    }
};

}

#endif // MATRIXGRAPH_H
