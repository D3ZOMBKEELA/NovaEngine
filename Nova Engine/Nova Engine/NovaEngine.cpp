#include "NovaEngine.h"

NovaEngine::NovaEngine()
{
}

NovaEngine::~NovaEngine()
{
}

bool NovaEngine::Initialize()
{
	bool result;

	window.Initialize("Nova Engine");

#ifdef CONSOLE
	Logger::GetLogger()->CreateConsole();
#endif // CONSOLE

#ifdef LOGGER
	Logger::GetLogger()->Log(Log_All, "Window initialized successfully");
#endif // LOGGER

	return true;
}

bool NovaEngine::Tick()
{
	MSG msg;
	bool result;
	bool done;
	bool returnVal = true;

	result = true;
	done = false;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
			returnVal = false;
		}
		else
		{
			result = Update();
			if (!result)
			{
				done = true;
				returnVal = false;
			}

			result = Render();
			if (!result)
			{
				done = true;
				returnVal = false;
			}
		}
	}

	return returnVal;
}

void NovaEngine::Shutdown()
{
	window.Shutdown();

#ifdef CONSOLE
	Logger::GetLogger()->CloseConsole();
#endif

}

bool NovaEngine::Update()
{
	return true;
}

bool NovaEngine::Render()
{
	return true;
}