#pragma once
#ifndef UI_HEADER
#define UI_HEADER
#include <string>


class UI
{
private:

public:
	static int ShowMainMenu();
	static void MSTMenu();
	static void SPMenu();
	static void MaxFlowMenu();
	static std::string ReadPath();
	static void Start();
	static int ShowMSTMenu();
	static int ShowSPMenu();
	static int ShowMaxFlowMenu();
};

#endif