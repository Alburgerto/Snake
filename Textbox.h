#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using MessageContainer = std::vector<std::string>;

class Textbox {
public:
	Textbox();
	Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos); 
	~Textbox();

	//  Arguments: Number visible lines, size of char (pixels), width entire textbox (pixels), position screen where will be drawn
	void setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos);
	void add(std::string l_message);
	void clear();
	void render(sf::RenderWindow& l_window);
private:
	MessageContainer m_messages;
	int m_numVisible;

	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_content;
};