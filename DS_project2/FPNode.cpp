#include "FPNode.h"

FPNode::FPNode()	//constructor
{
	//initialize
	parent = NULL;
	next = NULL;
	//allocation
	item = new char[40]; memset(item, 0, 40);
	frequency = 0;
}

FPNode::~FPNode()//destructor
{
	delete[]item;
}

FPNode* FPNode::getChildrenNode(string item) {
	//finding node from item
	map<string, FPNode*>::iterator it = children.find(item);
	if (it == children.end()) return NULL;
	FPNode* findNode = it->second;
	return findNode;
}
