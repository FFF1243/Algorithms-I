#include "Matrix.h"
#include <iostream>
#include <fstream>
#include "HelperMethods.h"
#include <iomanip>
#include "DisjointSet.h"
#include "MSTree.h"
#include "AdjacencyList.h"


using namespace std;

int Matrix::GetEdges()
{
	return edges;
}

int Matrix::GetVertexes()
{
	return vertexes;
}

Edge Matrix::GetEdge(int start, int end)
{
	int weight;
	Edge* edge = new Edge();
	if(start < vertexes && end < vertexes)
	{
		weight = matrix[start]->Get(end);
	}
	edge->Start = start;
	edge->End = end;
	edge->Weight = weight;

	return *edge;
}

void Matrix::Kruskal()
{
	DisjointSet* ds = new DisjointSet(vertexes);
	BinaryHeapT<Edge>* queEdges = new BinaryHeapT<Edge>(edges);
	AdjacencyList* msTree = new AdjacencyList(vertexes - 1, vertexes);
	msTree->SetDirected(true);

	for (int i = 0; i < vertexes; i++)
	{
		ds->MakeSet(i);
	}
	for (int i = 0; i < vertexes; i++)
	{
		for (int k = 0; k < vertexes; k++)
		{
			Edge edge = this->GetEdge(i, k);
			if (edge.Weight < HelperMethods::MAX_WEIGHT)
			{
				queEdges->Add(edge);
			}
		}
	}

	Edge temp;
	for (int i = 1; i < vertexes; i++)
	{
		do
		{
			temp = queEdges->GetFront();
			queEdges->Delete();
		} while (ds->FindSet(temp.Start) == ds->FindSet(temp.End) && queEdges->GetSize() > 0);
		msTree->InsertEdge(temp.Start, temp.End, temp.Weight);
		ds->UnionSets(temp);
	}

	msTree->PrintMST();
}

void Matrix::Prim()
{
	BinaryHeapT<Edge>* queEdges = new BinaryHeapT<Edge>(edges);
	AdjacencyList* msTree = new AdjacencyList(vertexes - 1, vertexes);
	msTree->SetDirected(true);

	bool* visited = new bool[vertexes];
	for(int i = 0; i < vertexes; i++)
	{
		visited[i] = false;
	}

	int vertex = 0;
	visited[vertex] = true;

	Edge temp;
	for (int i = 1; i < vertexes; i++)
	{
		int endIndex = 0;
		int l = 0;
		int weight = HelperMethods::MAX_WEIGHT;
		while (l < vertexes)
		{
			weight = matrix[vertex]->Get(l);
			if (weight < HelperMethods::MAX_WEIGHT)
			{
				endIndex = l;
			}
			else
			{
				l++;
				continue;
			}
			if (!visited[endIndex])
			{
				temp.Weight = weight;
				temp.Start = vertex;
				temp.End = endIndex;
				queEdges->Add(temp);
			}
			l++;
		}
		do
		{
			temp = queEdges->GetFront();
			queEdges->Delete();
		} while (visited[temp.End] && queEdges->GetSize() > 0);
		msTree->InsertEdge(temp.Start, temp.End, temp.Weight);
		visited[temp.End] = true;
		vertex = temp.End;
	}

	msTree->PrintMST();
}

void Matrix::Dijkstry()
{
	long long int * costs = new long long int[vertexes];
	int * predecessors = new int[vertexes];
	bool * processed = new bool[vertexes];

	for (int i = 0; i < vertexes; i++)
	{
		costs[i] = HelperMethods::MAX_WEIGHT;
		predecessors[i] = -1;
		processed[i] = false;
	}

	costs[graph_start] = 0;
	int k = 0;
	for (int i = 0; i < vertexes; i++)
	{
		k = 0;
		while (processed[k])
		{
			k++;
		}
		int j;
		for (j = k++; k < vertexes; k++)
		{
			if (!processed[k] && (costs[k] < costs[j]))
			{
				j = k;
			}
		}

		processed[j] = true;
		EdgeNode* ptr;

		int endIndex = 0;
		int l = 0;
		int weight = HelperMethods::MAX_WEIGHT;
		while (l < vertexes)
		{
			weight = matrix[j]->Get(l);
			if(weight < HelperMethods::MAX_WEIGHT)
			{
				endIndex = l;
			}
			else
			{
				l++;
				continue;
			}
			if (!processed[endIndex] && (costs[endIndex] > costs[j] + weight))
			{
				costs[endIndex] = costs[j] + weight;
				predecessors[endIndex] = j;
			}
			l++;
		}
	}

	//return;

	int * temp = new int[vertexes];
	int index = 0;

	cout << "START = " << graph_start << endl;
	cout << left << setw(10) << "End" << setw(10) << "Dist" << "Path" << endl << endl;
	for (int i = 0; i < vertexes; i++)
	{
		cout << right << setw(5) << std::to_string(i) << setw(5) << "|";
		cout << right << setw(5) << std::to_string(costs[i]) << setw(5) << "|";
		for (int j = i; j >= 0; j = predecessors[j])
		{
			temp[index++] = j;
		}

		while (index)
		{
			index--;
			cout << temp[index] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

void Matrix::DijkstryHeap()
{
	long int * costs = new long int[vertexes];
	BinaryHeapT<VertexPath>* priortyQueue = new BinaryHeapT<VertexPath>(vertexes);
	VertexPath tempVertex;
	long long int * predecessors = new long long int[vertexes];

	for (int i = 0; i < vertexes; i++)
	{
		costs[i] = HelperMethods::MAX_WEIGHT;
		predecessors[i] = -1;
		if (i > 0)
		{
			tempVertex.Weight = &costs[i];
			tempVertex.Vertex = i;
			priortyQueue->Add(tempVertex);
		}
	}

	costs[graph_start] = 0;
	tempVertex.Weight = &costs[graph_start];
	tempVertex.Vertex = graph_start;

	priortyQueue->Add(tempVertex);

	while (priortyQueue->GetSize() > 0)
	{
		//	priortyQueue->PrintData();
		tempVertex = priortyQueue->GetFront();
		priortyQueue->Delete();

		if (*tempVertex.Weight == HelperMethods::MAX_WEIGHT)
			break;

		int j = tempVertex.Vertex;
		int endIndex = 0;
		int l = 0;
		int weight = HelperMethods::MAX_WEIGHT;
		while (l < vertexes)
		{
			weight = matrix[j]->Get(l);
			if (weight < HelperMethods::MAX_WEIGHT)
			{
				endIndex = l;
			}
			else
			{
				l++;
				continue;
			}
			if ((costs[endIndex] > costs[j] + weight))
			{
				costs[endIndex] = costs[j] + weight;
				predecessors[endIndex] = j;

				tempVertex.Vertex = endIndex;
				tempVertex.Weight = &costs[endIndex];
				priortyQueue->DeleteFrom(priortyQueue->GetIndex(tempVertex));
				priortyQueue->Add(tempVertex);
			}
			l++;
		}

	}

	//return;
	int * temp = new int[vertexes];
	int index = 0;


	cout << "START = " << graph_start << endl;
	cout << left << setw(10) << "End" << setw(10) << "Dist" << "Path" << endl << endl;
	for (int i = 0; i < vertexes; i++)
	{
		cout << right << setw(5) << std::to_string(i) << setw(5) << "|";
		cout << right << setw(5) << std::to_string(costs[i]) << setw(5) << "|";
		for (int j = i; j >= 0; j = predecessors[j])
		{
			temp[index++] = j;
		}

		while (index)
		{
			index--;
			cout << temp[index] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

void Matrix::BellmanFord()
{
	long long int * costs = new long long int[vertexes];
	int * predecessors = new int[vertexes];
	bool test;																		//zmienna do sprawdzania czy w obiegu nic sie nie zmienilo
	EdgeNode* ptr = nullptr;

	for (int i = 0; i < vertexes; i++)
	{
		costs[i] = HelperMethods::MAX_WEIGHT;
		predecessors[i] = -1;
	}

	costs[graph_start] = 0;
	for (int i = 1; i < vertexes; i++)
	{
		test = true;
		for (int j = 0; j < vertexes; j++)
		{
			int endIndex = 0;
			int l = 0;
			int weight = HelperMethods::MAX_WEIGHT;
			while (l < vertexes)
			{
				weight = matrix[j]->Get(l);
				if (weight < HelperMethods::MAX_WEIGHT)
				{
					endIndex = l;
				}
				else
				{
					l++;
					continue;
				}
				if (costs[endIndex] > costs[j] + weight)
				{
					test = false;
					costs[endIndex] = costs[j] + weight;
					predecessors[endIndex] = j;
				}
				l++;
			}
		}
		if (test)
			break;
	}


	for (int i = 0; i < vertexes; i++)
	{
		int endIndex = 0;
		int l = 0;
		int weight = HelperMethods::MAX_WEIGHT;
		while (l < vertexes)
		{
			weight = matrix[i]->Get(l);
			if (weight < HelperMethods::MAX_WEIGHT)
			{
				endIndex = l;
			}
			else
			{
				l++;
				continue;
			}
			if (costs[endIndex] > costs[i] + weight)
			{
				cout << "Cykl ujemny" << endl;
				return;
			}
			l++;
		}
	}
//	return;
	cout << endl;
		int * temp = new int[vertexes];
		int index = 0;

		cout << "START = " << graph_start << endl;
		cout << left << setw(10) << "End" << setw(10) << "Dist" << "Path" << endl << endl;
		for (int i = 0; i < vertexes; i++)
		{
			cout << right << setw(5) << std::to_string(i) << setw(5) << "|";
			cout << right << setw(5) << std::to_string(costs[i]) << setw(5) << "|";
			for (int j = i; j >= 0; j = predecessors[j])
			{
				temp[index++] = j;
			}

			while (index)
			{
				index--;
				cout << temp[index] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
	
}

void Matrix::FulkersonBFS()
{
	DoublyLinkedList* queue = new DoublyLinkedList();
	bool foundPath;
	int cp = 0;
	int temp;
	int ** flows = new int*[vertexes];
	int * CFP = new int[vertexes];
	int * predecessors = new int[vertexes];
	int maxFlow = 0;

	for (int i = 0; i < vertexes; i++)
	{
		flows[i] = new int[vertexes];
		for (int j = 0; j < vertexes; j++)
		{
			flows[i][j] = 0;
		}
		CFP[i] = 0;
	}

	do
	{
		for (int i = 0; i < vertexes; i++)
		{
			predecessors[i] = -1;
		}

		predecessors[graph_start] = -2;
		CFP[graph_start] = HelperMethods::MAX_WEIGHT;

		while ( queue->GetSize() > 0)
			queue->Delete(0);

		queue->addToEnd(graph_start);
		foundPath = false;

		while (queue->GetSize() > 0)
		{
			temp = queue->GetHead()->Number;
			queue->Delete(0);

			for (int i = 0; i < vertexes; i++)
			{
				if (matrix[temp]->Get(i) == HelperMethods::MAX_WEIGHT)
				{
					matrix[temp]->Set(i, 0);
					continue;
				}

				cp = matrix[temp]->Get(i) - flows[temp][i];

				if ((cp == 0 || predecessors[i] != -1))
					continue;
				else
				{
					predecessors[i] = temp;

					CFP[i] = CFP[temp] > cp ? cp : CFP[temp];

					if (i == graph_end)
					{

						maxFlow += CFP[graph_end];

						int counter = i;
						while (counter != graph_start)
						{
							temp = predecessors[counter];
							flows[temp][counter] += CFP[graph_end];
							flows[counter][temp] -= CFP[graph_end];
							counter = temp;
						}
						//cout << endl << i << " <- ";
						/*int help = i;
						do
						{
							cout << predecessors[help] << " <- ";
							help = predecessors[help];
						} while (help != graph_start);*/

						foundPath = true;
						break;
					}
					queue->addToEnd(i);
				}
			}
			if (foundPath)
				break;
		}
	} while (foundPath);

	//return;
	cout << endl;
	cout << setw(10) << left << "Edge:" << "Flow(max / used): " << endl;
	for (int i = 0; i < vertexes; i++)
	{
		for (int j = 0; j < vertexes; j++)
		{
			if(matrix[i]->Get(j) != 0 && matrix[i]->Get(j) != HelperMethods::MAX_WEIGHT)
			{
				string temp = "(" + std::to_string(i) + ", " + std::to_string((j)) + ")";
				cout << setw(10) << left << temp << left << matrix[i]->Get(j) << " / " << flows[i][j] << endl;
			}
		}
	}
	cout << endl << "MAX_FLOW = " << maxFlow << endl;
}

void Matrix::FulkersonDFS()
{
	DoublyLinkedList* stack = new DoublyLinkedList();
	bool foundPath;
	int cp = 0;
	int ** flows = new int*[vertexes];
	int * CFP = new int[vertexes];
	int * predecessors = new int[vertexes];
	int maxFlow = 0;

	for (int i = 0; i < vertexes; i++)
	{
		flows[i] = new int[vertexes];
		for (int j = 0; j < vertexes; j++)
		{
			flows[i][j] = 0;
		}
		CFP[i] = 0;
	}

	do
	{
		for (int i = 0; i < vertexes; i++)
		{
			predecessors[i] = -1;
		}

		predecessors[graph_start] = -2;
		CFP[graph_start] = HelperMethods::MAX_WEIGHT;

		while (stack->GetSize() > 0)
			stack->Delete(0);

		stack->Add(graph_start, 0);
		foundPath = false;

		while (stack->GetSize() > 0)
		{
			int temp = stack->GetHead()->Number;
			stack->Delete(0);
		//	cout << endl << temp << " -> ";
			for (int i = 0; i < vertexes; i++)
			{
				if ( matrix[temp]->Get(i) == HelperMethods::MAX_WEIGHT)
				{
					matrix[temp]->Set(i, 0);
					//cout << matrix[temp]->Get(i) << endl;
					continue;
				}

				cp = matrix[temp]->Get(i) - flows[temp][i];

				if (( cp <= 0 || predecessors[i] != -1))
			//	if( predecessors[i] != -1)
					continue;
				else
				{
					predecessors[i] = temp;

					CFP[i] = CFP[temp] > cp ? cp : CFP[temp];

					if (i == graph_end)
					{

						maxFlow += CFP[graph_end];

						int counter = i;
						while (counter != graph_start)
						{
							temp = predecessors[counter];
							flows[temp][counter] += CFP[graph_end];
							flows[counter][temp] -= CFP[graph_end];
							counter = temp;
							
						}
						//cout << endl << i << " <- ";
						//int help = i;

						//do
						//{
						//	cout << predecessors[help] << " <- ";
						//	help = predecessors[help];
						//} while (help != graph_start);

						foundPath = true;
						break;
					}
					stack->Add(i, 0);
				}
			}
			if (foundPath)
				break;
		}
	} while (foundPath);
	//return;
	cout << endl;
	cout << setw(10) << left << "Edge:" << "Flow(max / used): " << endl;
	for (int i = 0; i < vertexes; i++)
	{
		for (int j = 0; j < vertexes; j++)
		{
			if (matrix[i]->Get(j) != 0 && matrix[i]->Get(j) != HelperMethods::MAX_WEIGHT)
			{
				string temp = "(" + std::to_string(i) + ", " + std::to_string((j)) + ")";
				cout << setw(10) << left << temp << left << matrix[i]->Get(j) << " / " << flows[i][j] << endl;
			}
		}
	}
	cout << endl << "MAX_FLOW = " << maxFlow << endl;
}

void Matrix::PrintData()
{
	cout << setw(7) << " ";
	for(int i = 0; i < vertexes; i++)
	{
		cout << setw(7) << i;
	}
	cout << endl << endl;
	for(int i = 0; i < vertexes; i++)
	{
		cout << setw(7) << i;
		matrix[i]->PrintData();
	}
	cout << endl << endl;
}

void Matrix::InsertEdge(int start, int end, int val)
{
	if(start < vertexes && end < vertexes)
	{
		matrix[start]->Insert(val, end);
	}
	if(!directed)
	{
		matrix[end]->Insert(val, start);
	}
}

void Matrix::SetGraphStart(int ver)
{
	graph_start = ver;
}

void Matrix::SetGraphEnd(int ver)
{
	graph_end = ver;
}

Matrix::Matrix(int edg, int ver)
{
	directed = false;
	edges = edg;
	vertexes = ver;
	matrix = new Array*[ver];

	for(int i = 0; i < ver; i++)
	{
		matrix[i] = new Array(ver);
	}

}

Matrix* Matrix::ReadDataFromFile(std::string path, bool directed)
{
	Matrix* data = nullptr;
	ifstream file;
	int tab[4];
	file.open(path.c_str());
	if(file.is_open())
	{
		if(HelperMethods::File_read_line(file, tab, 4))
		{
			data = new Matrix(tab[0], tab[1]);
			data->directed = directed;
			data->SetGraphStart(tab[2]);
			data->SetGraphEnd(tab[3]);
			for(int i = 0; i < data->GetEdges(); i++)
				if(HelperMethods::File_read_line(file, tab, 3))
				{
					data->InsertEdge(tab[0], tab[1], tab[2]);
				}
				else
				{
					cout <<	"File error - READ EDGE"<< endl;
					break;
				}
		}
		else cout << "File error - READ INFO" << endl;
		file.close();
	}
	else
		cout << "File error - OPEN" << endl;

	if(data)
	data->directed = directed;

	return data;
}

Matrix::~Matrix()
{
	for(int i = 0 ; i < vertexes; i++)
	{
		delete matrix[i];
	}
	delete[] matrix;
}
