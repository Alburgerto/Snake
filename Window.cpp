	#include "Window.h"

Window::Window() { setup("Window", sf::Vector2u(640, 480)); }
Window::Window(const std::string& title, const sf::Vector2u& size) { setup(title, size); }
Window::~Window() { destroy(); }
void Window::setup(const std::string& title, const sf::Vector2u& size) {
	m_title = title;
	m_size = size;
	m_isFullscreen = false;
	m_isDone = false;	
	create();
}

void Window::create() {
	sf::Uint32 style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_size.x, m_size.y, 32 }, m_title, style);
}
void Window::destroy() { m_window.close(); }

void Window::beginDraw() { m_window.clear(sf::Color::Black); }
void Window::endDraw() { m_window.display(); }
void Window::draw(sf::Drawable& l_drawable) { m_window.draw(l_drawable); }

void Window::update() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { m_isDone = true; }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { m_isDone = true; }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) { toggleFullscreen(); }
	}
}

sf::RenderWindow* Window::getRenderWindow() { return &m_window; }

void Window::toggleFullscreen() {
	m_isFullscreen = !m_isFullscreen;
	destroy();
	create();
}
bool Window::isDone() const { return m_isDone; }
bool Window::isFullscreen() const { return m_isFullscreen; }
sf::Vector2u Window::getSize() const { return m_size; }