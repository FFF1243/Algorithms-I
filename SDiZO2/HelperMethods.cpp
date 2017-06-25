#include "HelperMethods.h"
#include <string>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include "AdjacencyList.h"
using namespace std;


bool HelperMethods::File_read_line(std::ifstream& file, int tab[], int size)
{
	std::string s;
	getline(file, s);
	if (file.fail() || s.empty())
		return(false);
	std::istringstream in_ss(s);
	for(int i = 0; i < size; i++)
	{
		in_ss >> tab[i];
		if (in_ss.fail())
		{
			cout << "tu";
			return false;
		}

	}
	return(true);
		
}

long long HelperMethods::ReadQPC()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return ((long long int)  start.QuadPart);
}

double HelperMethods::GetElapsedTime(long long start, long long stop)
{
	long long int elapsed, freq;
	elapsed = stop - start;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	return (1000000.0 * elapsed) / freq;
}

void HelperMethods::SaveToCsv(std::string operation, int size, double result, int density)
{
	string path = operation + ".csv";
	ofstream file;

	if (!ifstream(path))
	{
		file.open(path, ios_base::app);
		file << "Operacja:;" << "Wielkosc strukutry:;" << "Gestosc:;" << "Czas[us];" << "\n";
		file << operation + ";" << std::to_string(size) + ";" << std::to_string(density) + ";" << fixed << result << "\n";
	}
	else
	{
		file.open(path, ios_base::app);
		file << operation + ";" << std::to_string(size) + ";" << fixed << result << "\n";
	}

	file.close();
}

void HelperMethods::SaveAvg(std::string operation, int size, double result, int density)
{
	string path = operation + ".csv";
	ofstream file;

	if (!ifstream(path))
	{
		file.open(path, ios_base::app);
		file << "Operacja:;" << "Wielkosc strukutry:;" << "Gestosc:;" << "Czas[us];" << "\n";
		file << operation + ";" << std::to_string(size) + ";" << std::to_string(density) + ";" << fixed << result << "\n";
	}
	else
	{
		file.open(path, ios_base::app);
		file << operation + ";" << std::to_string(size) + ";" << std::to_string(density) + ";" << fixed << result << "\n";
	}

	file.close();
}


