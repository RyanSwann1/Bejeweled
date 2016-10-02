#pragma once

class Timer
{
public:
	Timer(const float expirationTime, const float timeElasped);
	~Timer() {}

	float getElaspedTime() const { return m_timeElasped; }
	bool isExpired() const { return (m_increasingTimer ? m_timeElasped >= m_expirationTime : m_timeElasped <= m_expirationTime); }
	void update(const float timeElasped);
	void restart() { m_timeElasped = m_initialTimeValue; }
	
private:
	float m_expirationTime;
	float m_timeElasped;
	float m_initialTimeValue;
	bool m_increasingTimer;

	void decideTimer();

};

