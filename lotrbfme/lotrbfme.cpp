/*
Created by: byt3m
Description: Executes Battle For Middle Earth with the supplied parameters. Works with gameranger.
Version: 2.2
*/

#include "pch.h"

using namespace std;

#define MAXBUFCHARS 500
PROCESS_INFORMATION lpProcessInfo;
STARTUPINFOA lpStartupInfo;
char executionParameters[MAXBUFCHARS];
stringstream iniFile;
stringstream ssApplication;
stringstream ssCommandLine;

// Returns the last Win32 error, in string format. Returns an empty string if there is no error.
// https://stackoverflow.com/questions/1387064/how-to-get-the-error-message-from-the-error-code-returned-by-getlasterror
std::string GetLastErrorAsString()
{
	//Get the error message ID, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0) {
		return std::string(); //No error message has been recorded
	}

	LPSTR messageBuffer = nullptr;

	//Ask Win32 to give us the string version of that message ID.
	//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	//Copy the error message into a std::string.
	std::string message(messageBuffer, size);

	//Free the Win32's string's buffer.
	LocalFree(messageBuffer);

	return message;
}

void printLastError()
{
	printf("[X] Error code %d: ", GetLastError());
	printf(GetLastErrorAsString().c_str());
}

string getModulePath()
{
	char buffer[MAXBUFCHARS];
	GetModuleFileNameA(NULL, buffer, MAXBUFCHARS);
	return string(buffer).substr(0, string(buffer).find_last_of("\\"));
}

int main(int argc, char* argv[])
{
	// Get INI file path
	printf("[i] Getting ini file path.\n");
	iniFile << getModulePath().c_str() << "\\lotrbfme_parameters.ini";

	// Get original binary path
	printf("[i] Getting original binary \"lotrbfme_.exe\" path.\n");
	ssApplication << getModulePath().c_str() << "\\lotrbfme_.exe";

	// Read info from ini file
	printf("[i] Reading \"execution_parameters\" from ini file.\n");
	if (!GetPrivateProfileStringA("Settings", "execution_parameters", NULL, executionParameters, MAXBUFCHARS, iniFile.str().c_str()))
	{
		printf("[X] Error reading \"execution_parameters\" from ini file.\n");
		printLastError();
		cin.get();
		return 1;
	}

	// Build lpCommandLine
	printf("[i] Building lpCommandLine\n");
	ssCommandLine << ssApplication.str() << " " << executionParameters;

	// Execute BFME
	ZeroMemory(&lpStartupInfo, sizeof(lpStartupInfo));
	lpStartupInfo.cb = sizeof lpStartupInfo;
	printf("[i] Executing BFME.\n");
	if (!CreateProcessA(ssApplication.str().c_str(), LPSTR(ssCommandLine.str().c_str()), NULL, NULL, 1, 0, NULL, NULL, &lpStartupInfo, &lpProcessInfo))
	{
		printf("[X] CreateProcessA failed.\n");
		printLastError();
		cin.get();
		return 1;
	}

	printf("\nPress enter to close this window...\n");
	cin.get();
	return 0;
}