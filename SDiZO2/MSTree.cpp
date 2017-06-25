#include "MSTree.h"
#include <iostream>
#include <iomanip>
using namespace std;

MSTree::MSTree(int n)
{
	/*list = new TreeNode *[n];
	for(int i = 0; i < n; i++)
	{
		list[i] = nullptr;
	}
	size = n - 1;
	weight = 0;*/

	list = new DoublyLinkedListEdges*[n];
	for (int i = 0; i < n; i++)
	{
		list[i] = new DoublyLinkedListEdges();
	}
	size = n - 1;
	weight = 0;
}

MSTree::~MSTree()
{
	//TreeNode *ptr, *r;

	//for (int i = 0; i <= size; i++)
	//{
	//	ptr = list[i];
	//	while (ptr)
	//	{
	//		r = ptr;                      
	//		ptr = ptr->Next;               
	//		delete r;                   
	//	}
	//}

/*	delete[] list*/;

	for (int i = 0; i< size; i++)
	{
		delete list[i];
	}
	delete[] list;
             
}

void MSTree::AddEdge(Edge e)
{
	//TreeNode *ptr;

	//weight += e.Weight;							// Do wagi drzewa dodajemy wag� kraw�dzi
	//ptr = new TreeNode;						 // Tworzymy nowy w�ze�
	//ptr->EndVertex = e.End;                    // Wierzcho�ek ko�cowy
	//ptr->Weight = e.Weight;				  // Waga kraw�dzi
	//ptr->Next = list[e.Start];              // Dodajemy ptr do listy wierzcho�ka v1
	//list[e.Start] = ptr;

	//ptr = new TreeNode;					 // To samo dla kraw�dzi odwrotnej
	//ptr->EndVertex = e.Start;             // Wierzcho�ek ko�cowy
	//ptr->Weight = e.Weight;				// Waga kraw�dzi
	//ptr->Next = list[e.End];              // Dodajemy ptr do listy wierzcho�ka v2
	//list[e.End] = ptr;

	Edge eReverse;
	eReverse.Start = e.End;
	eReverse.End = e.Start;
	eReverse.Weight = e.Weight;

	if (e.Start < size && e.End< size)
	{
		int size = list[e.Start]->GetSize();
		list[e.Start]->Add(e, size - 1);

		size = list[eReverse.Start]->GetSize();
		list[eReverse.Start]->Add(eReverse, size - 1);
	}

	weight += e.Weight;
}

//DoublyLinkedListEdges* MSTree::GetAdjacencyList(int n)
//{
//	return list[n];
//}

void MSTree::PrintData()
{
	Node *ptr;

	std::cout << endl;
	cout << setw(10) << left << "Value:" << "Weight: " << endl;
	for (int i = 0; i <= size; i++)
	{
		for (ptr = list[i]->GetHead(); ptr; ptr = ptr->Next)
		{
			string temp = "(" + std::to_string(i) + ", " + std::to_string((ptr->Value.End)) + ")";
			cout << setw(10) << left << temp << setw(10) << left << ptr->Value.Weight << endl;
		}
	}
	cout << endl << endl << "MST = " << weight << endl << endl;
}
