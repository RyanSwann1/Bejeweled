#include "Window.h"



Window::Window(SharedContext* sharedContext, const sf::Vector2u & size, const std::string & name)
	: m_eventSystem(sharedContext)
{
	setup(size, name);
	
}

Window::~Window()
{
}

void Window::setup(const sf::Vector2u& size, const std::string& name)
{
	m_name = name;
	m_size = size;
	m_fullScreen = false;
	create();
}

void Window::update()
{
	sf::Event m_event;
	while (m_window.pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		m_eventSystem.update(m_event);
	}
}

void Window::create()
{
	auto style = (m_fullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create(sf::VideoMode(m_size.x, m_size.y), m_name, style);
}
