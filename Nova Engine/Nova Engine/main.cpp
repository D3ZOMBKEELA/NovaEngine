#include "NovaEngine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpScmdLine, int iCmdShow)
{
	NovaEngine engine; // Change this to singleton

	bool result;

	result = engine.Initialize();
	if (!result)
	{
		return 1;
	}

	while (result)
	{
		result = engine.Tick();
	}

	engine.Shutdown();

	return 0;
}