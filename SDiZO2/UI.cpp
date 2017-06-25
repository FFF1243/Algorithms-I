#include "UI.h"
#include <iostream>
#include <string>
#include "AdjacencyList.h"
#include "Matrix.h"
using namespace std;
int UI::ShowMSTMenu()
{
	int a;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		cout<< endl << "Wybierz operacje " << endl
			<< "1. Wczytaj graf z pliku" << endl
			<< "2. Wyswietl graf macierzowo i listowo" << endl
			<< "3. Algorytm Kruskala" << endl
			<< "4. Algorytm Prima" << endl
			<< "5. Wyjscie" << endl;

		cin >> a;

	} while (a > 5 || a < 1 || std::cin.fail());
	return a;
}

int UI::ShowSPMenu()
{
	int a;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		cout << endl << "Wybierz operacje " << endl
			<< "1. Wczytaj graf z pliku" << endl
			<< "2. Wyswietl graf macierzowo i listowo" << endl
			<< "3. Algorytm Dijkstry" << endl
			<< "4. Algorytm Bellmana-Forda" << endl
			<< "5. Wyjscie" << endl;

		cin >> a;

	} while (a > 5 || a < 1 || std::cin.fail());
	return a;
}

int UI::ShowMaxFlowMenu()
{
	int a;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		cout << endl << "Wybierz operacje " << endl
			<< "1. Wczytaj graf z pliku" << endl
			<< "2. Wyswietl graf macierzowo i listowo" << endl
			<< "3. Algorytm Forda-Fulkersona DFS" << endl
			<< "4. Algorytm Forda-Fulkersona BFS" << endl
			<< "5. Wyjscie" << endl;

		cin >> a;

	} while (a > 5 || a < 1 || std::cin.fail());
	return a;
}

int UI::ShowMainMenu()
{
	int a;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		cout<< endl << "Wybierz operacje " << endl
			<< "1. Minimalne drzewo rozpinajace" << endl
			<< "2. Najkrotsza sciezka w grafie" << endl
			<< "3. Maksymalny przeplyw" << endl
			<< "4. Wyjscie" << endl;

		cin >> a;

	} while (a > 4 || a < 1 || std::cin.fail());
	return a;
}

void UI::MSTMenu()
{
	string path = "";
	AdjacencyList* adjList = nullptr;
	Matrix* matrix = nullptr;
	do
	{
		switch (ShowMSTMenu())
		{
			case 1:
			{
				cin.ignore();
				while (!adjList || !matrix)
				{
					path = ReadPath();
					adjList = AdjacencyList::ReadFromFile(path, false);
					matrix = Matrix::ReadDataFromFile(path, false);
				}
				cout << "Wczytano dane." << endl;
				break;
			}
			case 2:
			{
				if (adjList && matrix)
				{
					adjList->PrintData();
					matrix->PrintData();
				}
				else
				{
					cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
				}
				break;
			}
			case 3:
			{
				if (adjList && matrix)
				{

					cout << "ALGORYTM KRUSKALA LISTA SASIEDZTWA" << endl;
					adjList->Kruskal();
					cout << "ALGORYTM KRUSKALA MACIERZ WAG" << endl;
					matrix->Kruskal();
				}
				else
				{
					cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
				}
				break;
			}
			case 4:
			{
				if (adjList && matrix)
				{

					cout << "ALGORYTM PRIMA LISTA SASIEDZTWA" << endl;
					adjList->Prim();
					cout << "ALGORYTM PRIMA MACIERZ WAG" << endl;
					matrix->Prim();
				}
				else
				{
					cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
				}
				break;
			}
			case 5:
			{
				if (adjList && matrix)
				{
					delete adjList;
					delete matrix;
				}
				Start();
				return;
			}
			default:
			{
				if (adjList && matrix)
				{
					delete adjList;
					delete matrix;
				}
				Start();
				return;
			}
		}
	} while (true);
}

void UI::SPMenu()
{
	string path = "";
	AdjacencyList* adjList = nullptr;
	Matrix* matrix = nullptr;
	do
	{
		switch (ShowSPMenu())
		{
		case 1:
		{
			cin.ignore();
			while (!adjList || !matrix)
			{
				path = ReadPath();
				adjList = AdjacencyList::ReadFromFile(path, true);
				matrix = Matrix::ReadDataFromFile(path, true);
			}
			cout << "Wczytano dane." << endl;
			break;
		}
		case 2:
		{
			if (adjList && matrix)
			{
				adjList->PrintData();
				matrix->PrintData();
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 3:
		{
			if (adjList && matrix)
			{

				cout << "ALGORYTM DIJKSTRY LISTA SASIEDZTWA" << endl;
				adjList->Dijkstry();
				cout << "ALGORYTM DIJKSTRY MACIERZ WAG" << endl;
				matrix->Dijkstry();
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 4:
		{
			if (adjList && matrix)
			{

				cout << "ALGORYTM BELLMANA-FORDA LISTA SASIEDZTWA" << endl;
				adjList->BellmanFord();
				cout << "ALGORYTM BELLMANA-FORDA MACIERZ WAG" << endl;
				matrix->BellmanFord();
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 5:
		{
			if(adjList && matrix)
			{
				delete adjList;
				delete matrix;
			}
			Start();
			return;
		}
		default:
		{
			if (adjList && matrix)
			{
				delete adjList;
				delete matrix;
			}
			Start();
			return;
		}
		}
	} while (true);
}

void UI::MaxFlowMenu()
{
	string path = "";
	AdjacencyList* adjList = nullptr;
	Matrix* matrix = nullptr;
	do
	{
		switch (ShowMaxFlowMenu())
		{
		case 1:
		{
			cin.ignore();
			while (!adjList || !matrix)
			{
				path = ReadPath();
				adjList = AdjacencyList::ReadFromFile(path, true);
				matrix = Matrix::ReadDataFromFile(path, true);
			}
			cout << "Wczytano dane." << endl;
			break;
		}
		case 2:
		{
			if (adjList && matrix)
			{
				adjList->PrintData();
				matrix->PrintData();
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 3:
		{
			if (adjList && matrix)
			{

				cout << "ALGORYTM FORDA-FULKERSONA DFS LISTA SASIEDZTWA" << endl;
				adjList->FulkersonDFS();
				cout << "ALGORYTM FORDA-FULKERSONA DFS MACIERZ WAG" << endl;
				matrix->FulkersonDFS();
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 4:
		{
			if (adjList && matrix)
			{

				cout << "ALGORYTM FORDA-FULKERSONA BFS LISTA SASIEDZTWA" << endl;
				adjList->FulkersonBFS();
				cout << "ALGORYTM FORDA-FULKERSONA BFS MACIERZ WAG" << endl;
				matrix->FulkersonBFS();
			}
			else
			{
				cout << "BLAD: NIE WCZYTANO DANYCH" << endl;
			}
			break;
		}
		case 5:
		{
			if (adjList && matrix)
			{
				delete adjList;
				delete matrix;
			}
			Start();
			return;
		//	break;
		}
		default:
		{
			if (adjList && matrix)
			{
				delete adjList;
				delete matrix;
			}
			Start();
			return;
		//	break;
		}
		}
	} while (true);
}

std::string UI::ReadPath()
{
	std::string path;
	cout << "Podaj nazwe pliku: ";
	getline(cin, path);
	return path;
}

void UI::Start()
{
	do
	{
		switch (ShowMainMenu())
		{
			case 1:
			{
				MSTMenu();
				break;
			}
			case 2:
			{
				SPMenu();
				break;
			}
			case 3:
			{
				MaxFlowMenu();
				break;
			}
			case 4:
			{
				exit(0);
				return;
			}
			default:
			{
				return;
			}
		}
	} while (true);
}

