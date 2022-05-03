#include "PatientBSTNode.h"
//#pragma warning(disable:4996)
#include <cstring>

PatientBSTNode::PatientBSTNode()
{
	Name = NULL;  pLeft = NULL; pRight = NULL; Disease = 0;
}

PatientBSTNode::~PatientBSTNode()
{
}

/*RETURN*/
char * PatientBSTNode::GetName()
{
	return this->Name;
}

char PatientBSTNode::GetDisease()
{
	return this->Disease;
}

PatientBSTNode * PatientBSTNode::GetLeft()
{
	return this->pLeft;
}

PatientBSTNode * PatientBSTNode::GetRight()
{
	return this->pRight;
}

/*SETTING*/
void PatientBSTNode::SetName(char * name)
{
	// memory allocation
	Name = new char[strlen(name) + 1];
	//set name
	strcpy(Name, name);
}

void PatientBSTNode::SetDisease(char disease)
{
	Disease = disease;
}

void PatientBSTNode::SetLeft(PatientBSTNode * node)
{
	this->pLeft = node;
}

void PatientBSTNode::SetRight(PatientBSTNode * node)
{
	this->pRight = node;
}
