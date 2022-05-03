#include "Manager.h"
#include <sstream>
#include<algorithm>
void Manager::run(const char* command)
{
	fin.open(command);
	flog.open("log.txt", ios::app);
	
	if(!fin) // file open fail
	{
		flog << "File Open Error" << endl;
		return;
	}
	while (!fin.eof())
	{
		fin >> cmd;
		/*LOAD*/
		if (strcmp(cmd, "LOAD") == 0)
		{
			if (LOAD())
				printSuccessCode();
			else
				printErrorCode(100);
		}
		/*PRINT ITEMLIST*/
		else if (strcmp(cmd, "PRINT_ITEMLIST") == 0)
		{
			if (PRINT_ITEMLIST())
			{
			}
			else
				printErrorCode(300);
		}
		else if (strcmp(cmd, "BTLOAD") == 0)
		{
		}

		/*PRINT FPTREE*/
		else if (strcmp(cmd, "PRINT_FPTREE") == 0)
		{
			if (PRINT_FPTREE())
			{
			}
			else
				printErrorCode(400);
		}
		else if (strcmp(cmd, "SAVE") == 0)
		{
		}
		else if (strcmp(cmd, "PRINT_MIN") == 0)
		{
			string a;
			getline(fin, a);
		}
		else if (strcmp(cmd, "PRINT_CONFIDENCE") == 0)
		{
			string a;
			getline(fin, a);
		}
		else if (strcmp(cmd, "PRINT_RANGE") == 0)
		{
			string a;
			getline(fin, a);
		}

		/*EXIT*/
		else if (strcmp(cmd, "EXIT") == 0)
		{
			flog << "======== EXIT ========" << endl;
			printSuccessCode();
			return;
		}
		/*ERROR*/
		else
		{
			flog << "Command Error" << endl;
		}
	}
	fin.close();
	flog.close();
	return;
}

bool Manager::LOAD()
{
	fin2.open("market.txt"); // data file open
	flog << "======== LOAD ========" << endl;

	if (!fin2) // file open error
		return false;
	if (!fpgrowth->getHeaderTable()->getindexTable().empty()) //already loaded
		return false;

	char data[300]; // for load line
	/* headertable */
	string line;
	while (getline(fin2, line))
	{
		strcpy(data, line.c_str());
		char* item = strtok(data, "\t"); 
		if (item == NULL)break; // segmentation fault
		while (item != NULL) {
			int f; // frequency check
			f = fpgrowth->item_frequency(item);
			/*INSERT ITEM IN TABLE*/
			fpgrowth->createTable(item, f + 1); 
			item = strtok(NULL, "\t");//next string
		}
	}
	fpgrowth->getHeaderTable()->descendingIndexTable(); // index table list desc sort
	fin2.close();

	/*FP Growth*/
	// reopen 
	fin2.open("market.txt"); 
	while (getline(fin2, line))
	{
		/*1 line = 1path*/
		list<pair<int, string>> forsort; //list for sorting descending
		list<string> forfp; //list for path in fp growth

//		fin2.getline(data, 300, '\n'); // load 1line
		strcpy(data, line.c_str());
		char* item = strtok(data, "\t");
		if (item == NULL)break;
		while (item != NULL) {
			int f; // frequency check
			f = fpgrowth->item_frequency(item);
			forsort.push_back(make_pair(f, item)); // for sorting
			item = strtok(NULL, "\t");// next string
		}

		forsort.sort(greater<pair<int, string>>()); //sort descending

		auto it=forsort.begin();
		for (int i = 0; i < forsort.size(); i++) {
				if(it->first>=fpgrowth->getThreshold()) // if frequency >=threshold
					forfp.push_back(it->second); // item of sortlist moving to forfp list
				it++;
			}
		// list_array for fpgrowth done
		//create fp tree
		fpgrowth->createFPtree(fpgrowth->getTree(), fpgrowth->getHeaderTable(), forfp,1);
	}
	fin2.close();
	return true;
}
/*
bool Manager::BTLOAD()
{
	
	return true;
}
*/
bool Manager::PRINT_ITEMLIST() {
	if (fpgrowth->printList())
		return true;
	else
		return false;
}

bool Manager::PRINT_FPTREE() {

	if (fpgrowth->printTree())
		return true;
	else
		return false;
}
/*
bool Manager::PRINT_MIN(char* item, int min_frequency) {
}
bool Manager::PRINT_CONFIDENCE(char* item, double rate) {	
}
bool Manager::PRINT_RANGE(char* item, int start, int end) {	
}
*/
void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "======== ERROR " << n << " ========" << endl;
	flog << "=======================" << endl << endl;
}

void Manager::printSuccessCode() {//SUCCESS CODE PRINT 
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
}
