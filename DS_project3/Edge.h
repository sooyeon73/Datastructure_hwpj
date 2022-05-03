#ifndef EDGE_H
#define EDGE_H

#ifndef NULL
#define NULL	0
#endif

class Edge
{
private:
    // the key of this edge
    int m_key;
    // the weight of this edge
    int m_weight;
    // the next pointer for the linked list of the edges
    Edge* m_pNext;

public:
	/// constructor
    Edge()
    {
        m_key = 0; m_weight = 0;
        m_pNext = NULL;
    };

	/// copy constructor
    Edge(int key, int weight)
    {
        m_key = key; m_weight = weight;
        m_pNext = NULL;
    }
   
    /// set the next pointer of this edge
    void SetNext(Edge* pNext)
    {
        this->m_pNext = pNext;
    }
    
    void SetWeight(int weight)
    {
        this->m_weight = weight;
    }

    /// get the key of this edge
    int GetKey() const
    {
        return this->m_key;
    }

    /// get the weight of this edge
    int GetWeight() const
    {
        return this->m_weight;
    }

    /// get the next pointer of this edge
    Edge* GetNext() const
    {
        return this->m_pNext;
    }
};

#endif