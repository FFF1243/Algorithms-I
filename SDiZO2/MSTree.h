#pragma once
#include "DoublyLinkedListEdges.h"

#ifndef MSTREE_HEADER
#define MSTREE_HEADER
//class TreeNode
//{
//public:
//	TreeNode* Next;
//	int EndVertex;
//	int Weight;
//};
//class MSTree
//{
//private:
//	TreeNode** list;
//	int weight;
//	int size;
//public:
//	MSTree(int n);
//	~MSTree();
//	void AddEdge(Edge e);
//	TreeNode* GetAdjacencyList(int n);
//	void PrintData();
//};

class MSTree
{
private:
	DoublyLinkedListEdges** list;
	int weight;
	int size;
public:
	MSTree(int n);
	~MSTree();
	void AddEdge(Edge e);
	void PrintData();
};
#endif