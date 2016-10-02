#pragma once

#include "EventSystem.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>

struct SharedContext;
class Window
{
	friend class Game;
public:
	Window(SharedContext* sharedContext, const sf::Vector2u& size = sf::Vector2u(500, 500), const std::string& name = "SFML_WINDOW");
	~Window();

	void beginDraw() { m_window.clear(sf::Color::Black); }
	void draw(sf::Drawable& drawable) { m_window.draw(drawable); }
	void endDraw() { m_window.display(); }

	void setup(const sf::Vector2u& size, const std::string& name);
	void update();
	
	sf::RenderWindow& getWindow() { return m_window; }

private:
	sf::RenderWindow m_window;
	sf::Vector2u m_size;
	std::string m_name;
	bool m_fullScreen;
	EventSystem m_eventSystem;

	void create();
};

