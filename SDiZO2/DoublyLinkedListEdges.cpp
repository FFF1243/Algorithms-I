#include "DoublyLinkedListEdges.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
void DoublyLinkedListEdges::addToBeginning(Edge value)
{
	if(head)
	{
		EdgeNode* temp = new EdgeNode(nullptr, value, head);
		head->Previous = temp;
		head = temp;
	}
	else
	{														/*Jesli head i tail == null czyli po usunieciu wszystkich elementow tablicy*/
		head = new EdgeNode(nullptr, value, tail);
		tail = head;
	}
	size++;
}

void DoublyLinkedListEdges::addToEnd(Edge value)
{
	if(tail)																		
	{
		EdgeNode* temp = new EdgeNode(tail, value, nullptr);
		tail->Next = temp;
		tail = temp;
	}
	else													/*Jesli head i tail == null czyli po usunieciu wszystkich elementow tablicy*/
	{
		head = new EdgeNode(nullptr, value, tail);
		tail = head;
	}
	size++;
}

DoublyLinkedListEdges::DoublyLinkedListEdges()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

DoublyLinkedListEdges::DoublyLinkedListEdges(Edge value)
{
	size = 1;
	head = new EdgeNode(nullptr, value, nullptr);
	tail = head;
}

DoublyLinkedListEdges::~DoublyLinkedListEdges()
{
	EdgeNode* temp = head;
	if (head)
		delete head;
}

int DoublyLinkedListEdges::GetSize()
{
	return size;
}

EdgeNode* DoublyLinkedListEdges::GetHead()
{
	return head;
}

void DoublyLinkedListEdges::PrintData()
{
	EdgeNode* temp = head;
	if(temp)
	{
		while (temp->Next)
		{
			cout << setw(4) << right <<temp->Value.Weight <<setw(5) <<" -> " << temp->Value.End;
			temp = temp->Next;
		}
		cout << setw(4) << right <<temp->Value.Weight << setw(5) << " -> " << temp->Value.End << endl;
	}
	else
	{
		//cout << "Nie ma zadnych elementow w strukturze" << endl;
		cout << endl;
		return;
	}

}

void DoublyLinkedListEdges::Add(Edge value, int index)
{
	if(index == 0)
	{
		addToBeginning(value);
	}
	else if(index == size - 1)
	{
		addToEnd(value);
	}
	else
	{
		EdgeNode* temp = head;
		for(int i = 0; i < index; i++)
		{
			temp = temp->Next;
		}
		EdgeNode* newNode = new EdgeNode(temp->Previous, value, temp);
		(temp->Previous)->Next = newNode;
		temp->Previous = newNode;
		size++;
	}

}

void DoublyLinkedListEdges::Delete(int index)
{
	EdgeNode* temp = head;
	if(size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else if (index == 0)
	{
		(temp->Next)->Previous = nullptr;
		head = temp->Next;
		delete temp;
	}
	else if (index == size - 1)
	{
		temp = tail;
		(temp->Previous)->Next = nullptr;
		tail = temp->Previous;
		delete temp;
	}
	else
	{
		for (int i = 0; i < index; i++)
		{
			temp = temp->Next;
		}
		(temp->Next)->Previous = temp->Previous;
		(temp->Previous)->Next = temp->Next;
		delete temp;
	}

	size--;
}


bool DoublyLinkedListEdges::Search(Edge value)
{
	EdgeNode *temp = head;
	do
	{
		if(temp->Value == value)
		{
			return true;
		}
		temp = temp->Next;
	} while (temp);
	return false;
}

//DoublyLinkedListEdges* DoublyLinkedListEdges::LoadDataFromFile(string path)
//{
//	int size, temp;
//	DoublyLinkedListEdges* structure = nullptr;
//	fstream file;
//	file.open(path, ios::in);
//
//	if (file.is_open())
//	{
//		file >> size;
//		if (file.fail())
//		{
//			cout << "FILE ERROR - READ SIZE" << endl;
//			return nullptr;
//		}
//		else
//		{
//			for (int i = 0; i < size; i++)
//			{
//				file >> temp;
//				if (file.fail())
//				{
//					cout << "FILE ERROR - READ DATA" << endl;
//					return nullptr;
//				}
//				if(i == 0)
//				{
//					structure = new DoublyLinkedListEdges(temp);
//				}
//				else
//				{
//					structure->addToEnd(temp);
//				}	
//			}
//		}
//		file.close();
//	}
//	else
//	{
//		cout << "FILE ERROR - OPEN FILE" << endl;
//	}
//
//	return structure;
//}

EdgeNode::EdgeNode(EdgeNode* prev, Edge val, EdgeNode* next) : Value(val), Previous(prev), Next(next)
{

}

EdgeNode::EdgeNode()
{
	Previous = nullptr;
	Next = nullptr;
	Value = Edge();
}

EdgeNode::~EdgeNode()
{
	/*if (this->Next)
		delete this->Next;*/
}
