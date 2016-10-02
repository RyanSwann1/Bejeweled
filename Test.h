#pragma once
class TestClass
{
public:
	TestClass() 
	{
		m_numb = 5;
	}

	int getNumb() const { return m_numb; }

private:
	int m_numb;
};