#include "LocationHeapNode.h"
//#pragma warning(disable:4996)

LocationHeapNode::LocationHeapNode()
{
	Location = NULL; Count = 0;
}

LocationHeapNode::~LocationHeapNode()
{
	delete[]Location;
}

int LocationHeapNode::GetCount()
{
	return this->Count;
}

char * LocationHeapNode::GetLoc()
{
	return this->Location; //return location
}

void LocationHeapNode::SetCount(int count)
{
	Count = count; //set new count
}

void LocationHeapNode::SetLoc(char * location)
{
	//memory allocaiton
	Location = new char[strlen(location) + 1];
	//set loc
	strcpy(Location, location);
}

