#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"


namespace DTLib
{

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};

template < typename T >
class BTree: public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue;

    BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const
    {
        BTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)
            {
                ret = node;
            }
            else
            {
                if(ret == NULL)
                {
                    ret = find(node->left, value);
                }

                if(ret == NULL)
                {
                    ret = find(node->right, value);
                }
            }
        }

        return ret;
    }

    BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = NULL;

        if(node == obj)
        {
            ret = node;
        }
        else
        {
            if(node != NULL)
            {
                if(ret == NULL)
                {
                    ret = find(node->left, obj);
                }

                if(ret == NULL)
                {
                    ret = find(node->right, obj);
                }
            }
        }

        return ret;
    }

    bool insert(BTreeNode<T>* parent, BTreeNode<T>* n, BTNodePos pos)
    {
        bool ret = true;

        if(this->m_root == NULL)
        {
            n->parent = NULL;
            this->m_root = n;
        }
        else
        {
            if(parent != NULL)
            {
                if(pos == ANY)
                {
                    if(parent->left == NULL)
                    {
                        parent->left = n;
                    }
                    else if(parent->right == NULL)
                    {
                        parent->right = n;
                    }
                    else
                    {
                        ret = false;
                    }
                }
                else if(pos == LEFT)
                {
                    if(parent->left == NULL)
                    {
                        parent->left = n;
                    }
                    else
                    {
                        ret = false;
                    }
                }
                else if(pos == RIGHT)
                {
                    if(parent->right == NULL)
                    {
                        parent->right = n;
                    }
                    else
                    {
                        ret = false;
                    }
                }
                else
                {
                    ret = false;
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "Invalid btree parent node...");
            }
        }

        return ret;
    }

    void remove(BTreeNode<T>* node, BTree<T>*& ret)
    {
        ret = new BTree<T>;

        if(ret != NULL)
        {
            if(node == this->m_root)
            {
                node->parent = NULL;
                ret->m_root = node;
                this->m_root = NULL;
            }
            else
            {
                BTreeNode<T>* parent = find(node->parent);

                if(parent != NULL)
                {
                    if(parent->left == node)
                    {
                        parent->left = NULL;
                    }
                    else if(parent->right == node)
                    {
                        parent->right = NULL;
                    }

                    node->parent = NULL;

                    ret->m_root = node;
                }
                else
                {
                    THROW_EXCEPTION(InvalidParameterException, "Invalid btreenode to remove...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemonyException, "no enough memory to create btree");
        }
    }

    void free(BTreeNode<T>* node)
    {
        if(node != NULL)
        {
            free(node->left);
            free(node->right);

            if(node->flag())
            {
                delete node;
            }
        }
    }

    int count(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = 1;

            ret += count(node->left);
            ret += count(node->right);
        }

        return ret;
    }

    int height(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = 1;

            int temp1 = height(node->left);
            int temp2 = height(node->right);

            if(temp1 > temp2)
            {
                ret += temp1;
            }
            else
            {
                ret += temp2;
            }
        }

        return ret;
    }

    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            if(node->left != NULL)
            {
                ret++;
            }

            if(node->right != NULL)
            {
                ret++;
            }

            int temp1 = degree(node->left);
            int temp2 = degree(node->right);

            if(temp1 > ret)
            {
                ret = temp1;
            }
            else if(temp2 > ret)
            {
                ret = temp2;
            }
        }

        return ret;
    }

    void preOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != NULL)
        {
            queue.add(node);
            preOrderTraversal(node->left, queue);
            preOrderTraversal(node->right, queue);
        }
    }

    void inOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != NULL)
        {
            inOrderTraversal(node->left, queue);
            queue.add(node);
            inOrderTraversal(node->right, queue);
        }
    }

    void postOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != NULL)
        {
            postOrderTraversal(node->left, queue);
            postOrderTraversal(node->right, queue);
            queue.add(node);
        }
    }

    void leverOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
    {
        if(node != NULL)
        {
            LinkQueue<BTreeNode<T>*> tmp;

            tmp.add(node);

            while (tmp.length() > 0)
            {
                BTreeNode<T>* front = tmp.front();

                tmp.remove();

                queue.add(front);

                if(front->left != NULL)
                {
                    tmp.add(front->left);
                }

                if(front->right != NULL)
                {
                    tmp.add(front->right);
                }
            }
        }
    }

    BTreeNode<T>* clone(BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            ret = BTreeNode<T>::NewNode();

            ret->value = node->value;

            ret->left = clone(node->left);
            ret->right = clone(node->right);

            if(ret->left != NULL)
            {
                ret->left->parent = node;
            }

            if(ret->right != NULL)
            {
                ret->right->parent = node;
            }
        }

        return ret;
    }

    bool equal(const BTreeNode<T>* lt, const BTreeNode<T>* rt) const
    {
        bool ret = true;

        if(lt == NULL && rt != NULL)
        {
            ret = false;
        }
        else if(lt != NULL && rt == NULL)
        {
            ret = false;
        }
        else if(lt != NULL && rt != NULL)
        {
            ret &= (lt->value == rt->value);

            ret &= equal(lt->left, rt->left);
            ret &= equal(lt->right, rt->right);
        }

        return ret;
    }

    BTreeNode<T>* add(BTreeNode<T>* lt, BTreeNode<T>* rt) const
    {
        BTreeNode<T>* ret = NULL;

        if(lt == NULL && rt != NULL)
        {
            ret = clone(rt);
        }
        else if(lt != NULL && rt == NULL)
        {
            ret = clone(lt);
        }
        else if(lt != NULL && rt != NULL)
        {
            ret = BTreeNode<T>::NewNode();

            if(ret != NULL)
            {
                ret->value = lt->value + rt->value;

                ret->left = add(lt->left, rt->left);
                ret->right = add(lt->right, rt->right);
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemonyException, "no enough memory to create btreenode...");
            }
        }

        return ret;
    }

    void traversal(BTTraversal order, LinkQueue<BTreeNode<T>*>& queue)
    {
        switch (order)
        {
            case PreOrder:
                preOrderTraversal(root(), queue);
                break;
            case InOrder:
                inOrderTraversal(root(), queue);
                break;
            case PostOrder:
                postOrderTraversal(root(), queue);
                break;
            case LevelOrder:
                leverOrderTraversal(root(), queue);
                break;
            default:
                THROW_EXCEPTION(InvalidParameterException, "invalid order type...");
                break;
        }
    }

    BTreeNode<T>* connect(LinkQueue<BTreeNode<T>*>& queue)
    {
        BTreeNode<T>* ret = NULL;

        if(queue.length() > 0)
        {
            BTreeNode<T>* slider = queue.front();

            ret = slider;

            slider->left = NULL;
            queue.remove();

            while(queue.length() > 0)
            {
                slider->right = queue.front();

                queue.front()->left = slider;

                slider = queue.front();

                queue.remove();
            }

            slider->right = NULL;
        }

        return ret;
    }
public:
    bool insert(TreeNode<T>* node)
    {
        return insert(node, ANY);
    }

    virtual bool insert(TreeNode<T>* node, BTNodePos pos)
    {
        bool ret = true;

        if(node != NULL)
        {
            BTreeNode<T>* parent = find(node->parent);

            ret = insert(parent, dynamic_cast<BTreeNode<T>*>(node), pos);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Invalid btree node parameter...");
        }

        return ret;
    }

    bool insert(const T& value, TreeNode<T>* parent)
    {
        return insert(value, parent, ANY);
    }

    virtual bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
    {
        bool ret = true;

        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if(node != NULL)
        {
            node->parent = find(parent);
            node->value = value;

            ret = insert(dynamic_cast<BTreeNode<T>*>(node->parent), node, pos);

            if(!ret)
            {
                delete node;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemonyException, "no enough memory to create btreenode...");
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(const T& value)
    {
        BTree<T>* ret = NULL;

        BTreeNode<T>* node = find(value);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "No such treenode in this tree...");
        }
        else
        {
            remove(node, ret);

            m_queue.clear();
        }

        return ret;
    }

    SharedPointer< Tree<T> > remove(TreeNode<T>* node)
    {
        BTree<T>* ret = NULL;

        node = find(node);

        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParameterException, "No such treenode in this tree...");
        }
        else
        {
            remove(dynamic_cast<BTreeNode<T>*>(node), ret);

            m_queue.clear();
        }

        return ret;
    }

    BTreeNode<T>* find(const T& value) const
    {
        return find(root(), value);
    }

    BTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
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

        m_queue.clear();
    }

    bool begin()
    {
        bool ret = true;

        if(this->m_root != NULL)
        {
            m_queue.clear();
            m_queue.add(root());
        }
        else
        {
            ret = false;
        }

        return ret;
    }

    bool end()
    {
        return (this->m_root == NULL) || (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = true;

        if(!end())
        {
            BTreeNode<T>* current = m_queue.front();

            m_queue.remove();

            if(current->left != NULL)
            {
                m_queue.add(current->left);
            }
            if(current->right != NULL)
            {
                 m_queue.add(current->right);
            }
        }
        else
        {
            ret = false;
        }

        return ret;
    }

    T current()
    {
        if(!end())
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "no btreenode in current positon...");
        }
    }

    virtual SharedPointer< Array<T> > traversal(BTTraversal order)
    {
        LinkQueue<BTreeNode<T>*> queue;

        traversal(order, queue);

        DynamicArray<T>* ret = new DynamicArray<T>(queue.length());

        if(ret != NULL)
        {
            for(int i=0; i<ret->length(); i++, queue.remove())
            {
                ret->set(i, queue.front()->value);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemonyException, "no memory to create return array...");
        }

        return ret;
    }

    virtual SharedPointer< BTree<T> > clone() const
    {
        BTree<T>* ret = new BTree<T>;

        if(ret != NULL)
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemonyException, "no enough memory to clone btree...");
        }

        return ret;
    }

    virtual bool operator == (const BTree<T>& rt) const
    {
        return equal(root(), rt.root());
    }

    virtual bool operator != (const BTree<T>& rt) const
    {
        return !(root() == rt.root());
    }

    virtual SharedPointer< BTree<T> > add(BTree<T>& rt) const
    {
        BTree<T>* ret = new BTree<T>;

        if(ret != NULL)
        {
            ret->m_root = add(root(), rt.root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemonyException, "no enough memory to create btree...");
        }

        return ret;
    }

    virtual BTreeNode<T>* thread(BTTraversal order)
    {
        BTreeNode<T>* ret = NULL;

        if(this->m_root != NULL)
        {
            LinkQueue<BTreeNode<T>*> queue;

            traversal(order, queue);

            ret = connect(queue);

            this->m_root = NULL;

            m_queue.clear();
        }

        return ret;
    }

    ~BTree()
    {
        clear();
    }
};

}

#endif // BTREE_H
