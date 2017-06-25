#include "DoublyLinkedList.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
void DoublyLinkedList::addToBeginning(int value)
{
	if(head)
	{
		Node* temp = new Node(nullptr, value, head);
		head->Previous = temp;
		head = temp;
	}
	else
	{														/*Jesli head i tail == null czyli po usunieciu wszystkich elementow tablicy*/
		head = new Node(nullptr, value, tail);
		tail = head;
	}
	size++;
}

DoublyLinkedList::DoublyLinkedList()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

void DoublyLinkedList::addToEnd(int value)
{
	if(tail)																		
	{
		Node* temp = new Node(tail, value, nullptr);
		tail->Next = temp;
		tail = temp;
	}
	else													/*Jesli head i tail == null czyli po usunieciu wszystkich elementow tablicy*/
	{
		head = new Node(nullptr, value, tail);
		tail = head;
	}
	size++;
}

Node* DoublyLinkedList::GetHead()
{
	return head;
}

DoublyLinkedList::DoublyLinkedList(int value)
{
	size = 1;
	head = new Node(nullptr, value, nullptr);
	tail = head;
}

DoublyLinkedList::~DoublyLinkedList()
{
	Node* temp = head;
	do
	{
		if(temp->Next)
		{
			temp = temp->Next;
			delete temp->Previous;
		}
		else
		{
			delete temp;
		}
	} while (temp->Next);
}

int DoublyLinkedList::GetSize()
{
	return size;
}

void DoublyLinkedList::PrintData()
{
	Node* temp = head;
	if(temp)
	{
		while (temp->Next)
		{
			cout << setw(5) << temp->Number;
			temp = temp->Next;
		}
		cout << setw(5) << temp->Number << endl;
	}
	else
	{
		cout << "Nie ma zadnych elementow w strukturze" << endl;
	}

}

void DoublyLinkedList::Add(int value, int index)
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
		Node* temp = head;
		for(int i = 0; i < index; i++)
		{
			temp = temp->Next;
		}
		Node* newNode = new Node(temp->Previous, value, temp);
		(temp->Previous)->Next = newNode;
		temp->Previous = newNode;
		size++;
	}

}

void DoublyLinkedList::Delete(int index)
{
	Node* temp = head;
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

std::string DoublyLinkedList::GetStructureName()
{
	return "Lista dwukierunkowa";
}

bool DoublyLinkedList::Search(int value)
{
	Node *temp = head;
	do
	{
		if(temp->Number == value)
		{
			return true;
		}
		temp = temp->Next;
	} while (temp);
	return false;
}

DoublyLinkedList* DoublyLinkedList::LoadDataFromFile(string path)
{
	int size, temp;
	DoublyLinkedList* structure = nullptr;
	fstream file;
	file.open(path, ios::in);

	if (file.is_open())
	{
		file >> size;
		if (file.fail())
		{
			cout << "FILE ERROR - READ SIZE" << endl;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				file >> temp;
				if (file.fail())
				{
					cout << "FILE ERROR - READ DATA" << endl;
					break;
				}
				if(i == 0)
				{
					structure = new DoublyLinkedList(temp);
				}
				else
				{
					structure->addToEnd(temp);
				}	
			}
		}
		file.close();
	}
	else
	{
		cout << "FILE ERROR - OPEN FILE" << endl;
	}

	return structure;
}

Node::Node(Node* prev, int val, Node* next) : Number(val), Previous(prev), Next(next)
{

}
