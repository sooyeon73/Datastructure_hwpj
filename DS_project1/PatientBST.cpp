#include "PatientBST.h"
#include <iostream>
#include<string.h>
using namespace std;
PatientBST::PatientBST()
{
    P_Root = nullptr;
}


PatientBST::~PatientBST()
{
}

PatientBSTNode * PatientBST::GetRoot()
{
    return this->P_Root; //return root
}

void PatientBST::Insert(PatientNode * node)
{
    //QPOP
    string str1(node->GetName());

   PatientBSTNode* p = P_Root, * pp = NULL;
   //starting from root
    while (p)
    {
        pp = p;
        string str2(p->GetName());
        if (str1.compare(str2)<0) p = p->GetLeft(); // if node<p
        else p = p->GetRight(); // node>p
    }
    p = new PatientBSTNode; // new NODE allocation
    //value setting
    p->SetName(node->GetName());
    if (node->GetTemp() > 37.5 && node->GetCough() == 'Y') p->SetDisease('+');
    else p->SetDisease ('-');
    if (P_Root != NULL) // if root exists
    {
        //find location
        string str2(pp->GetName());
        if (str1.compare(str2)<0) pp->SetLeft(p); 
        else pp->SetRight(p);
    }
    else P_Root = p; // if root doesnt exists
}


void PatientBST::Print_PRE(PatientBSTNode * node)
{
    ofstream flog;
    flog.open("log.txt", ios::app);
    if (node == NULL)
        return;
    //PRINT PRE
    flog << node->GetName() << "/" <<node->GetDisease()<<endl;
    Print_PRE(node->GetLeft());
    Print_PRE(node->GetRight());
}

void PatientBST::Print_IN(PatientBSTNode * node)
{
    ofstream flog;
    flog.open("log.txt", ios::app);
   
    if (node == NULL)
        return;
    Print_IN(node->GetLeft());
    flog << node->GetName() << "/"<<node->GetDisease()<<endl; //PRINT IN
    Print_IN(node->GetRight());
}

void PatientBST::Print_POST(PatientBSTNode * node)
{
    ofstream flog;
    flog.open("log.txt", ios::app);
    if (node == NULL)
        return;
    Print_POST(node->GetLeft());
    Print_POST(node->GetRight());
    flog << node->GetName() << "/" << node->GetDisease() << endl; //PRINT PoST
}

void PatientBST::Print_LEVEL()
{
    ofstream flog;
    flog.open("log.txt", ios::app);

    queue<PatientBSTNode*>q; // queue declaration
    PatientBSTNode* p = P_Root; //from root
    while (p) {
        flog << p->GetName() << "/" << p->GetDisease() << endl; // PRINT LEVEL
        if (p->GetLeft()) //if p->pLeft exist
            q.push(p->GetLeft()); //push
        if (p->GetRight()) //if p->pRight exist
            q.push(p->GetRight());//push
        if (q.empty()) return;
        p = q.front();
        q.pop();
    }
}

PatientBSTNode* PatientBST::Search(PatientBSTNode* root, const char* name)
{
     if (root == NULL)
        return NULL;

    if (strcmp(root->GetName(), name) == 0) //FOUND!
        return root; //return PATIENTBSTNODE

    //self functioning
    if (Search(root->GetLeft(), name))
        return Search(root->GetLeft(), name);
    if (Search(root->GetRight(), name))
        return Search(root->GetRight(), name);
}


void PatientBST::Delete(char* name)
{
//BPOP
    PatientBSTNode* p = P_Root, *pp = NULL;
    //finding location of node
    while (p && strcmp(name, p->GetName()) != 0)
    {
        pp = p;
        string str1(name);
        string str2(p->GetName());
        if (str1.compare(str2) < 0) p = p->GetLeft(); //if name<p
        else p = p->GetRight(); // name>p
    }
    if (p == 0) return; // no exist
    if (p->GetLeft() == NULL && p->GetRight() == NULL) // no child
    {
        if (pp == 0) P_Root = NULL; //if root
        //pointersetting null
        else if (pp->GetLeft() == p) pp->SetLeft(NULL);
        else pp->SetRight(NULL);
        delete p;
    }

    else if (p->GetLeft() == NULL)   //only have right subtree
    {
        if (pp == NULL) //if root
            P_Root = p->GetRight();
        //finding loc
        else if (pp->GetLeft() == p)pp->SetLeft(p->GetRight());
        else pp->SetRight(p->GetRight());
        delete p;
    }
    
    else if (p->GetRight() == NULL) // only have left subtree
    {
        if (pp == NULL) //if root
            P_Root = p->GetLeft();
        //finding loc
        else if (pp->GetLeft() == p)pp->SetLeft(p->GetLeft());
        else pp->SetRight(p->GetLeft());
        delete p;
    }
    else {
        // both child exist
        PatientBSTNode* prevprev = p, * prev = p->GetLeft(), * curr = p->GetLeft()->GetRight();
        /*FINDING MAX node in LEFT SUBTREE*/
        while (curr)
        {
            prevprev = prev;
            prev = curr;
            curr = curr->GetRight();
        }
        p->SetName(prev->GetName());
        p->SetDisease(prev->GetDisease());
        if (prevprev == p)prevprev->SetLeft(prev->GetLeft());
        else prevprev->SetRight(prev->GetLeft());
        delete prev;
    }
}