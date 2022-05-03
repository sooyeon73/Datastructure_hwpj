#include "PatientNode.h"
//#pragma warning(disable:4996)

PatientNode::PatientNode()
 {}

PatientNode::~PatientNode()
{
	delete[]Name;
	delete[]Location;
}
/*RETURN*/
char * PatientNode::GetName()
{
	return Name;
}

float PatientNode::GetTemp()
{
	return Temperature;
}

const char PatientNode::GetCough()
{
	return Cough;
}

char * PatientNode::GetLoc()
{
	return Location;
}
/*SETTING*/
void PatientNode::SetName(char * name)
{
	Name = new char[strlen(name) + 1]; // dynamic allocation 
	strcpy(Name,name); 
}

void PatientNode::SetTemp(float temp)
{
	Temperature = temp;
}

void PatientNode::SetCough(char cough)
{
	Cough = cough;
}

void PatientNode::SetLoc(char * location)
{
	Location = new char[strlen(location) + 1]; //dynamic allocaiton
	strcpy(Location, location);
}