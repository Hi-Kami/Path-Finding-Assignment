// PathFinding.cpp : main project file.
#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "GridClass.h"
#include "BestFirst.h"
#include "Dijkstra's.h"
#include "AStar.h"
#include "Form1.h"

using namespace PathFinding;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	// Create the main window and run it
    Application::Run(gcnew Form1());
	return 0;
}
