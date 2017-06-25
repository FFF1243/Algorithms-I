#include "Test.h"
#include <string>
#include "AdjacencyList.h"
#include "HelperMethods.h"
#include <random>
#include "Matrix.h"
#include <iostream>
#include <windows.h>


BinaryHeapT<Edge>* Test::fillDirectEdgeQueue(int size)
{
	BinaryHeapT<Edge>* heap = new BinaryHeapT<Edge>(size * (size - 1));
	std::random_device	rd; // non-deterministic generator
	std::mt19937 gen(rd()); // random engine seeded with rd()
	std::uniform_int_distribution<> dist(0, size * (size - 1));
	Edge tempEdge;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i != j)
			{
				tempEdge.Start = i;
				tempEdge.End = j;
				tempEdge.Weight = dist(gen);
				heap->Add(tempEdge);
			}
		}
	}
	return heap;
}

BinaryHeapT<Edge>* Test::fillUndirectEdgeQueue(int size)
{
	BinaryHeapT<Edge>* heap = new BinaryHeapT<Edge>(size * (size - 1) / 2);
	std::random_device	rd; // non-deterministic generator
	std::mt19937 gen(rd()); // random engine seeded with rd()
	std::uniform_int_distribution<> dist(0, size * (size - 1) / 2);
	Edge tempEdge;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (i != j)
			{
				tempEdge.Start = i;
				tempEdge.End = j;
				tempEdge.Weight = dist(gen);
				heap->Add(tempEdge);
			}
		}
	}
	return heap;
}

void Test::KruskalAdjList(int size, int density)
{
	long long int start, stop;
	AdjacencyList* adjList = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Undirect\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		adjList = AdjacencyList::ReadFromFile(path, false);

		start = HelperMethods::ReadQPC();
		adjList->Kruskal();
		stop = HelperMethods::ReadQPC();
	//	HelperMethods::SaveToCsv("KruskalAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete adjList;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("KruskalAdjAvg", size, avg, density);
}

void Test::PrimAdjList(int size, int density)
{
	long long int start, stop;
	AdjacencyList* adjList = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Undirect\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		adjList = AdjacencyList::ReadFromFile(path, false);

		start = HelperMethods::ReadQPC();
		adjList->Prim();
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("PrimAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete adjList;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("PrimAdjAvg", size, avg, density);
}

void Test::KruskalMatrix(int size, int density)
{
	long long int start, stop;
	Matrix* matrix = nullptr;
	std::string path = PATH + "Undirect\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Undirect\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		matrix = Matrix::ReadDataFromFile(path, false);
		start = HelperMethods::ReadQPC();
		matrix->Kruskal();
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("KruskalMatrix", matrix->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete matrix;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("KruskalMatrixAvg",size, avg, density);

}

void Test::PrimMatrix(int size, int density)
{
	long long int start, stop;
	Matrix* matrix = nullptr;
	std::string path = PATH + "Undirect\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Undirect\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		matrix = Matrix::ReadDataFromFile(path, false);
		start = HelperMethods::ReadQPC();
		matrix->Prim();
		stop = HelperMethods::ReadQPC();
	//	HelperMethods::SaveToCsv("PrimMatrix", matrix->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete matrix;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("PrimMatrixAvg", size, avg, density);
}

void Test::DijkstryAdjList(int size, int density)
{
	long long int start, stop;
	AdjacencyList* adjList = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Direct\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		adjList = AdjacencyList::ReadFromFile(path, true);

		start = HelperMethods::ReadQPC();
		adjList->Dijkstry();
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("DijkstryAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete adjList;
		adjList = nullptr;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("DijkstryAdjAvg", size, avg, density);
}

void Test::DijkstryMatrix(int size, int density)
{
	long long int start, stop;
	Matrix* matrix = nullptr;
	std::string path = PATH + "Direct\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Direct\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		matrix = Matrix::ReadDataFromFile(path, true);
		start = HelperMethods::ReadQPC();
		matrix->Dijkstry();
		stop = HelperMethods::ReadQPC();
	//	HelperMethods::SaveToCsv("DijkstryMatrix", matrix->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete matrix;
		matrix = nullptr;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("DijkstryMatrixAvg", size, avg, density);
}

void Test::BellmanFordAdjList(int size, int density)
{
	long long int start, stop;
	AdjacencyList* adjList = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Direct\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		adjList = AdjacencyList::ReadFromFile(path, false);

		start = HelperMethods::ReadQPC();
		adjList->BellmanFord();
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("DijkstryAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete adjList;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("BellmanFordAdjAvg", size, avg, density);
}

void Test::BellmanFordMatrix(int size, int density)
{
	long long int start, stop;
	Matrix* matrix = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Direct\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		matrix = Matrix::ReadDataFromFile(path, false);
		start = HelperMethods::ReadQPC();
		matrix->BellmanFord();
		stop = HelperMethods::ReadQPC();
		//	HelperMethods::SaveToCsv("DijkstryMatrix", matrix->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete matrix;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("BellmanFordMatrixAvg", size, avg, density);
}

void Test::FulkersonFordDFSMatrix(int size, int density)
{
	long long int start, stop;
	Matrix* matrix = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Direct\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		matrix = Matrix::ReadDataFromFile(path, false);
		start = HelperMethods::ReadQPC();
		matrix->FulkersonDFS();
		stop = HelperMethods::ReadQPC();
		//	HelperMethods::SaveToCsv("DijkstryMatrix", matrix->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete matrix;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("FulkersonFordDFSMatrixAvg", size, avg, density);
}

void Test::FulkersonFordDFSAdjList(int size, int density)
{
	long long int start, stop;
	AdjacencyList* adjList = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Direct\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		adjList = AdjacencyList::ReadFromFile(path, false);

		start = HelperMethods::ReadQPC();
		adjList->FulkersonDFS();
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("DijkstryAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete adjList;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("FulkersonFordDFSAdjAvg", size, avg, density);
}

void Test::FulkersonFordBFSMatrix(int size, int density)
{
	long long int start, stop;
	Matrix* matrix = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Direct\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		matrix = Matrix::ReadDataFromFile(path, false);
		start = HelperMethods::ReadQPC();
		matrix->FulkersonBFS();
		stop = HelperMethods::ReadQPC();
		//	HelperMethods::SaveToCsv("DijkstryMatrix", matrix->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete matrix;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("FulkersonFordBFSMatrixAvg", size, avg, density);
}

void Test::FulkersonFordBFSAdjList(int size, int density)
{
	long long int start, stop;
	AdjacencyList* adjList = nullptr;
	std::string path;
	double avg = 0.0;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Direct\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		adjList = AdjacencyList::ReadFromFile(path, false);

		start = HelperMethods::ReadQPC();
		adjList->FulkersonBFS();
		stop = HelperMethods::ReadQPC();
		//HelperMethods::SaveToCsv("DijkstryAdj", adjList->GetVertexes(), HelperMethods::GetElapsedTime(start, stop), density);
		avg += HelperMethods::GetElapsedTime(start, stop);
		delete adjList;
	}
	avg = avg / 100.0;
	HelperMethods::SaveAvg("FulkersonFordBFSAdjAvg", size, avg, density);
}

void Test::TestIfConnected(int size, int density)
{
	AdjacencyList* adjList = nullptr;
	std::string path;
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Undirect\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		adjList = AdjacencyList::ReadFromFile(path, false);

		if(adjList->IsConnected())
		{
			//cout << "Size: " << size << " Density: " << density << " File: " << i << "OK" << endl;
		}
		else
		{
			cout << "Size: " << size << " Density: " << density << " File: " << i << "Zle" << endl;
		}

		delete adjList;
	}
	for (int i = 0; i < 100; i++)
	{
		path = PATH + "Direct\\" + std::to_string(density) + "\\" + std::to_string(size) + "\\";
		path.append(std::to_string(i) + ".txt");
		adjList = AdjacencyList::ReadFromFile(path, false);

		if (adjList->IsConnected())
		{
			//cout << "Size: " << size << " Density: " << density << " File: " << i << "OK" << endl;
		}
		else
		{
			cout << "Size: " << size << " Density: " << density << " File: " << i << "Zle" << endl;
		}

		delete adjList;
	}
}


void Test::GenerateGraphs(int size, double density, bool direct)
{
	BinaryHeapT<Edge>* allEdges;
	AdjacencyList* checkList;
	std::fstream file;
	std::string path;
	bool connected = true;
	int edg;
	if (direct)
		edg = (size * (size - 1)) * density;
	else
		edg = (size * (size - 1)) / 2 * density;

	std::random_device	rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distWeight(0, edg);
	std::uniform_int_distribution<> distVer(0, size - 1);

	for (int i = 0; i < 100; i++)
	{
		if(direct)
		{
			allEdges = fillDirectEdgeQueue(size);
			path = PATH + "Direct\\" +std::to_string( (int)(density * 100) ) + "\\"+ std::to_string(size);
		}
		else
		{
			allEdges = fillUndirectEdgeQueue(size);
			path = PATH + "Undirect\\" + std::to_string((int)(density * 100)) + "\\" + std::to_string(size);
		}

		path.append("\\" + std::to_string(i) + ".txt");

		do
		{
			file.open(path.c_str(), std::ios::out | std::ios::trunc);
			if (file.good())
			{
				for (int j = 0; j < edg; j++)
				{
					if (j == 0)
					{
						file << edg << " " << size << " " << distVer(gen) << " " << distVer(gen) << std::endl;
					}
					file << allEdges->GetFront().Start << " " << allEdges->GetFront().End << " " << distWeight(gen) << std::endl;
					allEdges->Delete();
				}
				file.close();
			}
				checkList = AdjacencyList::ReadFromFile(path, direct);
				connected = checkList->IsConnected();
		} while (!connected);
	

		delete allEdges;
	}
}

std::string Test::PATH = "D:\\PWR\\SDiZO\\Projekt2Dane2\\";
int Test::maxWeight = 20;