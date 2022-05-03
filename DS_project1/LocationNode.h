#pragma once
#include "PatientBST.h"

class LocationNode
{
private:
	char * Location;
	PatientBST* BST; // link to BSTNode's root
	LocationNode * pLeft;
	LocationNode * pRight;

public:
	LocationNode();
	~LocationNode();

	char * GetLoc();
	PatientBST * GetBST();
	LocationNode * GetLeft();
	LocationNode * GetRight();

	void SetLoc(const char * location);
	void SetLeft(LocationNode * node);
	void SetRight(LocationNode * node);
};
