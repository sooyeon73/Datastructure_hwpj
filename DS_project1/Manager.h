#pragma once
#include "PatientNode.h"
#include "LocationBST.h"
#include "LocationHeap.h"

class Manager
{
private:
	/*ALLOCATION*/
	queue <PatientNode*>* ds_queue = new queue <PatientNode*>;
	LocationBST* ds_bst = new LocationBST;
	LocationHeap * ds_heap = new LocationHeap;
	ifstream fin; //for command
	ifstream finn; //for data
	ofstream flog; //for log.txt

public:
	Manager();
	~Manager();

	void run(const char * command);
	bool LOAD();
	bool ADD();
	bool QPOP();
	bool SEARCH();
	bool PRINT();
	bool BPOP();

	void PrintErrorCode(int num);
	void PrintSuccess(const char * act);
};
