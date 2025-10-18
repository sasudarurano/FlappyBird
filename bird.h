// Bird.h
#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"

class Bird {
public:
    Bird(const sf::Texture& texture);

    void draw(sf::RenderWindow& window);
    void update(); // Terapkan gravitasi
    void flap();   // Buat lompat
    void reset();
    sf::FloatRect getGlobalBounds() const;
    float getPositionY() const;
    void setRotation(float angle);

private:
    sf::Sprite sprite;
    float velocityY;
};