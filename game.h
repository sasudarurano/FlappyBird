// Game.h
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory> 
#include "Bird.h"
#include "Pipe.h"
#include "Score.h"

class Game {
public:
    Game();
    void run(); 

private:
    void processInput();
    void update();
    void render();
    void restartGame();
    void loadAssets();
    void calculateLetterboxViewport(); // <-- TAMBAHKAN INI
    enum GameState { Ready, Playing, GameOver };
    GameState state;
    
    sf::RenderWindow window;
    sf::View gameView; // <-- TAMBAHKAN BARIS INI

    // Aset
    sf::Texture bgTexture, birdTexture, pipeTexture;
    sf::Font font;
    sf::SoundBuffer flapBuffer, hitBuffer;

    // Entitas
    std::unique_ptr<sf::Sprite> background;
    std::unique_ptr<Bird> bird;
    std::unique_ptr<Pipe> pipe;
    std::unique_ptr<Score> score;
    std::unique_ptr<sf::Sound> flapSound;
    std::unique_ptr<sf::Sound> hitSound;
};