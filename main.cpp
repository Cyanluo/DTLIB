#include <iostream>
#include <cstdlib>
#include "GTree.h"
#include "GTreeNode.h"
#include "DualCircleLinkList.h"
#include "LinkQueue.h"

using namespace std;
using namespace DTLib;


int main()
{
    LinkQueue<int> l;

    for(int i=0; i<5; i++)
    {
        l.add(i);
    }

    for(int i=0; i<5; i++)
    {
        cout << l.front() << endl;
        l.remove();
    }

    return 0;
}

/* tree
    GTree<int> test;
    GTreeNode<int> test2;
    test2.parent = NULL;
    test2.value = 0;
    test.insert(&test2);

    GTreeNode<int>* root = test.find(0);
    test.insert(1, root);
    test.insert(5, root);
    test.insert(9, root);

    root = test.find(1);
    test.insert(2, root);
    //test.insert(3, root);
    test.insert(4, root);

    root = test.find(5);
    test.insert(6, root);
    root = test.find(6);
    test.insert(7, root);
    root = test.find(7);
    test.insert(8, root);

    root = test.find(9);
    test.insert(10, root);
    //test.insert(11, root);
    test.insert(12, root);

    cout << "count1: " << test.count() << endl;
    cout << "height1: " << test.height() << endl;
    cout << "degree1: " << test.degree() << endl;

    SharedPointer<Tree<int>> a = test.remove(5);

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

    for(int i=0; i<3; i++)
    {
        root = test.find(i*4 + 4);

        while (root != NULL)
        {
            cout << root->value << " ";

            root = dynamic_cast<GTreeNode<int>*>(root->parent);
        }

        cout << endl;
    }

    return 0;

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

