#pragma once
#include "Array.h"
#include "BinaryHeapT.h"
#include "DoublyLinkedList.h"
#ifndef MATRIX_HEADER
#define MATRIX_HEADER
class Matrix
{
private:
	Array** matrix;
	int edges;
	int vertexes;
	int graph_start;
	int graph_end;
	bool directed;
public:
	Matrix(int edg, int ver);											//Rezerwuje miejsce dla macierzy, wywoluje konstruktor klasy Array
	void InsertEdge(int start, int end, int val);						//Wstawia krawedz do podanego miejsca w grafie
	Edge GetEdge(int start, int end);

	void Kruskal();
	void Prim();
	void Dijkstry();
	void DijkstryHeap();
	void BellmanFord();
	void FulkersonBFS();
	void FulkersonDFS();
	void PrintData();

	int GetEdges();
	int GetVertexes();
	void SetGraphStart(int ver);
	void SetGraphEnd(int ver);
	static Matrix* ReadDataFromFile(std::string path, bool directed);
	~Matrix();

};
#endif