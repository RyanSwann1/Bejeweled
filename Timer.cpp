#include "Timer.h"
#include "SharedContext.h"

Timer::Timer(const float expirationTime, const float timeElasped)
	: m_expirationTime(expirationTime),
	m_timeElasped(timeElasped),
	m_initialTimeValue(timeElasped)
{
	decideTimer();
}

void Timer::update(const float timeElasped)
{
	m_timeElasped += timeElasped;
}

void Timer::decideTimer()
{
	if (m_expirationTime >= m_timeElasped) {
		m_increasingTimer = true;
	}

	else {
		m_increasingTimer = false;
	}
}
