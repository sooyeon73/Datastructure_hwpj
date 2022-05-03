#pragma once
#include "PatientBSTNode.h"
#include "PatientNode.h"
#include <fstream>
#include <queue>
using namespace std;

class PatientBST
{
private:
	PatientBSTNode* P_Root;

public:
	PatientBST();
	~PatientBST();

	PatientBSTNode * GetRoot();
	void Insert(PatientNode * node);
	PatientBSTNode* Search(PatientBSTNode*root, const char * name);
	void Delete( char* name);
	void Print_PRE(PatientBSTNode * node);
	void Print_IN(PatientBSTNode * node);
	void Print_POST(PatientBSTNode * node);
	void Print_LEVEL();

};
