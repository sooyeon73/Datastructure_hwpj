#pragma once
#include "LocationNode.h"
#include "PatientNode.h"
#include <iostream>
using namespace std;

class LocationBST
{
private:
	LocationNode * Root;

public:
	LocationBST();
	~LocationBST();

	LocationNode * GetRoot();
	void Insert_Location();
	void Insert_Patient(PatientNode * node);
	LocationNode* Search(LocationNode* root,const char * name); // location name-> location search
	PatientBSTNode* Search2(LocationNode* root, const char* name); // patient name -> search patient
	LocationNode* Search3(LocationNode* root, const char* name); // patient name -> search location Node

	void Delete(LocationNode* node, char* name);
	void Print_PRE(LocationNode* node);
	void Print_IN(LocationNode* node);
	void Print_POST(LocationNode* node);
	void Print_LEVEL();
};	
