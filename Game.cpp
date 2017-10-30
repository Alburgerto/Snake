#include "Game.h"

Game::Game() : m_window("Snake", sf::Vector2u(800, 600)),
			   m_snake(m_world.getBlockSize(), &m_textbox),
			   m_world(sf::Vector2u(800, 600))
{
	m_clock.restart();
	srand(time(nullptr));
	m_elapsed = 0.0f;
	
	m_textbox.setup(5, 14, 350, sf::Vector2f(225, m_world.getBlockSize()));
	m_textbox.add("Seeded random number generator with: " + std::to_string(time(nullptr)));
}

Game::~Game() {}
sf::Time Game::getElapsed() { return m_clock.getElapsedTime(); }
void Game::restartClock() { m_elapsed += m_clock.restart().asSeconds(); }
Window* Game::getWindow() { return &m_window; }

void Game::handleInput() {
	// Input handling.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& m_snake.getPhysicalDirection() != Direction::Down) {
		m_snake.setDirection(Direction::Up);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& m_snake.getPhysicalDirection() != Direction::Up) {
		m_snake.setDirection(Direction::Down);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& m_snake.getPhysicalDirection() != Direction::Right) {
		m_snake.setDirection(Direction::Left);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& m_snake.getPhysicalDirection() != Direction::Left) {
		m_snake.setDirection(Direction::Right);
	}
}

void Game::update() {
	m_window.update();
	float timestep = 1.0f / m_snake.getSpeed();
	if (m_elapsed >= timestep) {
		m_snake.tick();
		m_world.update(m_snake);
		m_elapsed -= timestep;
		if (m_snake.hasLost()) {
			m_textbox.add("GAME OVER! Score: " + std::to_string((long long)m_snake.getScore()));
			m_snake.reset();
		}
	}
}

void Game::render() {
	m_window.beginDraw();
	// Render here.
	m_world.render(*m_window.getRenderWindow());
	m_snake.render(*m_window.getRenderWindow());
	m_textbox.render(*m_window.getRenderWindow());

	m_window.endDraw();
}