#pragma once

#include "DoublyLinkedListEdges.h"

#ifndef ADJ_LISTHEADER
#define ADJ_LISTHADER
class AdjacencyList
{
private:
	DoublyLinkedListEdges** list;
	int edges;
	int vertexes;
	int graph_start;												//Wierzcholek startowy
	int graph_end;													//Wierzcholek koncowy
	bool directed;
	
public:
	AdjacencyList(int edg, int ver);												//Alokuje miejsce dla list sasiedztwa
	bool IsConnected();																//Sprawdza czy wczytany graf jest spojny
	void InsertEdge(int start, int end, int weight);								//Wstawia krawedz do odpowiedniej listy sasiedztwa
	void PrintData();
	void PrintMST();

	void Kruskal();
	void Prim();
	void Dijkstry();
	void DijkstryHeap();
	void BellmanFord();
	void FulkersonBFS();
	void FulkersonDFS();

	int GetEdges();
	int GetVertexes();
	void SetGraphStart(int i);
	void SetGraphEnd(int i);
	void SetDirected(bool dir);

	static AdjacencyList* ReadFromFile(std::string path,bool directed);
	~AdjacencyList();
};
#endif