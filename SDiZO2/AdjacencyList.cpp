#include "AdjacencyList.h"
#include "HelperMethods.h"
#include <iostream>
#include <iomanip>
#include "DisjointSet.h"
#include "MSTree.h"
#include "BinaryHeapT.h"
using namespace std;

bool AdjacencyList::IsConnected()
{
	int verCounter = 0;
	bool * visited = new bool[vertexes];

	for(int i = 0; i < vertexes; i++)
	{
		visited[i] = false;
	}
	Edge temp;
	EdgeNode* ptr;
	int u;
	DoublyLinkedListEdges* stack = new DoublyLinkedListEdges();

	stack->Add(list[0]->GetHead()->Value,0);
	visited[0] = true;

	while(stack->GetSize() > 0)
	{
		temp = stack->GetHead()->Value;
		stack->Delete(0);
		verCounter++;

		ptr = list[temp.Start]->GetHead();
		while(ptr)
		{
			u = ptr->Value.End;
			if(!visited[u])
			{
				visited[u] = true;
				if(list[ptr->Value.End]->GetHead())
					stack->Add(list[ptr->Value.End]->GetHead()->Value,0);
			}
			ptr = ptr->Next;
		}
	}
	if (verCounter == vertexes)
		return true;
	else
		return false;
}

AdjacencyList::AdjacencyList(int edg, int ver)
{
	vertexes = ver;
	edges = edg;
	list = new DoublyLinkedListEdges*[ver];												//Tablica wskaznikow na listy sasiadow

	for(int i = 0; i< ver; i++)
	{
		list[i] = new DoublyLinkedListEdges();
	}
}

void AdjacencyList::PrintData()
{
	for(int i = 0; i < vertexes; i++)
	{
		cout << "Wierzcholek " << i << ": " << setw(7);
		list[i]->PrintData();
	}
	cout << endl << endl;
}

void AdjacencyList::PrintMST()
{
	EdgeNode *ptr;
	int weight = 0;
	std::cout << endl;
	cout << setw(10) << left << "Value:" << "Weight: " << endl;
	for (int i = 0; i < vertexes; i++)
	{
		for (ptr = list[i]->GetHead(); ptr; ptr = ptr->Next)
		{
			string temp = "(" + std::to_string(i) + ", " + std::to_string((ptr->Value.End)) + ")";
			cout << setw(10) << left << temp << setw(10) << left << ptr->Value.Weight << endl;
			weight += ptr->Value.Weight;
		}
	}
	cout << endl << endl << "MST = " << weight << endl << endl;
}


int AdjacencyList::GetEdges()
{
	return edges;
}

int AdjacencyList::GetVertexes()
{
	return vertexes;
}

void AdjacencyList::Kruskal()
{
	DisjointSet* sets = new DisjointSet(vertexes);
	//BinaryHeap* queEdges = new BinaryHeap(edges);
	BinaryHeapT<Edge>* queEdges = new BinaryHeapT<Edge>(edges);
	AdjacencyList* msTree = new AdjacencyList(vertexes - 1, vertexes);
	msTree->directed = true;

	for (int i = 0; i < vertexes; i++)											//Utworzenie
	{
		sets->MakeSet(i);
	}

	for (int i = 0; i < vertexes; i++)
	{
		EdgeNode* temp = list[i]->GetHead();
		while(temp)
		{
			queEdges->Add(temp->Value);
			temp = temp->Next;
		}
	}

	Edge temp;
	for (int i = 1; i < vertexes; i++)
	{
		do
		{
			temp = queEdges->GetFront();
			queEdges->Delete();
		} while (sets->FindSet(temp.Start) == sets->FindSet(temp.End) && queEdges->GetSize() > 0);
		msTree->InsertEdge(temp.Start, temp.End, temp.Weight);
		sets->UnionSets(temp);
	}
	msTree->PrintMST();
}

void AdjacencyList::Prim()
{
	BinaryHeapT<Edge>* queEdges = new BinaryHeapT<Edge>(edges);
	AdjacencyList* msTree = new AdjacencyList(vertexes - 1, vertexes);
	msTree->directed = true;


	bool* visited = new bool[vertexes];
	for (int i = 0; i < vertexes; i++)
	{
		visited[i] = false;
	}

	int vertex = 0;
	visited[vertex] = true;

	Edge temp;
	EdgeNode* nodeTemp;
	for (int i = 1; i < vertexes; i++)
	{
		nodeTemp = list[vertex]->GetHead();
		while (nodeTemp)
		{
			if (!visited[nodeTemp->Value.End])
			{
				temp.Weight = nodeTemp->Value.Weight;
				temp.Start = vertex;
				temp.End = nodeTemp->Value.End;
				queEdges->Add(temp);
			}
			nodeTemp = nodeTemp->Next;
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

void AdjacencyList::Dijkstry()
{
		int * costs = new int[vertexes];
		long long int * predecessors = new long long int[vertexes];
		bool * processed = new bool[vertexes];
		EdgeNode* ptr;
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
			ptr = ptr = list[j]->GetHead();
			while (ptr)
			{
				if (!processed[ptr->Value.End] && (costs[ptr->Value.End] > costs[j] + ptr->Value.Weight))
				{
					costs[ptr->Value.End] = costs[j] + ptr->Value.Weight;
					predecessors[ptr->Value.End] = j;
				}
				ptr = ptr->Next;
			}
		}
	//	return;
		int * temp = new int[vertexes];
		int index = 0;
	
	
		cout << "START = " << graph_start << endl;
		cout << left << setw(10) << "End" << setw(10) << "Dist" << "Path" << endl << endl;
		for(int i = 0; i < vertexes; i++)
		{
			cout << right<< setw(5) << std::to_string(i) <<setw(5)<< "|";
			cout << right << setw(5) << std::to_string(costs[i]) <<setw(5)<< "|";
			for(int j = i; j >= 0; j = predecessors[j])
			{
				temp[index++] = j;
			}
	
			while(index)
			{
				index--;
				cout << temp[index] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
	

}

void AdjacencyList::DijkstryHeap()
{

	long int * costs = new long int[vertexes];
	BinaryHeapT<VertexPath>* priortyQueue = new BinaryHeapT<VertexPath>(vertexes);
	VertexPath tempVertex;
	long long int * predecessors = new long long int[vertexes];
	EdgeNode* ptr;

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
		ptr = ptr = list[j]->GetHead();
		while (ptr)
		{
			if ((costs[ptr->Value.End] > costs[j] + ptr->Value.Weight))
			{
				costs[ptr->Value.End] = costs[j] + ptr->Value.Weight;
				predecessors[ptr->Value.End] = j;

				tempVertex.Vertex = ptr->Value.End;
				tempVertex.Weight = &costs[ptr->Value.End];
				priortyQueue->DeleteFrom(priortyQueue->GetIndex(tempVertex));
				priortyQueue->Add(tempVertex);

			}
			ptr = ptr->Next;
		}

	}


	//return
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


void AdjacencyList::BellmanFord()
{
	long long int * costs = new long long int[vertexes];
	int * predecessors = new int[vertexes];
	bool test;
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
		for(int j = 0; j <vertexes; j++)
		{
			ptr = ptr = list[j]->GetHead();
			while (ptr)
			{
				if (costs[ptr->Value.End] > costs[j] + ptr->Value.Weight)
				{
					test = false;
					costs[ptr->Value.End] = costs[j] + ptr->Value.Weight;
					predecessors[ptr->Value.End] = j;
				}
				ptr = ptr->Next;
			}
		}
		if (test)
			break;
	}

	for(int i = 0; i < vertexes; i++)
	{
		ptr = list[i]->GetHead();
		while(ptr)
		{
			if (costs[ptr->Value.End] > costs[i] + ptr->Value.Weight)
			{
				cout << "Cykl ujemny" << endl;
				return;
			}
			ptr = ptr->Next;
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


void AdjacencyList::FulkersonBFS()
{
	DoublyLinkedListEdges* queue = new DoublyLinkedListEdges();
	bool foundPath;
	Edge temp;
	EdgeNode * ptr = nullptr;
	int cp = 0;
	int ** flows = new int*[vertexes];
	int * CFP = new int[vertexes];
	int * predecessors = new int[vertexes];
	int maxFlow = 0;


	//Utworzenie sieci rezydualnej
	for (int i = 0; i < vertexes; i++)
	{
		for (int j = 0; j < vertexes; j++)
		{
			EdgeNode * ptr = list[i]->GetHead();
			while (ptr)
			{
				if (ptr->Value.End == j)
					break;
				ptr = ptr->Next;
			}
			if (!ptr && i != j)
			{
				Edge edge;
				edge.Start = i;
				edge.Weight = 0;
				edge.End = j;
				list[i]->addToEnd(edge);
			}
		}
	}

	for(int i = 0; i < vertexes; i++)
	{
		flows[i] = new int[vertexes];
		for(int j = 0; j < vertexes; j++)
		{
			flows[i][j] = 0;
		}
		CFP[i] = 0;
	}

	do
	{
		for(int i = 0; i < vertexes; i++)
		{
			predecessors[i] = -1;
		}

		predecessors[graph_start] = -2;
		CFP[graph_start] = HelperMethods::MAX_WEIGHT;

		while (queue->GetSize() > 0)
			queue->Delete(queue->GetSize() - 1);

	//	if(list[graph_start]->GetSize() > 0 )
			queue->addToEnd(list[graph_start]->GetHead()->Value);

		foundPath = false;

		while(queue->GetSize() > 0)
		{
			temp = queue->GetHead()->Value;
			queue->Delete(0);

			for(int i = 0; i < vertexes; i++)
			{
				//if(list[temp.Start]->GetSize() > 0)
					ptr = list[temp.Start]->GetHead();
				while(ptr)
				{
					if (ptr->Value.End == i)
					{
						cp = ptr->Value.Weight - flows[temp.Start][i];
						break;
					}
					ptr = ptr->Next;
				}

				
				if ((!ptr || cp == 0 || predecessors[i] != -1))
					continue;
				else
				{
					predecessors[i] = temp.Start;

					CFP[i] = CFP[temp.Start] > cp ? cp : CFP[temp.Start];

					if(i == graph_end)
					{
						
						maxFlow += CFP[graph_end];

						int counter = i;
						while( counter != graph_start)
						{
							temp = list[predecessors[counter]]->GetHead()->Value;
							flows[temp.Start][counter] += CFP[graph_end];
							flows[counter][temp.Start] -= CFP[graph_end];
							counter = temp.Start;
						}

						foundPath = true;
						break;
					}
						queue->addToEnd(list[i]->GetHead()->Value);
				}
			}
			if (foundPath)
				break;
		}
	} while (foundPath);

//	return;
	cout << setw(10) << left << "Edge:" << "Flow(max / used): " << endl;
	for (int i = 0; i < vertexes; i++)
	{
		EdgeNode* ptr = list[i]->GetHead();
		while(ptr)
		{
			if(ptr && ptr->Value.Weight !=0)
			{
				string temp = "(" + std::to_string(ptr->Value.Start) + ", " + std::to_string((ptr->Value.End)) + ")";
				cout << setw(10) << left << temp << left << ptr->Value.Weight <<  " / " << flows[i][ptr->Value.End] << endl;
			}
			ptr = ptr->Next;
		}
	}
	cout << endl << "MAX_FLOW = " << maxFlow << endl;



}

void AdjacencyList::FulkersonDFS()
{
	DoublyLinkedListEdges* stack = new DoublyLinkedListEdges();
	bool foundPath;
	int cp = 0;
	int ** flows = new int*[vertexes];
	int * CFP = new int[vertexes];
	int * predecessors = new int[vertexes];
	int maxFlow = 0;

	//Utworzenie sieci rezydualnej
	for(int i = 0; i < vertexes; i++)
	{
		for(int j = 0; j < vertexes; j++)
		{
			EdgeNode * ptr = list[i]->GetHead();
			while (ptr)
			{
				if (ptr->Value.End == j)
					break;
					ptr = ptr->Next;
			}
			if(!ptr && i!=j)
			{
				Edge edge;
					edge.Start = i;
					edge.Weight = 0;
					edge.End = j;
					list[i]->addToEnd(edge);
			}
		}
	}

	//this->PrintData();


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

		stack->Add(list[graph_start]->GetHead()->Value, 0);
		foundPath = false;

		while (stack->GetSize() > 0)
		{
			Edge temp = stack->GetHead()->Value;
			stack->Delete(0);

			for (int i = 0; i < vertexes; i++)
			{
				EdgeNode * ptr = list[temp.Start]->GetHead();
				while (ptr)
				{
					if (ptr->Value.End == i)
					{
						cp = ptr->Value.Weight - flows[temp.Start][i];
						break;
					}
					ptr = ptr->Next;
				}

				if ((!ptr || cp == 0 || predecessors[i] != -1))
					continue;
				else
				{
					predecessors[i] = temp.Start;

					CFP[i] = CFP[temp.Start] > cp ? cp : CFP[temp.Start];

					if (i == graph_end)
					{

						maxFlow += CFP[graph_end];

						int counter = i;
						while (counter != graph_start)
						{
							temp = list[predecessors[counter]]->GetHead()->Value;
							flows[temp.Start][counter] += CFP[graph_end];
							flows[counter][temp.Start] -= CFP[graph_end];
							counter = temp.Start;
						}

						foundPath = true;
						break;
					}
						stack->Add(list[i]->GetHead()->Value, 0);
				}
			}
			if (foundPath)
				break;
		}
	} while (foundPath);
//	return;

	cout << setw(10) << left << "Edge:" << "Flow(max / used): " << endl;
	for (int i = 0; i < vertexes; i++)
	{
		EdgeNode* ptr = list[i]->GetHead();
		while (ptr)
		{
			if (ptr && ptr->Value.Weight != 0)
			{
				string temp = "(" + std::to_string(ptr->Value.Start) + ", " + std::to_string((ptr->Value.End)) + ")";
				cout << setw(10) << left << temp << left << ptr->Value.Weight << " / " << flows[i][ptr->Value.End] << endl;
			}
			ptr = ptr->Next;
		}
	}
	cout << endl << "MAX_FLOW = " << maxFlow << endl;
}

void AdjacencyList::SetGraphStart(int i)
{
	graph_start = i;
}

void AdjacencyList::SetGraphEnd(int i)
{
	graph_end = i;
}

void AdjacencyList::SetDirected(bool dir)
{
	directed = dir;
}

void AdjacencyList::InsertEdge(int start, int end, int weight)
{
	Edge edge;
	edge.End = end;
	edge.Start = start;
	edge.Weight = weight;

	if(start < vertexes && end < vertexes)
	{
		int size = list[start]->GetSize();
		list[start]->Add(edge, size - 1);
	}
	if(!directed)
	{
		Edge edgeReversed;
		edgeReversed.Start = end;
		edgeReversed.End = start;
		edgeReversed.Weight = weight;

		int size = list[end]->GetSize();
		list[end]->Add(edgeReversed, size - 1);
	}
}

AdjacencyList* AdjacencyList::ReadFromFile(std::string path, bool directed)
{
	AdjacencyList* data = nullptr;
	std::ifstream file;
	int tab[4];
	file.open(path.c_str());
	if (file.is_open())
	{
		if (HelperMethods::File_read_line(file, tab, 4))
		{
			data = new AdjacencyList(tab[0], tab[1]);
			data->directed = directed;
			data->SetGraphStart(tab[2]);
			data->SetGraphEnd(tab[3]);
			for (int i = 0; i < data->GetEdges(); i++)
			{
				if (HelperMethods::File_read_line(file, tab, 3))
				{
					data->InsertEdge(tab[0], tab[1], tab[2]);
				}
				else
				{
					std::cout << "File error - READ EDGE" << endl;
					break;
				}
			}	
		}
		else
			cout << "File error - READ INFO" << endl;
		file.close();
	}
	else
		cout << "File error - OPEN" << endl;

	//if(data)
	//	data->directed = directed;

	return data;
}

AdjacencyList::~AdjacencyList()
{
	for (int i = 0; i< vertexes; i++)
	{
		delete list[i];
	}
	delete[] list;
}
