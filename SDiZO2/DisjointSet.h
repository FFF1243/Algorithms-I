#pragma once
#include "BinaryHeapT.h"

#ifndef DS_HEADER
#define DS_HEADER
class DSNode
{
public:
	int Parent;												//Numer wierzcholka bedacego rodzicem wezla
	int Rank;												//Ranga drzewa - im drzewo jest wieksze tym jego ranga jest wieksza
};

class DisjointSet
{
private:
	DSNode * array;
public:
	DisjointSet(int size);										//Alokuje miejsce na podana ilosc zbiorow(drzew)
	~DisjointSet();
	void MakeSet(int vertex);									//Tworzy jednowezlowe drzewo - podany wierzcholek staje sie reprezentatnem tego zbioru
	int FindSet(int vertex);									//Zwraca reprezentanta zbioru do ktorego nalezy podany wierzcholek
	void UnionSets(Edge edge);									//Zlacza drzewa do ktorych nalezy wierzcholek startowy i wierzcholek koncowy
};

#endif