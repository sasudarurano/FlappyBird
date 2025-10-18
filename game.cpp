// Game.cpp
#include "Game.h"
#include "constants.h"
#include <memory> 
#include <algorithm> // Untuk std::max, std::min

// --- Helper function (sudah benar) ---
void centerTextOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
}

// --- Implementasi Game ---

// ===== PERBAIKAN DI CONSTRUCTOR =====
Game::Game() : 
    window(sf::VideoMode::getDesktopMode(), "Flappy Bird C++", sf::State::Fullscreen) // Perbaikan: sf::Style::fullscreen -> sf::State::Fullscreen
{
    window.setFramerateLimit(60);
    
    // Setup View (ukuran logis game kita adalah SCREEN_WIDTH x SCREEN_HEIGHT)
    gameView.setSize({static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)});
    gameView.setCenter({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f});

    // 1. PANGGIL loadAssets() PERTAMA
    loadAssets(); 
    
    // 2. SEKARANG BUAT OBJEK (aset sudah terisi)
    background = std::make_unique<sf::Sprite>(bgTexture);
    
    // PERBAIKAN: Skalakan background agar pas dengan gameView (400x600)
    float scaleX = static_cast<float>(SCREEN_WIDTH) / background->getLocalBounds().size.x;
    float scaleY = static_cast<float>(SCREEN_HEIGHT) / background->getLocalBounds().size.y;
    float finalScale = std::max(scaleX, scaleY); 
    background->setScale({finalScale, finalScale});
    background->setPosition({(SCREEN_WIDTH - background->getGlobalBounds().size.x) / 2.0f, 
                             (SCREEN_HEIGHT - background->getGlobalBounds().size.y) / 2.0f});

    bird = std::make_unique<Bird>(birdTexture);
    pipe = std::make_unique<Pipe>(pipeTexture);
    score = std::make_unique<Score>(font);
    flapSound = std::make_unique<sf::Sound>(flapBuffer);
    hitSound = std::make_unique<sf::Sound>(hitBuffer);

    // 3. Set state
    state = Ready; 
}

void Game::loadAssets() {
    if (!bgTexture.loadFromFile("assets/background.png")) { /* handle error */ }
    if (!birdTexture.loadFromFile("assets/bird.png")) { /* handle error */ }
    if (!pipeTexture.loadFromFile("assets/pipe.png")) { /* handle error */ }
    if (!font.openFromFile("assets/arial.ttf")) { /* handle error */ } 
    if (!flapBuffer.loadFromFile("assets/flap.wav")) { /* handle error */ }
    if (!hitBuffer.loadFromFile("assets/hit.wav")) { /* handle error */ }
}

void Game::run() {
    while (window.isOpen()) {
        processInput();
        update();
        render();
    }
}

void Game::processInput() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                window.close();
            }
            if (keyPressed->code == sf::Keyboard::Key::Space) {
                if (state == Ready) {
                    state = Playing;
                    bird->flap(); 
                    flapSound->play(); 
                } else if (state == Playing) {
                    bird->flap(); 
                    flapSound->play(); 
                } else if (state == GameOver) {
                    restartGame();
                }
            }
        }
    }
}

void Game::update() {
    if (state != Playing) {
        return; 
    }
    
    bird->update(); 
    pipe->update(); 

    // Logika "Fail": Cek tabrakan
    bool collision = false;
    
    if (pipe->checkCollision(bird->getGlobalBounds())) { 
        collision = true;
    }
    
    float birdY = bird->getPositionY(); 
    if (birdY > (SCREEN_HEIGHT - bird->getGlobalBounds().size.y / 2.0f) || birdY < 0) {
        collision = true;
    }
    
    if (collision) {
        state = GameOver;
        hitSound->play(); 
    }

    // Logika "Score":
    if (pipe->updateScore(bird->getGlobalBounds())) { 
        score->increment(); 
    }
}

// Fungsi helper untuk menghitung viewport letterbox
void Game::calculateLetterboxViewport() {
    // Ukuran sebenarnya window
    float windowRatio = static_cast<float>(window.getSize().x) / window.getSize().y;
    // Aspek rasio target game kita (400x600)
    float viewRatio = static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT;

    float viewportWidth = 1.0f;
    float viewportHeight = 1.0f;
    float viewportX = 0.0f;
    float viewportY = 0.0f;

    if (windowRatio > viewRatio) {
        // Window lebih lebar dari game (bilah hitam di kiri/kanan)
        viewportWidth = viewRatio / windowRatio;
        viewportX = (1.0f - viewportWidth) / 2.0f;
    } else {
        // Window lebih tinggi dari game (bilah hitam di atas/bawah)
        viewportHeight = windowRatio / viewRatio;
        viewportY = (1.0f - viewportHeight) / 2.0f;
    }

    // Set viewport untuk gameView (ini mengubah bagaimana gameView dipetakan ke window)
    sf::FloatRect viewport;
    viewport.position = {viewportX, viewportY};
    viewport.size = {viewportWidth, viewportHeight};
    gameView.setViewport(viewport);
}

void Game::render() {
    window.clear(); // Hapus layar (akan berwarna hitam)
    
    // PERBAIKAN: Hitung dan terapkan viewport letterbox setiap frame
    calculateLetterboxViewport();
    window.setView(gameView);

    // Gambar semua elemen
    window.draw(*background); 
    pipe->draw(window); 
    bird->draw(window); 

    // Gambar UI berdasarkan state
    if (state == Ready) {
        score->drawPrompt(window, "Klik Spasi untuk Mulai"); 
    } else if (state == Playing) {
        score->drawScore(window); 
    } else if (state == GameOver) {
        score->drawScore(window); 
        score->drawPrompt(window, "Game Over!\nKlik Spasi untuk Mulai Lagi"); 
    }

    window.display();
}

void Game::restartGame() {
    state = Ready;
    bird->reset(); 
    pipe->reset(); 
    score->reset(); 
}