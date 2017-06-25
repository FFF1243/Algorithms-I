#pragma once
#include <string>
#include "BinaryHeapT.h"
#ifndef DOUBLYLINKEDLISTEDGES_HEADER
#define DOUBLYLINKEDLISTEDGES_HEADER
class EdgeNode;
class DoublyLinkedListEdges 
{
private:
	int size;
	EdgeNode* head;
	EdgeNode* tail;
	void addToBeginning(Edge value);
	//void addToEnd(Edge value);

public:
	DoublyLinkedListEdges();
	DoublyLinkedListEdges(Edge value);

	int GetSize();
	EdgeNode* GetHead();
	void PrintData();
	void Add(Edge value, int index);
	void addToEnd(Edge value);
	void Delete(int index);
	bool Search(Edge value);

	~DoublyLinkedListEdges();
};


class EdgeNode
{
public:
	EdgeNode(EdgeNode* prev, Edge val, EdgeNode* next);
	EdgeNode();
	~EdgeNode();
	Edge Value;
	EdgeNode* Previous;
	EdgeNode* Next;
};

#endif
