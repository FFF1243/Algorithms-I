#pragma once
#include <string>
#ifndef DOUBLYLINKEDLIST_HEADER
#define DOUBLYLINKEDLIST_HEADER
class Node;
class DoublyLinkedList
{
private:
	int size;
	Node* head;
	Node* tail;
	void addToBeginning(int value);


public:
	DoublyLinkedList();
	DoublyLinkedList(int value);
	~DoublyLinkedList();

	int GetSize();
	void PrintData();
	void Add(int value, int index);
	void addToEnd(int value);
	Node* GetHead();
	void Delete(int index);
	std::string GetStructureName();
	bool Search(int value);
	static DoublyLinkedList* LoadDataFromFile(std::string path);
};


class Node
{
public:
	Node(Node* prev, int val, Node* next);
	int Number;
	Node* Previous;
	Node* Next;
};

#endif
