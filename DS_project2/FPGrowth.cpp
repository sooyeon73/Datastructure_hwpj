#include "FPGrowth.h"

FPGrowth::~FPGrowth() {
}
void FPGrowth::createFPtree(FPNode* root, HeaderTable* table, list<string> item_array, int frequency) {

	FPNode* curNode = root;

	auto it = item_array.begin(); // it = item(string)

	for (int i = 0; i < item_array.size(); i++) // all item insert
	{
		map<string, FPNode*> curMap = curNode->getChildren(); // children variable
		map<string, FPNode*> ::iterator iter; 
		iter = curMap.begin();
		bool check = false;

		for (int j = 0; j < curMap.size(); j++) //inside curChild map loop
		{
			if (it->compare(iter->second->getItem()) == 0) // item found
			{
				curNode = iter->second; // curNode update
				curNode->updateFrequency(1); // frequency update
				check = true;
				break;
			}
			iter++; // next map element
		}
			
		// if doesn't exist in curchild map
		if(check==false){
			//new children 
			FPNode* newNode = new FPNode; 
			newNode->setParent(curNode); // newnode's parent is curnode
			char* c = new char[20]; //for item name
			strcpy(c, it->c_str());
			newNode->setItem(c);
			newNode->updateFrequency(1); 
			curNode->pushchildren(*it, newNode);
			connectNode(table, *it, newNode); //connect
			curNode = newNode;	
		}
		it++;
	}
}

void FPGrowth::connectNode(HeaderTable* table, string item, FPNode* node) {

	FPNode* curNode = table->getNode(item);
	// find item node in table

	if(curNode->getNext()==NULL) // if connect node doesnt exist
		curNode->setNext(node);
	else
	{
		curNode = curNode->getNext(); // connected first children
		while (curNode->getNext() != NULL)
		{
			curNode = curNode->getNext();
			// loop by none connected last node
		}
		curNode->setNext(node);// connec new node
	}
}

bool FPGrowth::printList() {
	flog << "======= PRINT_ITEMLIST =======" << endl;
	if (table->getindexTable().empty()) // if empty
		return false;
	else {
			flog<<"Item" << "\t" << "Frequency" << endl;
		
		auto it = table->getindexTable();
		auto it_ = it.begin();
		
		for (int i =0; i< table->getindexTable().size();i++) // print all element
		{
			flog << it_->second <<" "<< it_->first << endl;
			it_++;
		}
		flog << "======================" << endl << endl;
		return true;
	}
}
bool FPGrowth::printTree() {
	table->ascendingIndexTable(); //ascending sort
	flog << "======= PRINT_FPTREE =======" << endl;

	if (fpTree->getChildren().empty()) // if empty
		return false;

		flog<< " {StandaraItem.Frequency} (Path_Itme.Frequency)" << endl;

		//table first element
		list<pair<int, string> > index = table->getindexTable();
		auto li = index.begin();

		for (int i = 0; i < index.size(); i++)
		{
			if (li->first >= threshold) {
				//curNode = connect node 
				FPNode* curNode = table->getNode(li->second)->getNext();
				flog << "{" << li->second << '.' << li->first << "}" << endl; // standaraitem,frequency

				FPNode* curNode2 = curNode; // for check all routine
				while (curNode2 != NULL)
				{
					while (curNode != fpTree) // if root?
					{
						flog << "(" << curNode->getItem() << "." << curNode->getFrequency() << ") ";
						curNode = curNode->getParent();
					}
					flog << endl;
					curNode2 = curNode2->getNext();
					curNode = curNode2;
				}
			}
			li++;
		}

	flog << "==========================" << endl;
	return true;
}


/*
bool FPGrowth::contains_single_path(FPNode* pNode) {
	if (pNode->getChildren().size() == 0) return true;
	else if (pNode->getChildren().size() > 1) return false;
	return contains_single_path(pNode->getChildren().begin()->second);
}

map<set<string>, int> FPGrowth::getFrequentPatterns(HeaderTable* pTable, FPNode* pTree) {
	return {};
}
void FPGrowth::powerSet(map<set<string>, int>* FrequentPattern, vector<string> data, string item, int frequency, int* ptr, int depth) {
	if (data.size() == depth) {
		set<string> set; set.insert(item);
		for (int i = 0; i < data.size(); i++) { if (ptr[i] == 1) set.insert(data[i]); }
		FrequentPattern->insert(make_pair(set, frequency)); return;
	}
	ptr[depth] = 1;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
	ptr[depth] = 0;
	powerSet(FrequentPattern, data, item, frequency, ptr, depth + 1);
}
void FPGrowth::saveFrequentPatterns(){
}
*/