/*
Created by: Istari`.
Description: runs the BFMEI with the supplied params taken from the "lotrbfme_params.txt" file. Made it to work with Gameranger.
Version: 2.1
*/


#include "pch.h"


using namespace std;


string ReadFile(string filepath)
{
	fstream parametersfile;
	string tp;

	parametersfile.open(filepath, ios::in);

	if (parametersfile.is_open())
	{
		while (getline(parametersfile, tp)) 
		{
			parametersfile.close();
			return tp;
		}		
	}
}


bool OpenBFME(string parameters)
{
	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFOA StartupInfo;

	ZeroMemory(&StartupInfo, sizeof(StartupInfo));

	StartupInfo.cb = sizeof StartupInfo;

	LPCSTR Application = "C:\\Program Files (x86)\\EA GAMES\\The Battle for Middle-earth (tm)\\lotrbfme_.exe";
	LPCSTR CurrentDirectory = "C:\\Program Files (x86)\\EA GAMES\\The Battle for Middle-earth (tm)";

	ifstream ifile(Application);

	if (!ifile)
		return false;

	LPSTR cString = _strdup(parameters.c_str());

	if (!CreateProcessA(Application, cString, NULL, NULL, TRUE, 0, NULL, CurrentDirectory, &StartupInfo, &ProcessInfo))
	{
		//printf("CreateProcess failed (%d).\n", GetLastError());
		MessageBoxA(NULL, "CreateProcessA Failed!", "ERROR", MB_OK | MB_ICONERROR);
		return false;
	}
	else
	{
		WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
		return true;
	}
}


int main()
{
	if (!OpenBFME(ReadFile("lotrbfme_params.txt")))
		system("pause");
}