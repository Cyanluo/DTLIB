#include <iostream>
#include <cstdlib>
#include "GTree.h"
#include "GTreeNode.h"
#include "DualCircleLinkList.h"
#include "LinkQueue.h"
#include "BTree.h"
#include "BTreeNode.h"
#include "DynamicArray.h"
#include "MatrixGraph.h"
#include "ListGraph.h"

using namespace std;
using namespace DTLib;

int main()
{
    ListGraph<char, int> graph;

    graph.addVertex('A');
    graph.addVertex('B');
    graph.addVertex('C');
    graph.addVertex('D');

    for(int i=0; i<graph.vCount(); i++)
    {
        cout << graph.getVertex(i) << " ";
    }

    cout << endl;

    graph.setEdge(0, 1, 10);
    graph.setEdge(0, 2, 8);
    graph.setEdge(1, 0, 4);
    graph.setEdge(1, 2, 3);
    graph.setEdge(2, 3, 3);

    cout << "vCount: " << graph.vCount() << endl;
    cout << "eCount: " << graph.eCount() << endl;
    cout << "ID(1): " << graph.ID(1) << endl;
    cout << "OD(1): " << graph.OD(1) << endl;
    cout << "TD(1): " << graph.TD(1) << endl;

    graph.removeEdge(1, 2);

    cout << "eCount: " << graph.eCount() << endl;
    cout << "ID(1): " << graph.ID(1) << endl;
    cout << "OD(1): " << graph.OD(1) << endl;

    SharedPointer< Array<int> > a = graph.getAdjacent(0);

    for(int i=0; i<a->length(); i++)
    {
        cout << (*a)[i] << " ";
    }

    cout << endl;

    graph.removeVertex();

    cout << "vCount: " << graph.vCount() << endl;
    cout << "eCount: " << graph.eCount() << endl;

    return 0;
}

/* GTree
 * GTree<int> test;
    GTreeNode<int> test2;
    test2.parent = NULL;
    test2.value = 0;
    test.insert(&test2);

    GTreeNode<int>* root = test.find(0);
    test.insert(1, root);
    test.insert(2, root);
    test.insert(3, root);

    root = test.find(1);
    test.insert(4, root);
    test.insert(5, root);
    test.insert(6, root);

    root = test.find(2);
    test.insert(7, root);
    test.insert(8, root);
    test.insert(9, root);

    root = test.find(3);
    test.insert(10, root);
    test.insert(11, root);
    test.insert(12, root);
    test.insert(13, root);

    cout << "count1: " << test.count() << endl;
    cout << "height1: " << test.height() << endl;
    cout << "degree1: " << test.degree() << endl;

    SharedPointer<Tree<int>> a = test.remove(2);

    root = dynamic_cast<GTreeNode<int>*>(a->find(8));

    while (root != NULL)
    {
        cout << root->value << " ";

        root = dynamic_cast<GTreeNode<int>*>(root->parent);
    }

    cout << endl;

    cout << "count2: " << test.count() << endl;
    cout << "height2: " << test.height() << endl;
    cout << "degree2: " << test.degree() << endl;

    for(test.begin(); !test.end(); test.next())
    {
        cout << test.current() << endl;
    }
 */

/* DualCircleLinkList
 * DualCircleLinkList<int> l;

    int j=0;

    for(int i=0; i<=5; i++)
    {
        l.insert(i);
    }

//    for(l.move(0); !l.end(); l.next())
//    {
//        cout << l.current() << endl;
//        j++;
//        if(j>10)
//        {
//            break;
//        }
//    }

    for(int i=0; i<=5; i++)
    {
        cout << l.get(i) << endl;
    }
 */

/*LinkQueue
 * LinkQueue<int> l;

    for(int i=0; i<5; i++)
    {
        l.add(i);
    }

    for(int i=0; i<5; i++)
    {
        cout << l.front() << endl;
        l.remove();
    }
 */

/* BTree
 * BTree<int> tree;

    tree.insert(0, NULL);

    TreeNode<int>* temp = tree.find(0);
    tree.insert(1, temp);
    tree.insert(2, temp);

    temp = tree.find(1);
    tree.insert(3, temp);
    tree.insert(4, temp);

    temp = tree.find(2);
    tree.insert(5, temp);
    tree.insert(6, temp);

    temp = tree.find(6);
    tree.insert(7, temp);
    tree.insert(8, temp);

    cout << "count:" << tree.count() << endl;
    cout << "height:" << tree.height() << endl;
    cout << "degree:" << tree.degree() << endl;

    temp = tree.find(6);
    tree.remove(temp);

    cout << "count:" << tree.count() << endl;
    cout << "height:" << tree.height() << endl;
    cout << "degree:" << tree.degree() << endl;

    int index[] = {3, 4, 5, 7, 8};

    for(int i=0; i<sizeof(index)/4; i++)
    {
        temp = tree.find(index[i]);

        while(temp)
        {
            cout << temp->value;

            temp = dynamic_cast<BTreeNode<int>*>(temp->parent);
        }
        cout  << endl;
    }

    cout << endl;

    for(tree.begin(); !tree.end(); tree.next())
    {
        cout << tree.current() << endl;
    }

    SharedPointer< Array<int> > array = tree.traversal(LevelOrder);
    cout << endl;

    for(int i=0; i<array->length(); i++)
    {
        cout << (*array)[i] << " ";
    }

    cout << endl;

    SharedPointer< BTree<int> > tclone = tree.clone();
    temp = tree.find(5);
    tree.insert(12, temp);

    for(int i=0; i<sizeof(index)/4; i++)
    {
        temp = tclone->find(index[i]);

        while(temp)
        {
            cout << temp->value;

            temp = dynamic_cast<BTreeNode<int>*>(temp->parent);
        }
        cout  << endl;
    }

    cout << endl;

    cout << "tclone == tree:" << (tree == *tclone) << endl;

    SharedPointer<BTree<int>> add_tree = tree.add(*tclone);

    for(add_tree->begin(); !add_tree->end(); add_tree->next())
    {
        cout << add_tree->current() << endl;
    }

    BTreeNode<int>* head = tree.thread(LevelOrder);

    while (head->right != NULL)
    {
        head = head->right;
    }

    while (head != NULL)
    {
        cout << head->value << " ";
        head = head->left;
    }

    cout << endl;
 */

/* MatrixGraph
 * MatrixGraph<3, int, int> graph;

    graph.setEdge(0, 1, 1);
    graph.setEdge(1, 0, 2);
    graph.setEdge(1, 2, 3);

    cout << "ID(1):" << graph.ID(1) << endl;
    cout << "OD(1):" << graph.OD(1) << endl;
    cout << "TD(1):" << graph.TD(1) << endl;
    cout << "vCount:" << graph.vCount() << endl;
    cout << "eCount:" << graph.eCount() << endl;

    cout << "edget(1,2):" << graph.getEdge(1, 2) << endl;

    graph.setEdge(0, 1, 30000);

    cout << "edget(0,1):" << graph.getEdge(0, 1) << endl;

    graph.removeEdge(0, 1);

    cout << "ID(1):" << graph.ID(1) << endl;
    cout << "OD(1):" << graph.OD(1) << endl;
    cout << "TD(1):" << graph.TD(1) << endl;
    cout << "vCount:" << graph.vCount() << endl;
    cout << "eCount:" << graph.eCount() << endl;

    SharedPointer< Array<int> > ad = graph.getAdjacent(1);

    for(int i=0; i<ad->length(); i++)
    {
        cout << (*ad)[i] << " ";
    }

    cout << endl;

    graph.setVertex(0, 100);

    cout << "vertex(0):" << graph.getVertex(0) << endl;

 */
