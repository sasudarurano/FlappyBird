// Score.cpp
#include "Score.h"
#include "constants.h"

// ===== PERBAIKAN DI CONSTRUCTOR =====
// Kita harus menginisialisasi 'scoreText' dan 'promptText'
// SEBELUM body constructor ( { ) dimulai.
Score::Score(const sf::Font& font) : 
    scoreText(font),  // <-- Inisialisasi sf::Text dengan font
    promptText(font)  // <-- Inisialisasi sf::Text dengan font
{
    // Sekarang kita atur propertinya
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(2);

    promptText.setCharacterSize(24);
    promptText.setFillColor(sf::Color::White);
    promptText.setOutlineColor(sf::Color::Black);
    promptText.setOutlineThickness(2);
    
    reset();
}

// ===== PERBAIKAN DI centerText =====
void Score::centerText(sf::Text& text) {
    sf::FloatRect textRect = text.getLocalBounds();
    // Gunakan .position.x, .size.x, .position.y, .size.y
    text.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});
    text.setPosition({SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f});
}

void Score::drawPrompt(sf::RenderWindow& window, const std::string& message) {
    promptText.setString(message);
    centerText(promptText);
    window.draw(promptText);
}

void Score::drawScore(sf::RenderWindow& window) {
    scoreText.setString(std::to_string(score));
    // Pusatkan teks skor
    sf::FloatRect textRect = scoreText.getLocalBounds();
    scoreText.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});
    scoreText.setPosition({SCREEN_WIDTH / 2.0f, 50.f}); // Posisi skor di atas tengah
    window.draw(scoreText);
}

void Score::increment() {
    score++;
}

void Score::reset() {
    score = 0;
}