#include "LocationHeap.h"
#include <fstream>
#include <algorithm>
//#pragma warning(disable:4996)


LocationHeap::LocationHeap()
{
    size = 0;  // initial state
    // * MEMORY ALLOCATION * //
    Heap = new LocationHeapNode * [7];
    for (int i = 0; i < 7; i++)
    {
        Heap[i] = new LocationHeapNode;
    } 
}


LocationHeap::~LocationHeap()
{
    delete[] *Heap;
}

bool LocationHeap::Insert(char * location)
{

    int i = 0;
    bool flag=false;

    while (i < size) // FIND same location Node
    {
        if (strcmp(Heap[i]->GetLoc(), location) == 0) //  IF location HeapNode always exists
        {
            Heap[i]->SetCount(Heap[i]->GetCount() + 1); // heapnode's count ++!
           
            //RE-SORTING
            for (int k = 1; k < size; k++)
            {
                int n = k; //child
                do {
                    int root = (n - 1) / 2;  //parent
                    //if parent<child
                    if (Heap[root]->GetCount() < Heap[n]->GetCount()) { 
                        //swap!
                        int temp = Heap[root]->GetCount();
                        Heap[root]->SetCount( Heap[n]->GetCount());
                        Heap[n]->SetCount(temp);

                        char* temp2 = new char[10];
                        strcpy(temp2,Heap[root]->GetLoc());
                        Heap[root]->SetLoc(Heap[n]->GetLoc());
                        Heap[n]->SetLoc(temp2);
                        delete[] temp2;                        
                    }
                    n = root;
                } while (n != 0);
          }
            
            flag = true;
            break; // stop loop
        }
        i++;
    }
    // new location!
    if (flag == false)
    {
        Heap[size]->SetLoc(location); //setting location
        Heap[size++]->SetCount(1); //count=1
    }
    return true;
}
int LocationHeap::GetSize()
{
    return size; //return size
}
void LocationHeap::Print()
{
    ofstream flog;
   flog.open("log.txt", ios::app);

   //PRINT LEVEL ORDER
    for (int i=0;i<size;i++)
    {
        flog << Heap[i]->GetCount() << "/" << Heap[i]->GetLoc() << endl;
   }
}
