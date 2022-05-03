#include "Manager.h"
#include "MinHeap.h"
#include <cstring>
#include <sstream>
#include<cstdlib>
#include <cmath>
#include <chrono>
#pragma warning(disable:4996)
using namespace std;


Manager::~Manager()
{
    if (fout.is_open())
        fout.close();

    if (ferr.is_open())
        ferr.close();
}

void Manager::Run(const char* filepath)
{
    fout.open(RESULT_LOG_PATH);
    char cmd[20];

    fin.open(filepath);
    if (!fin) // file open fail
    {
        Result a = CommandFileNotExist;
        fout << "====== SYSTEM ======" << endl
           << "Error code: " << a << endl <<
            "=====================" << endl;
        return;
    }

    while (!fin.eof())
    {
        if (fin.eof())
            break;
        
        fin >> cmd;
        if (cmd == NULL)
            break;
        if (cmd[0] == '/' && cmd[1] == '/')
        {
            string line;
            getline(fin, line);
        }

        /*LOAD*/
        else if (strcmp(cmd, "LOAD") == 0)
        {
            fin >> cmd;
            PrintError(Load(cmd));
        }

        /*UPDATE*/
        else if (strcmp(cmd, "UPDATE") == 0)
        {
            PrintError(Update());
        }


        /*PRINT*/
        else if (strcmp(cmd, "PRINT") == 0)
        {
            PrintError(Print());
        }

        /*BFS*/
        else if (strcmp(cmd, "BFS") == 0)
        {
            string line;
            getline(fin, line);
            char line_[15];
            strcpy(line_, line.c_str());

            char* ver = strtok(line_, " "); //  cut
            int start = atoi(ver); // startver
            ver = strtok(NULL, " ");
            if (ver == NULL)
            {
                PrintError(VertexKeyNotExist);
                continue;
            }
            int end = atoi(ver);
            PrintError(FindPathBfs(start, end));
        }

        else if (strcmp(cmd, "DIJKSTRA") == 0)
        {
            string line;
            getline(fin, line);
            char line_[15];
            strcpy(line_, line.c_str());

            char* ver = strtok(line_, " "); //  cut
            int start = atoi(ver); // startver
            ver = strtok(NULL, " ");
            if (ver == NULL)
            {
                PrintError(VertexKeyNotExist);
                continue;
            }
            int end = atoi(ver);
            PrintError(FindShortestPathDijkstraUsingSet(start, end));
        }
        else if (strcmp(cmd, "DIJKSTRAMIN") == 0)
        {
            string line;
            getline(fin, line);
            char line_[15];
            strcpy(line_, line.c_str());

            char* ver = strtok(line_, " "); //  cut
            int start = atoi(ver); // startver
            ver = strtok(NULL, " ");
            if (ver == NULL)
            {
                PrintError(VertexKeyNotExist);
                continue;
            }
            int end = atoi(ver);
            PrintError(FindShortestPathDijkstraUsingMinHeap(start, end));
        }

        else if (strcmp(cmd, "BELLMANFORD") == 0)
        {
            string line;
            getline(fin, line);
            char line_[15];
            strcpy(line_, line.c_str());

            char* ver = strtok(line_, " "); //  cut
            int start = atoi(ver); // startver
            ver = strtok(NULL, " ");
            if (ver == NULL)
            {
                PrintError(VertexKeyNotExist);
                continue;
            }
            int end = atoi(ver);
            PrintError(FindShortestPathBellmanFord(start, end));
        }

        else  if (strcmp(cmd, "FLOYD") == 0)
        {
            PrintError(FindShortestPathFloyd());
        }

        else if (strcmp(cmd, "CONFIG") == 0)
        {
            string line_;
            getline(fin, line_);
            char line__[15];
            strcpy(line__, line_.c_str());
            //0 quick 1 insert 2 merge 3 heap 4 bubble

            char* ver = strtok(line__, " "); //  cut
            //ver ="-sort"
            if (strcmp(ver, "-sort")!=0)
            {
                PrintError(InvalidOptionName);
                ver = strtok(NULL, " ");
                continue;
            }
            ver = strtok(NULL, " ");
            if (strcmp(ver, "quick") == 0)
                config = 0;
            else if (strcmp(ver, "insert") == 0)
                config = 1;
            else if (strcmp(ver, "merge") == 0)
                config = 2;
            else if (strcmp(ver, "heap") == 0)
                config = 3;
            else if (strcmp(ver, "bubble") == 0)
                config = 4;
            else {
                PrintError(InvalidAlgorithmName);
                continue;
            }
            fout << "====== CONFIG LOG ======" << endl <<
                "Sorted by : " << ver << " Sorting" << endl <<
                "========================" << endl;

            PrintError(Success);
        }

        else
        {
            PrintError(NonDefinedCommand);
        }
    }
    fin.close();
}
void Manager::PrintError(Result result)
{
    fout << "================" << endl <<
        "Error code: " << result << endl
        << "================" << endl;
}

Result Manager::Load(const char* filepath)
{
    fin2.open(filepath);
    if (!fin2)
        return LoadFileNotExist;

     //mapdata load

    /*LOAD*/
    string line;
    getline(fin2, line);
    int n = atoi(line.c_str()); // matrix N
    int i = 0; //M count

    while (i<n)
    {
        char line_[100]; //1line
        getline(fin2, line);
        strcpy(line_, line.c_str());

        char* ownerName = strtok(line_, "'"); // ownername cut
        
        m_graph.AddVertex(i);
        // i th Vertex
        m_graph.FindVertex(i)->SetOwner(ownerName); //set name

        char* storeName = strtok(NULL, "/");// "'s ~~~~ "

        int p = 0;
        while (p < strlen(storeName))
        {
            storeName[p] = storeName[p + 2]; //'s remove
            p++;
        }
        storeName[p - 2] = storeName[p-1]; //" " remove


        //storeName complete
        m_graph.FindVertex(i)->SetStore(storeName); //set store

        //weight list
        char* list = strtok(NULL, "\n"); //

        char* weight = strtok(list, " ");
        for (int j = 0; j< n; j++) //
        {
            if (strcmp(weight,"0")!=0)
            {
                m_graph.AddEdge(i, j, atoi(weight)); // add edge
            }
                weight = strtok(NULL, " "); // next.. weight
        }
        i++;
    }

    fout << "====== LOAD ======" << endl
        << "Success" << endl <<
        "==================" << endl;
    return Success;

}
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()
{

    if (m_graph.Size() == 0) //exception
        return GraphNotExist; //  GraphNotExist
   
    m_graph.Print(fout);
    return Success;
 
}

Result Manager::Update()
{
    //all edges
    int i = m_graph.Size();// Vertex's amount
    for (int k = 0; k < i; k++)
    {
        Vertex* curVer = m_graph.FindVertex(k);
        char* compareOwner = curVer->GetOwner();
        char* compareStore = curVer->GetStore();

        int j = curVer->Size();
        Edge* curEdge = curVer->GetHeadOfEdge();
        for (int p = 0; p < j; p++) // all edges
        {
            //Vertex string and
            //Edge's Key's Vertex string
            Vertex* comVer = m_graph.FindVertex(curEdge->GetKey());
            char* comparedOwner = comVer->GetOwner();
            char* comparedStore = comVer->GetStore();

            enum Result rabin;

            //1rule
            rabin = RabinKarpCompare(compareOwner, comparedOwner);
            if (rabin != None)
            {
                double w = double(curEdge->GetWeight());
                w = ceil(w * (0.9));
                curEdge->SetWeight(int(w));
            }

            //2rule
            if (rabin == Tensame)
            {
                double w = double(curEdge->GetWeight());
                w = ceil(w * (0.9));
                curEdge->SetWeight(int(w));
            }

            rabin = RabinKarpCompareW(compareStore, comparedStore);
          //3
            if (rabin == Wordsame)
            {
                double w = double(curEdge->GetWeight());
                w = ceil(w * (0.8));
                curEdge->SetWeight(int(w));
            }
            curEdge = curEdge->GetNext();
        }
    }

    fout << "====== UPDATE ======" << endl
        << "Success" << endl <<
        "==================" << endl;
    return Success;

}


Result Manager::RabinKarpCompare( const char* CompareString,  const char* ComparedString)
{
    enum Result result = None;

    //copy
    char compare[80];
    char compared[80];
    strcpy(compare, CompareString);
    strcpy(compared, ComparedString);

    //all upper alphabet
    for (int i = 0; i < strlen(compare); i++)
        compare[i] = toupper(compare[i]);
    for (int i = 0; i < strlen(compared); i++)
        compared[i] = toupper(compared[i]);

    //size
    int compareSize = strlen(CompareString); 
    int comparedSize = strlen(ComparedString);
        
    //if less then 5
    if (compareSize < 5 || comparedSize < 5)
        return result;

    //select 5 char...
    int p = 0;
    while (p<=(comparedSize-5)) // selecting 5 char's loop
    {

        int compareHash = 0; //for comparestring
        int comparedHash = 0;  //for comparedstring
        int power = 1; // 2^power

        /* 5char select in comparedString */
        char selectedCompared[6]; 
        selectedCompared[5] = '\0';// selected char
        for (int k = 0; k < 5; k++)
        {
            selectedCompared[k] = compared[p + k]; // copy
        }

        /*compare selected spring & comparestring*/
        for (int i = 0; i <= (compareSize - 5); i++)
        {
            if (i == 0)// get first hash 
            {
                  // hash counting
                for (int k = 0; k < 5; k++) {
                    compareHash += compare[4 - k] * power;
                    comparedHash += selectedCompared[4 - k] * power;
                    power *= 2; 
                 }
                power /= 2;
            }
            else {
            // hash changing
                compareHash = 
                    //(Value left without first character)*2
                    (compareHash - compare[i - 1] * power) * 2
                    //Add new one char hash (2^0)
                    + compare[4 + i]; 
            }

            //if hash same
            if (compareHash == comparedHash)
            {
                result = Fivesame;
                //Consider same hash, diffent string 
                for (int k = 0; k < 5; k++)
                {
                    if (compare[i + k] != selectedCompared[k]) //if different
                    {
                        result = None; // none
                        break;
                    }
                }
                break; // once -> completed
            }
        }
        if (result == Fivesame)
            break;
        p++;
    }

    if (result == None)
    {
        return result;
    }
    
    if (compareSize < 10 || comparedSize < 10)
    {
        return result;
    }

    //~
    //FiveSame

    //10 char compare
    p = 0;
    while (p <= (comparedSize - 10)) //loop of select 10 char
    {
        int compareHash = 0; //for comparestring
        int comparedHash = 0;  //for comparedstring
        int power = 1; // 2^power

        /* 10char select in comparedString */
        char selectedCompared[11];
        selectedCompared[10] = '\0';// selected string
        for (int k = 0; k< 10; k++)
        {
            selectedCompared[k] = compared[p + k];
        }


        /*compare selected spring & comparestring*/
        for (int i = 0; i <= (compareSize - 10); i++)
        {
            if (i == 0)//get first hash
            {
                // hash counting
                for (int k = 0; k < 10; k++) {
                    compareHash += compare[9 - k] * power;
                    comparedHash += selectedCompared[9 - k] * power;
                    power *= 2;
                }
                power /= 2;
            }
            else {
                     // hash changing
                compareHash =
                    //(Value left without first character)*2
                    (compareHash - compare[i - 1] * power) * 2
                    //Add new one char hash (2^0)
                    + compare[9 + i];
            }

            //samehash
            if (compareHash == comparedHash)
            {
                result = Tensame;
                //consider same hash diffrent stirng
                for (int k = 0; k < 10; k++)
                {
                    if (compare[i + k] != selectedCompared[k]) //if diffrent
                    {
                        result = Fivesame; // only five same
                        break;
                    }
                }
                break; //once done
            }
        }
        if (result == Tensame)
            break;
        p++;
    }

    return result;
}

Result Manager::RabinKarpCompareW(const char* CompareString, const char* ComparedString)
{
//for word compare
    enum Result result = None;
 
    char nul[3] = "\0";
    //for const char
    //preventing change original string
    char compare[80];
    char compared[80];
    char compared2[80];
    strcpy(compare, CompareString);
    strcpy(compared, ComparedString);
    strcpy(compared2, ComparedString);

    //all upper char
    for (int i = 0; i < strlen(compare); i++)
        compare[i] = toupper(compare[i]);
    for (int i = 0; i < strlen(compared); i++)
        compared[i] = toupper(compared[i]);
    for (int i = 0; i < strlen(compared2); i++)
        compared2[i] = toupper(compared2[i]);

    char* word1 = strtok(compare, " "); //cut
    char* nextword1 = strtok(NULL, "\0"); // null remove
    if(nextword1) strcat(nextword1, nul); // null insert
    
    while (word1 != NULL) // word1  loop
    {
        char* word2 = strtok(compared, " ");  
        strcpy(compared, compared2); // saving
        char* nextword2 = strtok(NULL, "\0"); 
        if(nextword2) strcat(nextword2, nul); // null insert
        
        while (word2 != NULL)//word2  loop
        {
            int word1size = strlen(word1); //size
            int word2size = strlen(word2);

            int hash1 = 0;
            int hash2 = 0;
            int power = 1; // 2^power

            if (word1size == word2size)
            {
                //hash counting
                for (int k = 0; k < word1size; k++) {
                    hash1 += word1[word1size - 1 - k] * power;
                    hash2 += word2[word2size - 1 - k] * power;
                    power *= 2;
                }

                //if hash same
                if (hash1 == hash2)
                {
                    result = Wordsame;
                    //consider same hash different string
                    for (int k = 0; k < word1size; k++)
                    {
                        if (word1[k] != word2[k]) //if diffrent
                        {
                            result = None;
                            break;
                        }
                    }
                    break; // once done
                }
            }
         //next word2
            word2 = strtok(nextword2, " ");
            nextword2 = strtok(NULL, "\0");
            if (nextword2) {
                strcat(nextword2, nul);
            }

        }
        if (result == Wordsame) //once done
            break;
        //next word1
        word1 = strtok(nextword1, " ");
        nextword1 = strtok(NULL, "\0");
        if (nextword1) {
            strcat(nextword1, nul);}
    }
    return result;
}

Result Manager::FindPathBfs(int startVertexKey, int endVertexKey)
{
    if (m_graph.Size() == 0) //exception
        return GraphNotExist; //  GraphNotExist

    if (m_graph.IsNegativeEdge() == true)
        return InvalidAlgorithm;
    if (startVertexKey >= m_graph.Size() || endVertexKey >= m_graph.Size())
        return InvalidVertexKey;
    
    vector<int> path = m_graph.FindPathBfs(startVertexKey, endVertexKey);

    fout << "===== BFS =====" << endl
        << "order: ";
    for (int p = 0; p < path.size(); p++)
            fout << path.at(p) << " ";
     
    
    fout << endl
        << "sorted nodes: " ;

    int* path_ = new int[path.size()];
    for (int p = 0; p < path.size(); p++)
        path_[p] = path[p];
    
    if (config == 0)
        QuickSort(path_, 0, path.size() - 1);
    else if (config == 1)
        InsertSort(path_, path.size());
    else if (config == 2)
        MergeSort(path_, 0, path.size() - 1, path.size());
    else if (config == 3)
        HeapSort(path_, path.size());
    else if (config == 4)
        BubbleSort(path_, path.size());

    for (int p = 0; p < path.size(); p++)
        fout << path_[p] << " ";

    int length = m_graph.GetDistance(path);
    fout << endl
        << "path length: " << length << endl
        << "Course : ";

    //course 출력
    fout << endl << "=====================" << endl;

    return Success;
}



Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    if (m_graph.Size() == 0) //exception
        return GraphNotExist; //  GraphNotExist

    if (m_graph.IsNegativeEdge() == true)
        return InvalidAlgorithm;
    if (startVertexKey >= m_graph.Size() || endVertexKey >= m_graph.Size())
        return InvalidVertexKey;

    vector<int> path = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);

    fout << "===== DIJKKSTRA =====" << endl
        << "order: ";
    for (int p = 0; p < path.size(); p++)
        fout << path.at(p) << " ";


    fout << endl
        << "sorted nodes: ";

    int* path_ = new int[path.size()];
    for (int p = 0; p < path.size(); p++)
        path_[p] = path[p];
    if (config == 0)
    {
        //chrono::system_clock::time_point start = chrono::system_clock::now();
        QuickSort(path_, 0, path.size() - 1);
        //chrono::system_clock::time_point end = chrono::system_clock::now();
        //chrono::nanoseconds duration_nano = end - start;
        //printf("Quick: %lld\n", duration_nano);
    }
    else if (config == 1)
    {
        //chrono::system_clock::time_point start = chrono::system_clock::now();
        InsertSort(path_, path.size());
        //chrono::system_clock::time_point end = chrono::system_clock::now();
        //chrono::nanoseconds duration_nano = end - start;
        //printf("Insert: %lld\n", duration_nano);
    }
    else if (config == 2)
    {
        //chrono::system_clock::time_point start = chrono::system_clock::now();
        MergeSort(path_, 0, path.size() - 1, path.size());
        //chrono::system_clock::time_point end = chrono::system_clock::now();
        //chrono::nanoseconds duration_nano = end - start;
        //printf("merge: %lld\n", duration_nano);
    }
    else if (config == 3)
    {
        //chrono::system_clock::time_point start = chrono::system_clock::now();
        HeapSort(path_, path.size());
        //chrono::system_clock::time_point end = chrono::system_clock::now();
        //chrono::nanoseconds duration_nano = end - start;
        //printf("Heap: %lld\n", duration_nano);
    }
    else if (config == 4)
    {
       // chrono::system_clock::time_point start = chrono::system_clock::now();
        BubbleSort(path_, path.size());
        //chrono::system_clock::time_point end = chrono::system_clock::now();
        //chrono::nanoseconds duration_nano = end - start;
    //    printf("Bubble: %lld\n", duration_nano);
    }
    for (int p = 0; p < path.size(); p++)
        fout << path_[p] << " ";
    
    
    int length = m_graph.GetDistance(path);

    fout << endl
        << "path length: " << length << endl
        << "Course : ";

    //course 출력
    fout << endl << "=====================" << endl;

    return Success;
}

Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{

    if (m_graph.Size() == 0) //exception
        return GraphNotExist; //  GraphNotExist

    if (m_graph.IsNegativeEdge() == true)
        return InvalidAlgorithm;
    if (startVertexKey >= m_graph.Size() || endVertexKey >= m_graph.Size() )
        return InvalidVertexKey;

    vector<int> path = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);

    fout << "===== DIJKKSTRAMIN =====" << endl
        << "order: ";
    for (int p = 0; p < path.size(); p++)
        fout << path.at(p) << " ";


    fout << endl
        << "sorted nodes: ";

    int* path_ = new int[path.size()];
    for (int p = 0; p < path.size(); p++)
        path_[p] = path[p];
    if (config == 0)
        QuickSort(path_, 0, path.size() - 1);
    else if (config == 1)
        InsertSort(path_, path.size());
    else if (config == 2)
        MergeSort(path_, 0, path.size() - 1, path.size());
    else if (config == 3)
        HeapSort(path_, path.size());
    else if (config == 4)
        BubbleSort(path_, path.size());    for (int p = 0; p < path.size(); p++)
        fout << path_[p] << " ";
    
    int length = m_graph.GetDistance(path);

    fout << endl
        << "path length: " << length << endl
        << "Course : ";

    //path 
    fout << endl << "=====================" << endl;

    return Success;
}


Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    if (m_graph.Size() == 0)//execption
        return GraphNotExist; //  GraphNotExist
    if (startVertexKey >= m_graph.Size() || endVertexKey >= m_graph.Size())
        return InvalidVertexKey;

    vector<int> path = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey);
    if (path.size()==0)
           return NegativeCycleDetected;

    fout << "===== BELLMANFORD =====" << endl
        << "order: ";
    for (int p = 0; p < path.size(); p++)
        fout << path.at(p) << " ";


    fout << endl
        << "sorted nodes: ";

    int* path_ = new int[path.size()];
    for (int p = 0; p < path.size(); p++)
        path_[p] = path[p];
    if (config == 0)
        QuickSort(path_, 0, path.size() - 1);
    else if (config == 1)
        InsertSort(path_, path.size());
    else if (config == 2)
        MergeSort(path_, 0, path.size() - 1, path.size());
    else if (config == 3)
        HeapSort(path_, path.size());
    else if (config == 4)
        BubbleSort(path_, path.size());    for (int p = 0; p < path.size(); p++)
        fout << path_[p] << " ";
    int length = m_graph.GetDistance(path);

    fout << endl
        << "path length: " << length << endl
        << "Course : ";

    //course
    fout << endl << "=====================" << endl;

    return Success;
}

Result Manager::FindShortestPathFloyd()
{
    if (m_graph.Size() == 0) //exception
        return GraphNotExist; //  GraphNotExist
   
    vector < vector<int> >floyd= m_graph.FindShortestPathFloyd();
    
    fout << "====== FLOYD ======" << endl;
    for (int i = 0; i < m_graph.Size(); i++) {
        for (int j = 0; j < m_graph.Size(); j++)
        {
            fout << floyd[i][j] << " ";
        }
        fout << endl;
    }
    fout << endl << "=====================" << endl;
    return Success;
}

void Manager::QuickSort(int *path, int start, int end)
{
    if (start >= end) //fin
        return;

    int pivot = start; //from start
    int i = pivot + 1; // index for left
    int j = end;  // index for right
    int swap; //for swapping

    while (i <= j) {
        //until pointer meet
        while (i <= end && path[i] <= path[pivot])  // getting big value in left
        {
            i++;
        }
        while (j > start && path[j] >= path[pivot]) // getting small value in right
        {
            j--;
        }
          if (i > j) { 
             //if be crossed
              //change with pivot
            swap = path[j];
            path[j] = path[pivot];
            path[pivot] = swap;
            }
          else {
              //change i, j
                swap = path[i];
                path[i] = path[j];
                path[j] = swap;
            }
    }
    QuickSort(path, start, j - 1); // for left
    QuickSort(path, j + 1, end); //for right
}

void Manager::InsertSort(int* path, int size)
{
    int n; // for key
    int i, j;
        for ( i = 1; i <size; i++) { //loop for key
            n = path[i]; //get key
            for ( j = i - 1; j >= 0; j--) { //loop key's left elements
                if (path[j] > n) {       //if left > key
                    path[j + 1] = path[j];  //shift right 
                }
                else {    // reach sorted values
                    break;
                }
            }
            path[j + 1] = n; // save key in [j+1]
        }
    }

void Manager::HeapSort(int * path, int size)
{
    //using minheap.h
    MinHeap<int, int> h;
    for (int i = 0; i <size; i++)
    {
        h.Push(i, path[i]); //push in heap 
    }
    for (int i = 0; i <size; i++)
    {
        path[i] = h.Top().second; //get min element
        h.Pop(); // pop 
    }
}


void Manager::MergeSort(int *path, int start, int end,int size)
{ 
    if(start < end){ 
        int half = (start+end)/2;  //get middle
        MergeSort(path, start, half,size); // left sort 
       MergeSort(path, half+1, end,size); // right sort
        Merge_(path, start, half, end,size);  //sorting by merge!!
    } 
}

void Manager::Merge_(int* path, int start, int half, int end,int size)
{
    int i = start; // left index
    int j = half + 1; //right index
    int k = start;
    int* path__ = new int[size];

    /*MERGING*/
    while (i <= half && j <= end)
    //decidng kth value 
    {
        if (path[i] <= path[j])
        { 
            path__[k] = path[i];
            i++;
        }
        else { // path[i] > path[j] 
            path__[k] = path[j];
            j++;
        }
        k++;
    }

    //copying
    if (i > half) {
        for (int p = j; p<= end; p++)
        {
            path__[p] = path[p]; 
            k++;
        }
    }
    else
    {
        for (int p = i; p <= half; p++)
        {
            path__[k] = path[p]; 
            k++;
        }
    } 
    
    //  sorted array copy
    for (int p = start; p<= end; p++)
    {
        path[p] = path__[p];
    }
}

void Manager::BubbleSort(int * path, int size)
{
    
    int swap;
    for (int i = size - 1; i > 0; i--) // N-1 count
    {
        for (int j = 0; j < i; j++) {
            if (path[j] > path[j + 1]) { // two value compare
                // need to swap
                swap = path[j];
                path[j] = path[j + 1];
                path[j + 1] = swap;
            }
        }
    }

}
