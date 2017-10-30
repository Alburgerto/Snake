#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window {
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void beginDraw();
	void endDraw();
	void draw(sf::Drawable& l_drawable);

	void update();
	void toggleFullscreen();
	sf::RenderWindow* getRenderWindow();

	bool isDone() const;
	bool isFullscreen() const;
	sf::Vector2u getSize() const;
private:
	void setup(const std::string& title, const sf::Vector2u& size);
	void create();
	void destroy();

	sf::RenderWindow m_window;
	sf::Vector2u m_size;
	std::string m_title;

	bool m_isFullscreen;
	bool m_isDone;
};