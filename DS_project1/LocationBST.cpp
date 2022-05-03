#include "LocationBST.h"
#include <string.h>

LocationBST::LocationBST() // conductor
{
    Root = NULL;

    Insert_Location(); // Location BST build!
}

LocationBST::~LocationBST()
{   
}

LocationNode * LocationBST::GetRoot() { return this->Root; } //return root

void LocationBST::Insert_Location()
{ 
    /*building BST once*/

    LocationNode* n = new LocationNode; // location node assigning
    n->SetLoc("Gwangju"); // set location
    Root = n; // assign in BST

    LocationNode* n1 = new LocationNode;
    n1->SetLoc("Daegu");
    Root->SetLeft(n1);

    LocationNode* n2 = new LocationNode;
    n2->SetLoc("Busan");
    Root->GetLeft()->SetLeft(n2);

    LocationNode* n3 = new LocationNode;
    n3->SetLoc("Daejeon");
    Root->GetLeft()->SetRight(n3);

    LocationNode* n4 = new LocationNode;
    n4->SetLoc("Seoul");
    Root->SetRight(n4);

    LocationNode* n5 = new LocationNode;
    n5->SetLoc("Incheon");
    Root->GetRight()->SetLeft(n5);

    LocationNode* n6 = new LocationNode;
    n6->SetLoc("Ulsan");
    Root->GetRight()->SetRight(n6);
}

void LocationBST::Insert_Patient(PatientNode * node)
{
    /* Inserting NEW NODE in BST*/
    //searching location -> insert node in that bst
    
    //Gwangju
    if (strcmp(node->GetLoc(), "Gwangju")==0)
    {
        Search(Root, "Gwangju")->GetBST()->Insert(node);
    }
    //Daegu
    else if (strcmp(node->GetLoc(),"Daegu")==0)
    {
        LocationNode* p = Search(Root, "Daegu");
        p->GetBST()->Insert(node);
    }
    //Busan
    else if (strcmp(node->GetLoc(),"Busan")==0)
    {
        LocationNode* p = Search(Root, "Busan");
        p->GetBST()->Insert(node);
    }
    //Daejeon
    else if (strcmp(node->GetLoc() , "Daejeon")==0)
    {
        LocationNode* p = Search(Root, "Daejeon");
        p->GetBST()->Insert(node);
    }
    //Seoul
    else if (strcmp(node->GetLoc(), "Seoul")==0)
    {
        LocationNode* p = Search(Root, "Seoul");
        p->GetBST()->Insert(node);
    }
    //Incheon
    else if (strcmp(node->GetLoc(), "Incheon")==0)
    {
        LocationNode* p = Search(Root, "Incheon");
        p->GetBST()->Insert(node);
    }
    //Ulsan
    else if (strcmp(node->GetLoc(),"Ulsan")==0)
    {
        LocationNode* p = Search(Root, "Ulsan");
        p->GetBST()->Insert(node);
    }
}

// SEARCH from Location to Location
LocationNode* LocationBST::Search(LocationNode*root, const char * name) 
{
    if (root == NULL)
        return NULL;

    if (strcmp(root->GetLoc() , name)==0) // if node found
        return root; //return!

    else if (root->GetLoc()[0] > name[0]) // else if node's Loc>name
        return Search(root->GetLeft(), name); // find Left child
    else 
        return Search(root->GetRight(), name); // find Right child
}

// SEARCH from patient name to patientnode
PatientBSTNode* LocationBST::Search2(LocationNode* root, const char* name) 
{
    if (root == NULL)
        return NULL;

    PatientBST* p = root->GetBST(); // get bst from root
    PatientBSTNode* p_r = p->GetRoot(); // get root from bst

    // if found
    if (p->Search(p_r, name) != NULL)
        return (p->Search(p_r, name)); //return 
    
    //self -functioning
    if (Search2(root->GetLeft(), name))
        return Search2(root->GetLeft(), name);
    if(Search2(root->GetRight(),name));
    return Search2(root->GetRight(), name);

}

// patient name -> search location Node
LocationNode* LocationBST::Search3(LocationNode* root, const char* name) 
{
    if (root == NULL)
        return NULL;

    PatientBST* p = root->GetBST(); //get bst from root
    PatientBSTNode* p_r = p->GetRoot(); //get root form bst

    //if found
    if (p->Search(p_r, name) != NULL)
        return root; //reutrn LOCATION NODE

    //self-functioning
    if (Search3(root->GetLeft(), name))
        return Search3(root->GetLeft(), name);
    if(Search3(root->GetRight(), name))
        return Search3(root->GetRight(),name);
}
//BPOP
void LocationBST::Delete(LocationNode*node,char * name)
{
    node->GetBST()->Delete(name); // Delete node in bst
}

void LocationBST::Print_PRE(LocationNode* node)
{
    if (node == NULL)
        return;
    //PRE ORDER 
    if (node->GetBST()->GetRoot() != NULL) // if bst exists
        node->GetBST()->Print_PRE(node->GetBST()->GetRoot()); //print_pre
    //self-functioning
    Print_PRE(node->GetLeft()); 
    Print_PRE(node->GetRight());
}

void LocationBST::Print_IN(LocationNode*node)
{
    if (node == NULL)
        return;
 //IN ORDER
    Print_IN(node->GetLeft());
    if (node->GetBST() != NULL) // if bst exist
        node->GetBST()->Print_IN(node->GetBST()->GetRoot()); //print_IN
    Print_IN(node->GetRight());
}

void LocationBST::Print_POST(LocationNode* node)
{
    if (node == NULL)
        return;
  
    //POST ORDER
    Print_POST(node->GetLeft());
    Print_POST(node->GetRight());
    if (node->GetBST() != NULL) // if bst exist
        node->GetBST()->Print_POST(node->GetBST()->GetRoot()); //PRINT_POST
}

void LocationBST::Print_LEVEL()
{
    //LEVEL ORDER
    queue<LocationNode*>q; // q decalaration
    LocationNode* p = Root;
    while (p) { //while p exist
        if(p->GetBST()!=NULL) // if bst exsit
             p->GetBST()->Print_LEVEL(); //PRINT_LEVEL
        if (p->GetLeft()) // if lefttree exist
            q.push(p->GetLeft()); //push
        if (p->GetRight()) //if righttree exist
            q.push(p->GetRight()); //push
        if (q.empty()) return;
        p = q.front();
        q.pop();
    }
}


