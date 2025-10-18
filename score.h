// Score.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Score {
public:
    Score(const sf::Font& font);

    void drawPrompt(sf::RenderWindow& window, const std::string& message);
    void drawScore(sf::RenderWindow& window);
    
    void increment();
    void reset();

private:
    void centerText(sf::Text& text);

    int score;
    sf::Text scoreText;
    sf::Text promptText;
};