#include "Snake.h"

Snake::Snake(int l_blockSize, Textbox* l_log) {
	m_log = l_log;
	m_size = l_blockSize;

	m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
	reset();
}

Snake::~Snake() {}

void Snake::setDirection(Direction l_dir) {
	m_dir = l_dir;
}

Direction Snake::getDirection() const {
	return m_dir;
}

int Snake::getSpeed() const {
	return m_speed;
}

sf::Vector2i Snake::getPosition() const {
	return (!m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1, 1));
}

int Snake::getLives() const {
	return m_lives;
}

int Snake::getScore() const {
	return m_score;
}

void Snake::increaseScore() {
	m_score += 10;
	m_log->add("You ate an apple. Score: " + std::to_string((long long)m_score));
}

bool Snake::hasLost() const {
	return m_lost;
}

void Snake::lose() {
	m_lost = true;
}

void Snake::toggleLost() {
	m_lost = !m_lost;
}

Direction Snake::getPhysicalDirection() {
	if (m_snakeBody.size() <= 1) {
		return Direction::None;
	}

	SnakeSegment& head = m_snakeBody[0];
	SnakeSegment& neck = m_snakeBody[1];

	if (head.position.x == neck.position.x) {
		return (head.position.y > neck.position.y
			? Direction::Down : Direction::Up);
	}
	else if (head.position.y == neck.position.y) {
		return (head.position.x > neck.position.x
			? Direction::Right : Direction::Left);
	}

	return Direction::None;
}

void Snake::extend() {
	if (m_snakeBody.empty()) { return; }
	SnakeSegment& tail_head = m_snakeBody[m_snakeBody.size() - 1];
	if (m_snakeBody.size() > 1) {
		SnakeSegment& tail_bone = m_snakeBody[m_snakeBody.size() - 2];
		if (tail_head.position.x == tail_bone.position.x) { // Last 2 segments vertical
			if (tail_head.position.y > tail_bone.position.y) {
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			} else {
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_bone.position.y - 1));
			}
		} else { // Last 2 segments horizontal
			if (tail_head.position.x > tail_bone.position.x) {
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			} else {
				m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_bone.position.y));
			}
		}
	} else { // Only 1 fragment
		if (m_dir == Direction::Up) {
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		} else if (m_dir == Direction::Down) {
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		} else if (m_dir == Direction::Right) {
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		} else if (m_dir == Direction::Left) {
			m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		}
	}
}

void Snake::reset() {
	m_snakeBody.clear(); // Remove all snake segments

	m_snakeBody.push_back(SnakeSegment(5, 7));
	m_snakeBody.push_back(SnakeSegment(5, 6));
	m_snakeBody.push_back(SnakeSegment(5, 5));

	setDirection(Direction::None); // Start off still. Wait por player to press a key
	m_speed = 15;
	m_lives = 3;
	m_score = 0;
	m_lost = false;
}

void Snake::move() {
	for (int i = m_snakeBody.size() - 1; i > 0; --i) {
		m_snakeBody[i].position = m_snakeBody[i - 1].position;
	}
	if (m_dir == Direction::Up) {
		--m_snakeBody[0].position.y;
	}
	else if (m_dir == Direction::Down) {
		++m_snakeBody[0].position.y;
	}
	else if (m_dir == Direction::Right) {
		++m_snakeBody[0].position.x;
	}
	else if (m_dir == Direction::Left) {
		--m_snakeBody[0].position.x;
	}
}

void Snake::tick() {
	if (m_snakeBody.empty() || m_dir == Direction::None) {
		return;
	}
	move();
	checkCollision();
}

void Snake::cut(int l_segments) {
	m_snakeBody.erase(m_snakeBody.begin() + l_segments, m_snakeBody.end());	
	--m_lives;
	if (m_lives > 0) {
		m_log->add("Remaining lives: " + std::to_string(m_lives));
	} else {
		m_log->add("Be careful not to cut yourself next time!");
	}
	if (m_lives < 1) { lose(); }
}

void Snake::render(sf::RenderWindow& l_window) {
	if (m_snakeBody.size() < 1) { return; }
	// Head
	SnakeContainer::const_iterator head = m_snakeBody.begin();
	m_bodyRect.setFillColor(sf::Color::Yellow);
	m_bodyRect.setPosition(head->position.x * m_size, head->position.y * m_size);
	l_window.draw(m_bodyRect);
	// Body
	m_bodyRect.setFillColor(sf::Color::Green);
	for (SnakeContainer::const_iterator iter = m_snakeBody.begin() + 1; iter != m_snakeBody.end(); ++iter) {
		m_bodyRect.setPosition(iter->position.x * m_size, iter->position.y * m_size);
		l_window.draw(m_bodyRect);
	}
}

void Snake::checkCollision() {
	if (m_snakeBody.size() < 5) { return; } // Cannot collide with body if 4 or less segments
	SnakeSegment& head = m_snakeBody.front();
	for (SnakeContainer::const_iterator iter = m_snakeBody.begin() + 1; iter != m_snakeBody.end(); ++iter) {
		if (head.position == iter->position) {
			int segments = m_snakeBody.end() - iter;
			cut(segments);
			break;
		}
	}
}