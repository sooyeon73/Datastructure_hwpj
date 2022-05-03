#include "HeaderTable.h"
#include <iostream>
HeaderTable::~HeaderTable() {
}
void HeaderTable::insertTable(char* item, int frequency) {

	//if new item
	if (frequency == 1) {
		// push item in indextable
		indexTable.push_back(make_pair(frequency, item)); 

		/*NEW NODE setting*/
		FPNode* newNode = new FPNode;
		newNode->setItem(item);
		newNode->updateFrequency(1);
		// push item in datatable
		dataTable.insert(make_pair(item, newNode)); 
	}
	else // item already exists
	{
		auto it = indexTable.begin();
		auto it2 = dataTable.begin();
		for (int i = 0; i < indexTable.size(); i++)
		{
			if (it->second.compare(item) == 0) // finding item node
			{
				it->first = frequency; //frequency setting
				it2->second->updateFrequency(1); 
				break;
			}
			else
			{
				it++; it2++; // next node
			}
		}
	}
}
int HeaderTable::find_frequency(string item){
	int frequency = 0;
	for (auto it = indexTable.begin(); it!=indexTable.end();it++)
	{
		if (it->second.compare(item) == 0) // if item's node is exist
		{
			frequency=it->first; //frequency return
			break;
		}
	}
	return frequency;
}
