#include "Manager.h"
#include <iostream>
#include <string>
#include<cstring>
//#pragma warning(disable:4996)

Manager::Manager()
{}

Manager::~Manager()
{}

void Manager::run(const char* command)
{
    fin.open(command); //file opening
    flog.open("log.txt", ios::app); //file writing for log.
    if (!fin) // if file dosent exist
    {
        flog << "File Open Error" << endl;
        return;
    }
    char cmd[32]; // command input
    while (!fin.eof())
    {
        fin >> cmd;
        /* LOAD */
        if (strcmp(cmd, "LOAD") == 0)
        {
            if (LOAD())
            {
                PrintSuccess("LOAD");
            }
            else
            {
                PrintErrorCode(100);
            }
        }
        /*ADD*/
        else if(strcmp(cmd, "ADD") == 0)      
        {
            if (ADD()) {}
            else
            {
                PrintErrorCode(200);
            }
        }
        /*QPQP*/
        else if (strcmp(cmd, "QPOP") == 0)
        {
            if (QPOP())
            {
                PrintSuccess("QPOP");
            }
            else
            {
                PrintErrorCode(300);
            }
        }
        /*PRINT*/
        else if (strcmp(cmd, "PRINT") == 0)
        {
            if (PRINT()) {}
            else
            {
                PrintErrorCode(400);
            }
        }
        /*SEARCH*/
        else if (strcmp(cmd, "SEARCH") == 0)
        {
            if (SEARCH()) {}
            else
            {
                PrintErrorCode(500);
            }
        }
        /*BPOP*/
        else if (strcmp(cmd, "BPOP") == 0)
        {
            if (BPOP()) {
                PrintSuccess("BPOP");
            }
            else
            {
                PrintErrorCode(600);
            }
        }
        /*EXIT*/
        else if(strcmp(cmd, "EXIT") == 0)
        {
            PrintSuccess("EXIT");
            break; // exit
        }
       /*ERROR*/
        else
        {
            flog << "========== ERROR ==========" << endl;
            flog << "Command Error" << endl;
            flog << "===========================" << endl << endl;
        }
    }
    fin.close();
    flog.close();
}

bool Manager::LOAD()
{
    finn.open("data.txt"); //file open
    if (!finn) //if file open error
    {
        return false;
    }
    if (!(ds_queue->empty())) // already LOADED
    {
        return false;
    }
    char data[32];
    float data_; //for temp
    while (!finn.eof())
    {
        PatientNode* pn = new PatientNode;
        // new node allocation
        /* setting value */
        finn >> data;
        pn->SetName(data);
        finn >> data_;
        pn->SetTemp(data_);
        finn >> data;
        pn->SetCough(data[0]);
        finn >> data;
        pn->SetLoc(data);

        //push in ds_queue
        ds_queue->push(pn);
    }
    return true;
}

bool Manager::ADD()
{
    char name[10]; //for name
    float temp; //for temparture
    char cough; //for cought
    char loc[10]; //for location
    string line; //for getline
    int sum = 0;
    getline(fin, line); 
    char* data = new char[32]; // new data allocation
    strcpy(data, line.c_str()); //copy

    //cutting by " "
    char* tok = strtok(data, " ");
    while (tok != NULL)
    {
        sum++;
        if (sum == 1) // first
            strcpy(name, tok);
        else if (sum == 2) //2nd
            temp = atof(tok);
        else if (sum == 3) //3rd
            cough = tok[0];
        else if (sum == 4) //4th
            strcpy(loc, tok);
        tok = strtok(NULL, " ");
    }
    delete[]data;
    // INPUT variables shortage
    if (sum != 4) {
        return false;
    }
    //new node alloctaion
    PatientNode* pn = new PatientNode;
    //setting value
    pn->SetName(name);
    pn->SetTemp(temp);
    pn->SetCough(cough);
    pn->SetLoc(loc);

    ds_queue->push(pn); // push in ds_queue
    flog << "========== ADD ==========" << endl;
    flog << ds_queue->back()->GetName() << "/" << ds_queue->back()->GetTemp()
        << "/" << ds_queue->back()->GetCough() << "/" << ds_queue->back()->GetLoc() << endl;
    flog << "===========================" << endl << endl;
  
    return true;
}

bool Manager::QPOP() // into BST
{
    int n;
    fin >> n; // number of QPOP
    if (n > ds_queue->size()) // number excess
    {
        return false;
   }
    
    while (n != 0)
    {
        //into BST from front queue
        PatientNode* temp = ds_queue->front();
        ds_bst->Insert_Patient(temp); //INSERT
        ds_queue->pop(); //POP
        n--;
    }
    return true;
}

bool Manager::PRINT()
{
    flog << "========== PRINT ==========" << endl;
    char data[10];
    fin >> data;
    if (strcmp(data,"B")==0) // BST PRINT
    {
        flog << "BST" << endl;
        fin >> data;
        if (strcmp(data, "PRE") == 0) //pre order
        {
            ds_bst->Print_PRE(ds_bst->GetRoot());
        }
        else if (strcmp(data, "IN") == 0) // in order
            {
                ds_bst->Print_IN(ds_bst->GetRoot());
            }
        else if (strcmp(data, "POST") == 0) //post order
            {
                ds_bst->Print_POST(ds_bst->GetRoot());
            }
        else if (strcmp(data, "LEVEL") == 0) //level order
        {
            ds_bst->Print_LEVEL();
        }
    }
    else if (strcmp(data, "H") == 0) // Heap PRINT
    {
        if (ds_heap->GetSize() == 0) // if heap doesnt exist
        {
            return false;
        }
        flog << "Heap" << endl;
        ds_heap->Print(); //print
    }
    flog << "===========================" << endl <<endl<<endl;
    return true;
}


bool Manager::SEARCH()
{
    char name[10];
    fin >> name;
    LocationNode* p = ds_bst->GetRoot();
    PatientBSTNode* pp = ds_bst->Search2(p, name); // SEARCH NAME TO PATIENT
    if (pp == NULL) // if doesnt exist
        return false;
    else // exist
    {
        flog << "========= SEARCH ==========" << endl
            << pp->GetName() << "/" << pp->GetDisease() << endl <<
            "==========================" << endl<<endl;    }
}



bool Manager::BPOP()
{
    /*FOR EXCEPTIONAL CONTROL
      :: working well in windows
      ::  not working in Ubuntu
    /*
    1)
    string line;
    getline(fin, line);
    char* data = new char[32];
    strcpy(data, line.c_str());
    char* tok = strtok(data, " ");
   if (tok == NULL)
    {
       return false;
    }
    char name[20];
    strcpy(name, tok);
       delete[]data;

    2)
    string line;
    getline(fin, line);
    strcpy(name, line.c_str());
    if (name==NULL||(strcmp(name,"\0"))==0)
        return false;
    line.erase(0, 1);
    strcpy(name, line.c_str());
    */
    char name[20];
    fin >> name;
    LocationNode* p = ds_bst->Search3(ds_bst->GetRoot(), name); // search Location!! of name
    if(!p) // if doesnt exist
    {
        return false;
    }
    ds_heap->Insert(p->GetLoc()); // INSERT IN HEAP
    ds_bst->Delete(p, name); //DELETE FROM BST
    return true;
}
void Manager::PrintErrorCode(int num) //print error
{
    flog << "========== ERROR ==========" << endl;
    flog << num << endl;
    flog << "===========================" << endl << endl;
}

void Manager::PrintSuccess(const char *act) //print success
{
    flog << "========== " << act << " ==========" << endl;
    flog << "Success" << endl;
    flog << "==========================" << endl << endl;
}