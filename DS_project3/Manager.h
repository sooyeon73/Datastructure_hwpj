#define _CRT_SECURE_NO_WARNINGS

#ifndef SOLUTION_H
#define SOLUTION_H

#include "Result.h"
#include "Graph.h"
#include <fstream>

class Manager
{
private:
    // the filepath for the result log
    const char* RESULT_LOG_PATH = "log.txt";
    // the filepath for the error log
    const char* ERROR_LOG_PATH = "log.txt";
    int config;

    // the file stream for the result log
    std::ofstream fout;
    // the file stream for the error log
    std::ofstream ferr;

    // the file stream for opening command
    std::ifstream fin;
    // the file stream for opening data
    std::ifstream fin2;

    // graph instance to manage the vertics.
    Graph m_graph;

public:
    Manager() { config = 0; }
    ~Manager();

    void Run(const char* filepath);
    void PrintError(Result result);

private:
    Result Load(const char* filepath);
    Result Print();
    Result Update();
    Result FindPathBfs(int startVertexKey, int endVertexKey);
    Result FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey);
    Result FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey);
    Result FindShortestPathBellmanFord(int startVertexKey, int endVertexKey);
    Result FindShortestPathFloyd();
    Result RabinKarpCompare(const char* CompareString, const char* ComparedString);
    Result RabinKarpCompareW(const char* CompareString, const char* ComparedString);

    void QuickSort(int* arr,int start, int end);
    void InsertSort(int* arr, int size);
    void MergeSort(int*arr, int start, int end, int size);
    void Merge_(int* path, int start, int half, int end, int size);
    void HeapSort(int *arr, int size);
    void BubbleSort(int*arr, int size);
  
};

#endif