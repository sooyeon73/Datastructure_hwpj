#pragma once
#include "HeaderTable.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

class FPGrowth
{
private:
	int threshold;
	FPNode* fpTree; // FPTREE's root
	HeaderTable* table;

	//map<set<string>, int> frequenctPatterns;
	ofstream* fout; //for result.txt
	ofstream flog; //for log.txt
public:

	FPGrowth(ofstream*fout, int threshold) {
		this->threshold = threshold;
		flog.open("log.txt", ios::app);
		flog.setf(ios::fixed);
		fpTree = new FPNode; //fpTree's root
		table = new HeaderTable; // allocation
		this->fout = fout;
	}
	~FPGrowth();

	//create , insert
	void createTable(char* item, int frequency) { table->insertTable(item, frequency); }
	void createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency);
	void connectNode(HeaderTable* table, string item, FPNode* node);

	/*
	void frequenctPatternSetting() {
		table->ascendingIndexTable();
		frequenctPatterns = getFrequentPatterns(table, fpTree);
	}
	map<set<string>, int> getFrequentPatterns(HeaderTable* pTable, FPNode* pTree);
	void powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* flag, int depth);
	bool contains_single_path(FPNode* pNode);
	*/

	//find from item to frequency
	int item_frequency(string item) {return table->find_frequency(item);}
	//return variables
	FPNode* getTree() { return fpTree; }
	HeaderTable* getHeaderTable() { return table; }
	int getThreshold() { return threshold; }

	bool printList(); //PRINT_TIEMLIST
	bool printTree(); //PRINT_FPTREE

	//void saveFrequentPatterns();

	};


