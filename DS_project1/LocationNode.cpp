#include "LocationNode.h"
#include <cstring>
//#pragma warning(disable:4996)

LocationNode::LocationNode() 
{
	Location = nullptr;  pLeft = nullptr; pRight = nullptr;
	BST=new PatientBST;
	//memory allocation!
}

LocationNode::~LocationNode()
{
	delete[]Location;
}
/*RETURN*/
char * LocationNode::GetLoc()
{
	return this->Location;
}

PatientBST * LocationNode::GetBST()
{
	return this->BST;
}

LocationNode * LocationNode::GetLeft()
{
	return this->pLeft;
}

LocationNode * LocationNode::GetRight()
{
	return this->pRight;
}

/*SET*/
void LocationNode::SetLoc(const char * location)
{
	//memory allocation
	Location = new char[strlen(location) + 1];
	//setting loc
	strcpy(Location, location);
}

void LocationNode::SetLeft(LocationNode * node)
{
	this->pLeft = node;
}

void LocationNode::SetRight(LocationNode * node)
{
	this->pRight = node;
}
