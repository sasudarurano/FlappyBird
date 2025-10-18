// Pipe.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"

class Pipe {
public:
    Pipe(const sf::Texture& texture);

    void draw(sf::RenderWindow& window);
    void update();
    void reset();
    
    // Logika "Fail": Cek tabrakan
    bool checkCollision(const sf::FloatRect& birdBounds) const;
    
    // Logika "Score": Cek jika burung melewati pipa
    bool updateScore(const sf::FloatRect& birdBounds);

private:
    void spawnPipe();
    
    const sf::Texture& texture; // Simpan referensi ke tekstur
    std::vector<sf::Sprite> pipes;
    std::vector<bool> scoredPipes; // Lacak pipa yang sudah diberi skor
    sf::Clock spawnClock;
};