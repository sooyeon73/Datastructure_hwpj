#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>

template<typename TKey, typename TValue>
class MinHeap
{
private:
    // array for the elements which should be heap-sorted
    std::vector<std::pair<TKey, TValue>> m_vec;

public:
    MinHeap() {}

    void Up(int i)
    {
        if (i == 0)
            return;
        int parent = (i - 1) / 2;
        if (m_vec[parent].second > m_vec[i].second)
        {
            std::pair<TKey, TValue> temp = m_vec[parent];
            m_vec[parent]= m_vec[i];
            m_vec[i] = temp;
            Up(parent);
        }
        return;
    }  
    void Push(TKey key, TValue value)
    {
        int length = m_vec.size();
        std::pair<TKey, TValue> p = make_pair(key, value);
        m_vec.push_back(p);
        Up(length);    
    }
   
    void Pop()
    {
        if (IsEmpty())
            return;
        int length = m_vec.size();
        m_vec[0] = m_vec[length - 1];
        m_vec.pop_back();
        Heapify();
    }
   
    std::pair<TKey, TValue> Top()
    {
        return m_vec[0];
    }

    std::pair<TKey, TValue> Get(TValue target);

    bool IsEmpty()
        {
            return (m_vec.size() == 0);
        }
  
    void DecKey(TValue target, TKey newKey);

private:
    void Heapify()
    {
        for (int k = 1; k < m_vec.size(); k++)
        {
            int n = k; //child
            do {
                int root = (n - 1) / 2;  //parent
                //if parent<child
                if (m_vec[root].second > m_vec[n].second) {
                //swap!
                std::pair<TKey, TValue> temp = m_vec[root];
                m_vec[root] = m_vec[n];
                m_vec[n] = temp;
                }
                n = root;
            } while (n != 0);
        }
    }
};

#endif