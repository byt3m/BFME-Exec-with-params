/*
Created by: Istari`/tributoo2.
Description: runs the BFMEI with the supplied params taken from the "lotrbfme_params.txt" file. Made it to work with Gameranger.
*/


#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;


string ReadFile(string filepath)
{
	fstream newfile;
	newfile.open(filepath, ios::in); //open a file to perform read operation using file object
	if (newfile.is_open()) {   //checking whether the file is open
		string tp;
		while (getline(newfile, tp)) {  //read data from file object and put it into string.
			return tp;
			//cout << tp << "\n";   //print the data of the string
		}
		newfile.close();   //close the file object.
	}
}


bool EjecutarBFME(string parameters)
{
	cout << "\n" << "Launching BFME..." << endl;

	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
	STARTUPINFOA StartupInfo; //This is an [in] parameter

	ZeroMemory(&StartupInfo, sizeof(StartupInfo));

	StartupInfo.cb = sizeof StartupInfo; //Only compulsory field

	LPCSTR Application = "C:\\Program Files (x86)\\EA GAMES\\The Battle for Middle-earth (tm)\\lotrbfme_.exe";
	LPCSTR CurrentDirectory = "C:\\Program Files (x86)\\EA GAMES\\The Battle for Middle-earth (tm)";

	ifstream ifile(Application);
	if (!ifile)
	{
		cout << "Can't find file " << Application;
		return false;
	}

	LPSTR cString = _strdup(parameters.c_str());

	if (!CreateProcessA(Application, cString, NULL, NULL, TRUE, 0, NULL, CurrentDirectory, &StartupInfo, &ProcessInfo))
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
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
	string param = ReadFile("lotrbfme_params.txt");
	if (!EjecutarBFME(param)) {
		system("pause");
	}
}