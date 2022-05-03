#pragma once
#include "LocationHeapNode.h"
#include <fstream>
using namespace std;

class LocationHeap
{
private:
	LocationHeapNode ** Heap; // element array
	int size; // heapnode count

public:
	LocationHeap();
	~LocationHeap();

	bool Insert(char * location);
	void Print();
	int GetSize();
};
