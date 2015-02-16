#include "NovaLogger.h"

#ifdef LOGGER	// CHECK IF DEFINED HERE TOO



Logger* Logger::m_instance = NULL;


Logger::Logger()
{
	m_consoleHandle = NULL;
	m_lastLog.open("lastLog.log", m_lastLog.trunc | m_lastLog.out);

	char* temp = new char[1024];

	time_t now = time(0);
	struct tm tstruct;
	tstruct = *localtime(&now);

	strftime(temp, 64, "%Y.%m.%d", &tstruct);

	_wmkdir(L"../logs/");

	int logNum = 1;

	bool logNumFound = false;
	
	while (!logNumFound)
	{
		struct stat info;
		int ret = stat(getFormattedText("../logs/%s-%02i.log", temp, logNum), &info);
		if (ret != -1)
		{
			logNum++;
		}
		else
		{
			logNumFound = true;
		}
	}
	
	m_currentLog.open(getFormattedText("../logs/%s-%02i.log", temp, logNum), m_currentLog.trunc | m_currentLog.out);
}


Logger::~Logger()
{
	m_lastLog.close();
	m_currentLog.close();
}

#ifdef CONSOLE
bool Logger::CreateConsole()
{
	if (!m_consoleHandle)
	{
		if (AllocConsole() != 0)
		{
			SetConsoleTitle("Nova Engine Debug Logger");
			m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			return true;
		}
	}

	return false;
}


bool Logger::CloseConsole()
{
	if (m_consoleHandle)
	{
		if (FreeConsole != 0)
		{
			return true;
		}
	}
	
	return false;
}
#endif // CONSOLE

Logger* Logger::GetLogger()
{
	if (!m_instance)
	{
		m_instance = new Logger();
	}

	return m_instance;
}


int Logger::Log(LogLevel level, const char* format, ...)
{
	va_list argList;
	va_start(argList, format);

	int charsWritten = 0;

	char* temp = new char[1024];

	time_t now = time(0);
	struct tm tstruct;
	tstruct = *localtime(&now);
	
	strftime(temp, 30, "%b %d %G - %r", &tstruct);

	charsWritten += PrintF("[%s]\n", temp);

	switch (level)
	{
	case Log_All:
		break;
	case Log_Info:
		charsWritten += PrintF("Info: ");
		break;
	case Log_Debug:
		charsWritten += PrintF("Debug: ");
		break;
	case Log_Warning:
		charsWritten += PrintF("Warning: ");
		break;
	case Log_Severe:
		charsWritten += PrintF("Severe: ");
		break;
	default:
		break;
	}

	charsWritten += PrintFormatted(format, argList);

	charsWritten += PrintF("\n");

	va_end(argList);

	return charsWritten;
}


char* Logger::getFormattedText(const char* format, ...)
{
	va_list argList;
	va_start(argList, format);

	const int MAX_CHARS = 1023;
	static char s_buffer[MAX_CHARS + 1];
	vsnprintf(s_buffer, MAX_CHARS, format, argList);
	s_buffer[MAX_CHARS] = '\0';

	va_end(argList);

	return s_buffer;
}


int Logger::PrintFormatted(const char* format, va_list argList)
{
	const int MAX_CHARS = 1023;
	static char s_buffer[MAX_CHARS + 1];
	int charsWritten = vsnprintf(s_buffer, MAX_CHARS, format, argList);
	s_buffer[MAX_CHARS] = '\0';

#ifdef CONSOLE
	WriteConsoleA(m_consoleHandle, s_buffer, strlen(s_buffer), NULL, NULL);
#endif // CONSOLE

	OutputDebugStringA(s_buffer);
	m_lastLog << s_buffer;
	m_currentLog << s_buffer;
}


int Logger::PrintF(const char* format, ...)
{
	va_list argList;
	va_start(argList, format);

	int charsWritten = PrintFormatted(format, argList);

	va_end(argList);

	return charsWritten;
}


int Logger::PrintLineFormatted(const char* format, va_list argList)
{
	int charsWritten = PrintFormatted(format, argList);
	charsWritten += PrintF("\n");
	return charsWritten;
}


int Logger::PrintLineF(const char* format, ...)
{
	va_list argList;
	va_start(argList, format);

	int charsWritten = PrintLineFormatted(format, argList);

	va_end(argList);

	return charsWritten;
}




#endif	// LOGGER