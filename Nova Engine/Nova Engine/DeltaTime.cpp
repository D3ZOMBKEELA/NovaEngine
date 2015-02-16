#include "DeltaTime.h"

DeltaTime::DeltaTime()
{
}

DeltaTime::~DeltaTime()
{
}

bool DeltaTime::Initialize()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if (m_frequency == 0)
	{
		return false;
	}

	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}

void DeltaTime::Tick()
{
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (float)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;

	return;
}

float DeltaTime::GetTime()
{
	if (m_frameTime < 3.0F)
	{
		return m_frameTime;
	}
	else
	{
		return 3.0F;
	}
}