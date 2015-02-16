#pragma once

#include <Windows.h>

class DeltaTime
{
public:
	DeltaTime();
	~DeltaTime();

	bool Initialize();
	void Tick();

	float GetTime();

private:
	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime;
};