#include "DisjointSet.h"

DisjointSet::DisjointSet(int size)
{
	array = new DSNode[size];
}

DisjointSet::~DisjointSet()
{
	delete[] array;
}

void DisjointSet::MakeSet(int vertex)
{
	array[vertex].Parent = vertex;
	array[vertex].Rank = 0;
}

int DisjointSet::FindSet(int vertex)
{
	if (array[vertex].Parent != vertex)										// Jesli wezel nie wskazuje na samego siebie
		array[vertex].Parent = FindSet(array[vertex].Parent);				// Kompresja sciezki - kazdy wezel nadrzedny bedzie wskazywal bezposrednio na rodzica
	return array[vertex].Parent;											// Zwroc rodzica - reprezentanta zbioru
}

void DisjointSet::UnionSets(Edge edge)
{
	int rootStart, rootEnd;

	rootStart = FindSet(edge.Start);											 // Wyznaczamy korze� drzewa z wierzcho�ka startowego
	rootEnd = FindSet(edge.End);												 // Wyznaczamy korze� drzewa z wierzcho�ka ko�cowego
	if (rootStart != rootEnd)													 // Korzenie musz� by� r�ne
	{
		if (array[rootStart].Rank > array[rootEnd].Rank)						// Por�wnujemy rangi drzew
			array[rootEnd].Parent = rootStart;									// rootStart ma wi�ksza range (nalezy do wiekszego drzewa), do��czamy rootEnd
		else
		{
			array[rootStart].Parent = rootEnd;									// r�wne lub rootEnd ma wi�ksza range(nalezy do wiekszego drzewa), do��czamy rootStart
			if (array[rootStart].Rank == array[rootEnd].Rank)
				array[rootEnd].Rank++;
		}
	}
}


