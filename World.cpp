#include "World.h"

World::World(sf::Vector2u l_windowSize) {
	m_blockSize = 16;
	m_windowSize = l_windowSize;

	respawnApple();

	m_appleShape.setFillColor(sf::Color::Red);
	m_appleShape.setRadius(m_blockSize / 2);

	for (int i = 0; i < 4; ++i) { // 4 rectangles, representing the walls
		m_bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2)) {
			m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
		} else {
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
		}
		if (i < 2) {
			m_bounds[i].setPosition(0, 0);
		} else {
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}
}

World::~World() {}

int World::getBlockSize() const {
	return m_blockSize;
}

void World::respawnApple() {
	int maxX = (m_windowSize.x / m_blockSize) - 2;
	int maxY = (m_windowSize.y / m_blockSize) - 2;
	m_apple  = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	m_appleShape.setPosition(m_apple.x * m_blockSize, m_apple.y * m_blockSize);
}

void World::update(Snake& l_player) {
	if (l_player.getPosition() == m_apple) {
		l_player.extend();
		l_player.increaseScore();
		respawnApple();
	}

	int gridSizeX = m_windowSize.x / m_blockSize;
	int gridSizeY = m_windowSize.y / m_blockSize;

	if (l_player.getPosition().x <= 0 ||
		l_player.getPosition().y <= 0 ||
		l_player.getPosition().x >= gridSizeX - 1 ||
		l_player.getPosition().y >= gridSizeY - 1) 
	{
		l_player.lose(); 
	}
}

void World::render(sf::RenderWindow& l_window) {
	for (int i = 0; i < 4; ++i) {
		l_window.draw(m_bounds[i]);
	}
	l_window.draw(m_appleShape);
}