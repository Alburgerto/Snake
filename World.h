#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class World {
public:
	World(sf::Vector2u l_windowSize);
	~World();
	int getBlockSize() const;
	void respawnApple();
	void update(Snake& l_player);
	void render(sf::RenderWindow& l_window);
private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_apple;
	int m_blockSize;
	sf::CircleShape m_appleShape;
	sf::RectangleShape m_bounds[4];
};