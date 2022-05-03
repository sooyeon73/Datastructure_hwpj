#include "Vertex.h"
Vertex::Vertex() // constructor
{
    m_key = 0; m_size = 0;
    m_pEHead = NULL;
    m_pNext = NULL;

    owner = new char[20];
    store = new char[40];

}

Vertex::Vertex(int key) // constructor with key
{
    m_key = key;  m_size = 0;

    m_pEHead = NULL;
    m_pNext = NULL;
                    

    owner = new char[20];
    store = new char[40];
}
Vertex::~Vertex()
{
    delete[] owner;
    delete[] store;
}

/// <summary>
/// add edge with edgeNum at the end of the linked list for the edges
/// </summary>
///
/// <param name="edgeKey">
/// the key of the vertex for the edge
/// </param>
/// <param name="weight">
/// the weight of the edge
/// </param>
void Vertex::AddEdge(int edgeKey, int weight)
{

    if (this->m_size == 0) // if head
    {
        m_pEHead = new Edge(edgeKey, weight);
    }
    else
    {
        Edge* curEdge = m_pEHead; // from head

        while (curEdge->GetNext() != NULL)
        {
            curEdge = curEdge->GetNext(); // next edge
        }
        Edge* newEdge = new Edge(edgeKey, weight);
        curEdge->SetNext(newEdge);
    }
    m_size++;
}

/// <summary>
/// get the head pointer of the edge
/// </summary>
///
/// <returns>
/// the ehad pointer of the edge
/// </returns>
Edge* Vertex::GetHeadOfEdge() const
{
    return this->m_pEHead;

}
/// <summary>
/// memory free for edges
/// </summary>
void Vertex::Clear()
{
    Edge* curEdge = m_pEHead;

    for (int i = 0; i < m_size; i++)
    {
        Edge* delEdge = curEdge;
        curEdge = curEdge->GetNext();
        delete[] delEdge;
    }
    m_size = 0;
}