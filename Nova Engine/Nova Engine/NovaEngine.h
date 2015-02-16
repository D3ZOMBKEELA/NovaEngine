#pragma once

#include "Window.h"
#include "NovaLogger.h"

class NovaEngine
{
public:
	NovaEngine();
	~NovaEngine();

	bool Initialize();
	bool Tick();
	void Shutdown();

private:
	bool Update();
	bool Render();

private:
	Window window; // Temp, change to either a pointer or a singleton
};