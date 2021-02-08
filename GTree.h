#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"

#include <iostream>

namespace DTLib
{

template <typename T>
class GTree: public Tree<T>
{
protected:
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
                {
                    ret = find(node->child.current(), value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node, GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret = NULL;

        if(node == obj)
        {
            return node;
        }
        else
        {
            if(node != NULL)
            {
                for(node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
                {
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }

    void free(GTreeNode<T>* node)
    {
        if(node != NULL)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                free(node->child.current());
            }

            if(node->flag())
            {
                delete node;
            }
        }
    }

    void remove(GTreeNode<T>* node, GTree<T>*& ret)
    {
        ret = new GTree<T>();

        if(ret == NULL)
        {
            THROW_EXCEPTION(NoEnoughMemonyException, "no  memary to create tree...");
        }
        else
        {
            if(node == root())
            {
                this->m_root = NULL;
            }
            else
            {
                LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;

                child.remove(child.find(node));

                node->parent = NULL;
            }

            ret->m_root = node;
        }
    }

    int count(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = 1;

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int temp = height(node->child.current());

                if(temp > ret)
                {
                    ret = temp;
                }
            }

            ret += 1;
        }

        return ret;
    }

    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = node->child.length();

            for(node->child.move(0); !node->child.end(); node->child.next())
            {
                int temp = degree(node->child.current());

                if(temp > ret)
                {
                    ret = temp;
                }
            }
        }

        return ret;
    }
public:
    bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        if(node != NULL)
        {
            if(root() == NULL)
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                GTreeNode<T>* np = find(node->parent);

                if(np != NULL)
                {
                    GTreeNode<T>* temp = dynamic_cast<GTreeNode<T>*>(node);

                    if(np->child.find(temp) < 0)
                    {
                        np->child.insert(temp);
                    }
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Invalid tree node parameter...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = true;

        GTreeNode<T>* node = GTreeNode<T>::NewNode();
        node->parent = parent;
        node->value = value;

        insert(node);

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        GTree<T>* ret = NULL;

        GTreeNode<T>* node = find(value);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "No such treenode in this tree...");
        }
        else
        {
            remove(node, ret);
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;

        node = find(node);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "No such treenode in this tree...");
        }
        else
        {
            remove(dynamic_cast<GTreeNode<T>*>(node), ret);
        }

        return ret;
    }

    GTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        free(root());

        this->m_root = NULL;
    }

    ~GTree()
    {
        clear();
    }
};

}

#endif // GTREE_H
