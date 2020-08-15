#include <iostream>
#include <cstdlib>
#include "Sort.h"

using namespace std;
using namespace DTLib;


int main()
{
    int array[] = {2, 1, 4, 3, 6, 4};

    Sort::Insert(array, 6);

    for(int i=0; i<6; i++)
    {
        cout << array[i] << endl;
    }

    return 0;
}
