#pragma once
#ifndef ARRAY_HEADER
#define ARRAY_HEADER


#include <string>
using namespace std;

class Array
{
private:
	int size;
	int* array;
	void addToBeginning(int x);
	void addToEnd(int x);

public:
	Array(int s = 0);								//Ustawia wszystkie wartosci w tablicy na umowna makysmalna wartosc wag
	~Array();
	int GetSize();
	void PrintData();
	void Add(int x, int index);
	void Insert(int x, int index);
	int Get(int index);
	void Set(int index, int value);
	void Delete(int index);
	bool Search(int value);
	string GetStructureName();
	static Array* LoadDataFromFile(string path);
};

#endif

