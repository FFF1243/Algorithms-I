#pragma once
#include <string>

#ifndef BINARY_HEAPT_HEADER
#define BINARY_HEAPT_HEADER
class Edge;
template <class T>
class BinaryHeapT
{
private:
	T* array;
	int heapSize;
	int size;
	int getLeftChild(int index);
	int getRightChild(int index);
	int getParent(int index);
	void printBT(std::string sp, std::string sn, std::string cr, std::string cp, std::string cl, int v);		// Zrodlo: eduinf.waw.pl/inf/alg/001_search/0113.php
public:
	inline BinaryHeapT(int size = 0);
	~BinaryHeapT();
	inline void PrintData();
	inline void Add(T value);
	inline T GetFront();
	inline void Delete();
	inline bool Search(T value);
	inline int GetSize();
	inline int GetIndex(T item);
	inline void DeleteFrom(int index);
	//inline void Update(T Value);
};

class Edge
{
public:
	int Start;
	int End;
	int Weight;
	bool operator==(const Edge & edge);								//Przeciazony operator porownania
	bool operator<(const Edge & edge);
	bool operator>(const Edge & edge);
	friend std::ostream& operator<<(std::ostream & s, const Edge & edge);
};

class VertexPath
{
public:
	int Vertex;
	long int* Weight;

	friend std::ostream& operator<<(std::ostream & s, const VertexPath & edge);
	bool operator<(const VertexPath & right);
	bool operator>(const VertexPath & right);
	bool operator==(const VertexPath & right);
	~VertexPath();
//	void UpdateWeight(const VertexPath & right);
	//bool operator==(const VertexPath & edge);
};

#endif#pragma once
