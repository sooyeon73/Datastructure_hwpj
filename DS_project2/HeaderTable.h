#pragma once
#include "FPNode.h"
#include <list>

class HeaderTable
{
private:
	list<pair<int, string> > indexTable;
	map<string, FPNode*> dataTable;
public:
	HeaderTable() { }
	~HeaderTable();
	void insertTable(char* item, int frequency);
	//insert item in both table

	//return variables
	list<pair<int, string>> getindexTable() { return indexTable; }
	map<string, FPNode*> getdataTable() { return dataTable; }
	FPNode* getNode(string item) { return dataTable.find(item)->second; }

	//sorting
	void descendingIndexTable() { indexTable.sort(greater<pair<int, string>>()); }
	void ascendingIndexTable() { indexTable.sort(); }

	//find from item to frequency
	int find_frequency(string item);
};


