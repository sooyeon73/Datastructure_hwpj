#pragma once
#include "FPGrowth.h"
#include "BpTree.h"

class Manager
{
private:
	char* cmd; //for command
	FPGrowth* fpgrowth; 
	BpTree* bptree;

public:
	Manager(int threshold, int bpOrder)	//constructor
	{
		//allocation
		fpgrowth = new FPGrowth(&flog,threshold);
		cmd = new char[20];
	}


	~Manager()//destructor
	{
		delete[]cmd;
	}

	ifstream fin; //for command.txt open
	ifstream fin2; //for market.txt open
	ofstream flog; //for log.txt write
	

	void run(const char* command);
	//function
	bool LOAD(); // fpgrowth create
	bool BTLOAD(); //bptree create
	bool PRINT_ITEMLIST(); //print headertable
	bool PRINT_FPTREE(); //print fptree
	bool PRINT_RANGE(char* item, int start, int end);
	bool PRINT_CONFIDENCE(char* item, double rate);
	bool PRINT_MIN(char* item, int min_frequency);


	void printErrorCode(int n);
	void printSuccessCode();

};

