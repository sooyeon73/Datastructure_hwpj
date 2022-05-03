#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include "Queue.h"
#include <set>
#include <tuple>
#include <algorithm>
#define BFS_FIRST_PATH
#define INF 987654321
using namespace std;
Graph::Graph()
{
    m_pVHead = new Vertex;  
    m_vSize = 0;
}
Graph::~Graph()
{
    Clear();
}

/// add vertex with vertexNum at the end of the linked list for the vertics
void Graph::AddVertex(int vertexKey)
{
    Vertex* curVer = this->m_pVHead; // from head

    Vertex* newVer = new Vertex(vertexKey); // new ver

    for (int i =0 ; i<vertexKey;i++)
    {
        curVer = curVer->GetNext();
    }
    
   
    curVer->SetNext(newVer);
    m_vSize++;

}

/// add edge from the vertex which the number is startVertexKey to the vertex which the number is endVertexKey
void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight)
{

    Vertex* curVer = FindVertex(startVertexKey);
    curVer->AddEdge(endVertexKey, weight); 
    //Edge Ãß°¡!
}


/// get the vertex which the key is vertexNum
Vertex* Graph::FindVertex(int key)
{
    Vertex* curVer = m_pVHead->GetNext(); // 0th vertex


    for (int i = 0; i <key; i++)
    {
        curVer = curVer->GetNext();
    }
    return curVer;
}

/// get the number of the vertics
int Graph::Size() const
{
    return m_vSize;
}

/// memory free for the vertics
void Graph::Clear()
{
    Vertex* curVer = m_pVHead;
 
    Vertex* delVer = curVer;
    curVer = curVer->GetNext();
    free(delVer);
    for (int i = 0; i < m_vSize; i++)
    {
        Vertex* delVer = curVer;
        curVer = curVer->GetNext();
        delVer->Clear();
        free(delVer);
    }
}

/// print out the graph as matrix form
void Graph::Print(std::ofstream& fout)
{
  

    fout << "====== PRINT =======" << endl;
    Vertex* curVer = m_pVHead->GetNext(); //from 0th

    for (int i = 0; i < m_vSize; i++) // Vertex loop
    {
        Edge* curEdge = curVer->GetHeadOfEdge(); // Edge head

        for (int j = 0; j < m_vSize; j++)
        {
            if (curEdge == NULL||curEdge->GetKey() != j)
            {
                fout << "0 ";
            }
            else
            {
                fout << curEdge->GetWeight() << " ";
                curEdge = curEdge->GetNext(); // next Edge
            }
        }
        fout << endl;
        curVer = curVer->GetNext(); // next Vertex
    }
    fout << "=====================" << endl;

}


/// check whether the graph has negative edge or not.
bool Graph::IsNegativeEdge()
{
    Vertex* curVer = m_pVHead->GetNext(); // 0th ver
    for (int i = 0; i < m_vSize; i++)
    {
        Edge*curEdge= curVer->GetHeadOfEdge(); //0th edge
        int count = curVer->Size();
        for (int k = 0; k < count; k++)
        {
            if (curEdge->GetWeight() < 0)
                return true;
            curEdge = curEdge->GetNext();
        }
        curVer = curVer->GetNext();
    }
    return false;
}


/// find the path from startVertexKey to endVertexKey with BFS using queue
std::vector<int> Graph::FindPathBfs(int startVertexKey, int endVertexKey)
{
    int *prev = new int[m_vSize];  // for saving path
    Queue<int> q;

    Vertex* curVer;
    Edge* curEdge;

    // visited = true
    // unvisited = false
    bool*check = new bool[m_vSize]; // checking visiting
    for (int i = 0; i < m_vSize; i++)
        check[i] = unvisited;

    bool breakpoint = false; //check loop breakpoint

    //init
    prev[startVertexKey] = startVertexKey;
    check[startVertexKey] = visited;
    q.push(startVertexKey);

    while (!q.empty()) // until q empty
    {
        int key = q.val[q.front]; // q's fisrt value
        curVer = FindVertex(key); // finding vertex of key
        q.pop();
        curEdge = curVer->GetHeadOfEdge(); // get Edges of keyVertex

        for (int i = 0; i < curVer->Size(); i++) // loop all adj vertexs
        {
            int keyEdge = curEdge->GetKey(); // destination vertex's key
            if (!check[keyEdge]) //if unvisited
            {
                q.push(keyEdge); // push in queue
                check[keyEdge] = visited; // check visitng
                prev[keyEdge] = key; // saving parent key (key ==> keyEdge)
                if (keyEdge == endVertexKey) // reached endvertex
                {
                    breakpoint = true; //breakout
                    break;
                }
            }
               curEdge = curEdge->GetNext(); // next edge
        }
        if (breakpoint == true) // breakout point
            break;
    }

    //short path
    vector <int> path; //for return
    
    int i = endVertexKey;
    while (i != startVertexKey) //end~~start
    {
        path.push_back(i); // push in path vector
        i = prev[i]; //get parent key
    }
    path.push_back(i); 
    reverse(path.begin(), path.end()); //reverse => start~~end
    return path;

}


/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    Vertex* curVer;
    Edge* curEdge;
    bool breakpoint = false; //for check breakout point
    
    int* prev = new int[m_vSize]; // for saving path 

    set< pair<int, int> > set; //for DIJSKSTRA 
    vector<int> dist(m_vSize, INF); // init as infinite

    //init
    set.insert(make_pair(0, startVertexKey));
    dist[startVertexKey] = 0;
    prev[startVertexKey] = startVertexKey;

    while (!set.empty()) // until set empty
    { 
        pair<int, int> cur = *(set.begin()); // at set first 
        set.erase(cur);
     
        int key = cur.second; // from set's first' key
        curVer = FindVertex(key); // finding vertex of key
        curEdge = curVer->GetHeadOfEdge(); // get edges from vertex

        for (int i = 0; i < curVer->Size(); i++) //  loop all adj vertexs
        {
            int keyEdge = curEdge->GetKey(); // get keyEdge
            int keyWei = curEdge->GetWeight(); //get KeyWight
            if (dist[keyEdge] > dist[key] + keyWei) // need to update short dist
            {
                set.erase(make_pair(dist[keyEdge], keyEdge));
                set.insert(make_pair(dist[key] + keyWei, keyEdge));
                dist[keyEdge] = dist[key] + keyWei; //update short distance
                prev[keyEdge] = key; // saving parent key
            }
             curEdge = curEdge->GetNext();
        }
    }

    //shortpath
    vector <int> path;

    int i = endVertexKey;
    while (i != startVertexKey)//end~~start
    {
        path.push_back(i);
        i = prev[i]; //get parent key
    }
    path.push_back(i); // push in path vector
    reverse(path.begin(), path.end()); //reverse => start~~end
    return path; //for return

}



/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
std::vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
    Vertex* curVer;
    Edge* curEdge;
    bool breakpoint = false; //for checking break point

    int* prev = new int[m_vSize]; //for saving path

    MinHeap<int, int> h; // for dijkstra , using min heap
    vector<int> dist(m_vSize, INF); // vector for saving distance

    //init
    h.Push(startVertexKey,0);
    dist[startVertexKey] = 0;
    prev[startVertexKey] = startVertexKey;

    while (!h.IsEmpty()) //until heap empty
    {
        pair<int, int> cur = (h.Top()); //from heap's first
        h.Pop();

        int key = cur.first; // from heap's min's key
        curVer = FindVertex(key); //find vertex of key
        curEdge = curVer->GetHeadOfEdge(); //get edges from vertexs

        for (int i = 0; i < curVer->Size(); i++)//  loop all adj vertexs
        {
            int keyEdge = curEdge->GetKey(); // get key
            int keyWei = curEdge->GetWeight(); // get weight
            if (dist[keyEdge] > dist[key] + keyWei) // need to update
            {
                dist[keyEdge] = dist[key] + keyWei; //update short dist
                h.Push(keyEdge,(dist[key] + keyWei)); // push current 
                prev[keyEdge] = key; // saving parent key
            }
            curEdge = curEdge->GetNext(); // next edge
        }
    }

    //shortpath
    vector <int> path; // for return

    int i = endVertexKey;
    while (i != startVertexKey) // end~~start
    {
        path.push_back(i);
        i = prev[i]; //get parent key
    }
    path.push_back(i); 
    reverse(path.begin(), path.end()); // start~~end
    return path; 
}

/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    vector<tuple<int, int, int>> edges; 
    //<startvertex, endvertex, weight>

    Vertex* curVer = m_pVHead->GetNext(); // from 0th vertex

    for (int i = 0; i < m_vSize; i++) // loop for vertex
    {
        Edge* curEdge = curVer->GetHeadOfEdge(); // get edges from vertex
        for (int j = 0; j < curVer->Size(); j++) //loop for edges
        {
            edges.push_back({ curVer->GetKey() ,curEdge->GetKey() ,curEdge->GetWeight() });
            //push tuple{startvertexkey, endvertexkey, weight}
            curEdge = curEdge->GetNext(); // next edge
        }
        curVer = curVer->GetNext(); // next Vertex
    }

    bool breakpoint = false; //checking breakout point

    int* prev = new int[m_vSize]; //for saving path
    vector<int> dist(m_vSize, INF); // init infinite

    //init
    dist[startVertexKey] = 0;
    prev[startVertexKey] = startVertexKey;
    bool check = true;

    while (check) 
    { 
        check = false;
        for (int i = 1; i < m_vSize; i++) // size-1 loop
        {
            for (int j = 0; j < edges.size(); j++) // all edges loop
            {
                //get edge datas
                int u = get<0>(edges[j]); // from
                int v = get<1>(edges[j]); // to
                int w = get<2>(edges[j]); // weight
                if (dist[u] != INF && dist[u] + w < dist[v]) //need to update
                {
                    dist[v] = dist[u] + w; // updata short dist
                    prev[v] = u; // saving parent 
                    check = true;
                }
            }
        }
    }
    // checkin negative cycle!!
    for(int j=0; j<edges.size();j++) 
    {
        int u = get<0>(edges[j]);
        int v = get<1>(edges[j]);
        int w = get<2>(edges[j]);
        if (dist[u] != INF && dist[u] + w < dist[v]) // if need to update
        {
            // negative cycle O
            vector<int> error;
            return error;
            // return null vector for error
        }
    }

    //short path
    vector <int> path;

    int i = endVertexKey;
    while (i != startVertexKey) // end~~start
    {
        path.push_back(i);
        i = prev[i]; //get parent key
    }
    path.push_back(i);
    reverse(path.begin(), path.end()); //start~~end
    return path;
  }


std::vector<vector<int> > Graph::FindShortestPathFloyd()
{
     vector<vector<int>> dist(m_vSize, vector<int>(m_vSize, 0));
    //adj matreix as vectory
    //only saving distance
   Vertex* curVer = m_pVHead->GetNext(); // from 0th vertex
    for (int i = 0; i < m_vSize; i++) // loop for vertex
    {
        Edge* curEdge = curVer->GetHeadOfEdge(); // get edges from vertex
        for (int j = 0; j < m_vSize; j++) // loop for edges
        {
            if (i == j) // self 
                dist[i][j] = 0;
            else if (curEdge == NULL || curEdge->GetKey() != j) // none
                dist[i][j] = INF; // init as INF
            else // saving dist
            {
                dist[i][j] = curEdge->GetWeight(); //saving only dist
                curEdge = curEdge->GetNext(); // next edge
            }
        }
        curVer = curVer->GetNext(); // next vertex
    }
     

    // from one vertex 
    for (int p = 0; p < m_vSize; p++)    {
        // from x
        for (int i = 0; i < m_vSize; i++)        {
            //to y
            for (int j = 0; j < m_vSize; j++)            {
                // need update
                if (dist[i][p] + dist[p][j] < dist[i][j]) 
                    dist[i][j] = dist[i][p] + dist[p][j]; //update short dist
            }
        }
    }
    return dist;
}

int Graph::GetDistance(vector<int> path) //for return length
{
    int length = 0;
    for (int p = 0; p < (path.size() - 1); p++) // adding path weight
    {
        Vertex* curVer = FindVertex(path.at(p)); // get vertex from key
        Edge* curEdge = curVer->GetHeadOfEdge(); //get edges
        while (curEdge->GetKey() != path.at(p + 1)) // until reach path edge
            curEdge = curEdge->GetNext(); // move to next
        length += curEdge->GetWeight(); // adding weight
    }
    return length;

}
