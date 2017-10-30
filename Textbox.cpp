#include "Textbox.h"

Textbox::Textbox() {
	setup(5, 9, 200, sf::Vector2f(0, 0));
}

Textbox::Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos) {
	setup(l_visible, l_charSize, l_width, l_screenPos);
}

Textbox::~Textbox() { clear(); }

void Textbox::setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos) {
	m_numVisible = l_visible;
	sf::Vector2f l_offset(2.0f, 2.0f);
	m_font.loadFromFile("Assets/Font/arial.ttf");
	m_content.setFont(m_font);
	m_content.setString("");
	m_content.setCharacterSize(l_charSize);
	m_content.setFillColor(sf::Color::White);
	m_content.setPosition(l_screenPos + l_offset);

	m_backdrop.setSize(sf::Vector2f(l_width, (l_visible * (l_charSize * 1.2f))));
	m_backdrop.setFillColor(sf::Color(90, 90, 90, 90));
	m_backdrop.setPosition(l_screenPos);
}
/*
void Textbox::setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos) {
	m_numVisible = l_visible;

	sf::Vector2f l_offset(2.0f, 2.0f);

	m_font.loadFromFile("arial.ttf");
	m_content.setFont(m_font);
	m_content.setString("");
	m_content.setCharacterSize(l_charSize);
	m_content.setColor(sf::Color::White);
	m_content.setPosition(l_screenPos + l_offset);

	m_backdrop.setSize(sf::Vector2f(
		l_width, (l_visible * (l_charSize * 1.2f))));
	m_backdrop.setFillColor(sf::Color(90, 90, 90, 90));
	m_backdrop.setPosition(l_screenPos);
} */

void Textbox::add(std::string l_message) {
	m_messages.push_back(l_message);
	if (m_messages.size() < 6) { return; }
	m_messages.erase(m_messages.begin());
}

void Textbox::clear() {
	m_messages.clear();
}

void Textbox::render(sf::RenderWindow& l_window) {
	std::string l_content;
	for (std::string &iter : m_messages) {
		l_content.append(iter + "/n");
	}
	if (l_content != "") {
		m_content.setString(l_content);
		l_window.draw(m_backdrop);
		l_window.draw(m_content);
	}
}