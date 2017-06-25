#pragma once
#include <string>
#include "BinaryHeapT.h"


class Test
{
private:
	static BinaryHeapT<Edge>* fillDirectEdgeQueue(int size);
	static BinaryHeapT<Edge>* fillUndirectEdgeQueue(int size);
	static int maxWeight;
public:
	static void KruskalAdjList(int size, int density);
	static void PrimAdjList(int size, int density);
	static void KruskalMatrix(int size, int density);
	static void PrimMatrix(int size, int density);
	static void DijkstryAdjList(int size, int density);
	static void DijkstryMatrix(int size, int density);
	static void BellmanFordAdjList(int size, int density);
	static void BellmanFordMatrix(int size, int density);
	static void FulkersonFordDFSMatrix(int size, int denisty);
	static void FulkersonFordDFSAdjList(int size, int density);
	static void FulkersonFordBFSMatrix(int size, int density);
	static void FulkersonFordBFSAdjList(int size, int density);
	static void TestIfConnected(int size, int density);
	static void GenerateGraphs(int size, double density, bool direct);
	static std::string PATH;

};
