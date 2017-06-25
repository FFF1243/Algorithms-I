#include <iostream>
#include "Matrix.h"
#include "AdjacencyList.h"
#include "DisjointSet.h"
#include "MSTree.h"
#include "UI.h"
#include "Test.h"
#include <ctime>
#include "HelperMethods.h"


using namespace std;

int main()
{
	UI::Start();

	//Matrix *temp = Matrix::ReadDataFromFile("Test.txt", true);
	//AdjacencyList *templist = AdjacencyList::ReadFromFile("Test.txt", true);


	//int denisty[4] = { 25, 50, 75, 99 };
	//int size[5] = { 20, 40, 60, 80, 100 };

	//for(int i = 0; i < 5; i++)
	//{
	//	for(int j = 0; j < 4; j++)
	//	{
	//		Test::FulkersonFordBFSAdjList(size[i], denisty[j]);
	//		Test::FulkersonFordBFSMatrix(size[i], denisty[j]);
	//		Test::FulkersonFordDFSAdjList(size[i], denisty[j]);
	//		Test::FulkersonFordDFSMatrix(size[i], denisty[j]);
	//	}
	//}

	//templist->FulkersonDFS();
	//templist->FulkersonBFS();
	//temp->FulkersonBFS();
	//temp->FulkersonDFS();

	//cin.get();
	//cin.ignore();
	return 0;
}