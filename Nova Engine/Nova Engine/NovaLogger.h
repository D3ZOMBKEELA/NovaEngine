#pragma once

#include <Windows.h>
#include <consoleapi.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

typedef enum
{
	Log_All,
	Log_Info,
	Log_Debug,
	Log_Warning,
	Log_Severe
} LogLevel;

#ifdef LOGGER

class Logger
{
public:
	Logger();
	~Logger();

#ifdef CONSOLE
	bool CreateConsole();
	bool CloseConsole();
#endif // CONSOLE

	static Logger* GetLogger();

	int Log(LogLevel level, const char* format, ...);

private:
	char* getFormattedText(const char* format, ...);

	int PrintFormatted(const char* format, va_list argList);
	int PrintF(const char* format, ...);

	int PrintLineFormatted(const char* format, va_list argList);
	int PrintLineF(const char* format, ...);

private:
	HANDLE m_consoleHandle;
	fstream m_lastLog;
	fstream m_currentLog;

	static Logger* m_instance;
};

#endif	// LOGGER

/*


Add output to a file, i.e. dump console buffer out to a file, if there is no console, then maybe store the logs in a local buffer and print
that out to a file


#define Logger
#define  _DEBUG

If debug mode is on, and logger is defined then at the very least create a logger

Logger will be defined if debug or test
Debug only if it's debug and will open a console to output logging information to as well as output it to a file

*/