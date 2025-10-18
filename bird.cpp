// Bird.cpp
#include "Bird.h"

Bird::Bird(const sf::Texture& texture) : sprite(texture) {
    sprite.setScale({BIRD_SCALE, BIRD_SCALE});
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
    reset();
}


void Bird::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Bird::update() {
    velocityY += GRAVITY;
    sprite.move({0.f, velocityY});

    // Animasi rotasi sederhana
    if (velocityY > 0) {
        setRotation(std::min(90.f, velocityY * 5));
    } else {
        setRotation(std::max(-25.f, velocityY * 3));
    }
}

void Bird::flap() {
    velocityY = JUMP_FORCE;
}

void Bird::reset() {
    sprite.setPosition({100.f, SCREEN_HEIGHT / 2.0f});
    velocityY = 0;
    sprite.setRotation(sf::degrees(0.f));
}

sf::FloatRect Bird::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

float Bird::getPositionY() const {
    return sprite.getPosition().y;
}

void Bird::setRotation(float angle) {
    sprite.setRotation(sf::degrees(angle));
}