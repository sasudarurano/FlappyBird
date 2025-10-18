// Pipe.cpp
#include "Pipe.h"
#include "constants.h" // Pastikan constants.h punya PIPE_SCALE & SCREEN_WIDTH
#include <cstdlib> // Untuk rand()

Pipe::Pipe(const sf::Texture& texture) : texture(texture) {
    // Kosong, reset() akan dipanggil oleh Game
}

void Pipe::draw(sf::RenderWindow& window) {
    for (const auto& pipe : pipes) {
        window.draw(pipe);
    }
}

void Pipe::update() {
    // 1. Munculkan Pipa
    if (spawnClock.getElapsedTime().asSeconds() > PIPE_SPAWN_TIME) {
        spawnPipe();
        spawnClock.restart();
    }

    // 2. Gerakkan & Hapus Pipa
    for (size_t i = 0; i < pipes.size(); ++i) {
        pipes[i].move({PIPE_SPEED, 0.f});

        // Hapus jika keluar layar
        if (pipes[i].getPosition().x < -100) {
            // Hapus pipa (pasangan atas & bawah)
            pipes.erase(pipes.begin() + i);
            pipes.erase(pipes.begin() + i); // Hapus pasangannya
            scoredPipes.erase(scoredPipes.begin()); // Hapus status skor
            --i; // Mundur 1 agar tidak skip
        }
    }
}

void Pipe::spawnPipe() {
    int minY = 150;
    int maxY = static_cast<int>(SCREEN_HEIGHT) - 150;
    int randomPos = (rand() % (maxY - minY + 1)) + minY;

    // Pipa bawah
    sf::Sprite pipeBottom(texture);
    pipeBottom.setScale({PIPE_SCALE, PIPE_SCALE});
    pipeBottom.setPosition({static_cast<float>(SCREEN_WIDTH), static_cast<float>(randomPos + GAP_HEIGHT / 2)});
    pipes.push_back(pipeBottom);

    // Pipa atas
    sf::Sprite pipeTop(texture);
    pipeTop.setScale({PIPE_SCALE, PIPE_SCALE});
    
    // PERBAIKAN: Hitung lebar pipa dengan benar
    float pipeWidth = pipeTop.getLocalBounds().size.x * PIPE_SCALE;
    
    pipeTop.setRotation(sf::degrees(180.f));
    pipeTop.setPosition({
        static_cast<float>(SCREEN_WIDTH) + pipeWidth,
        static_cast<float>(randomPos - GAP_HEIGHT / 2)
    });
    pipes.push_back(pipeTop);

    // Tambahkan status "belum diskor" untuk pasangan pipa ini
    scoredPipes.push_back(false);
}

// ===== PERBAIKAN BESAR DI SINI =====
bool Pipe::checkCollision(const sf::FloatRect& birdBounds) const {
    
    // "Mengecilkan" bounding box burung untuk tabrakan
    sf::FloatRect birdHitbox = birdBounds;
    // (Angka 0.15f dan 0.2f bisa Anda ubah-ubah)
    float birdPaddingX = birdHitbox.size.x * 0.15f; // Kecilkan 15% kiri/kanan
    float birdPaddingY = birdHitbox.size.y * 0.20f; // Kecilkan 20% atas/bawah
    
    birdHitbox.position.x += birdPaddingX;
    birdHitbox.size.x -= 2 * birdPaddingX;
    birdHitbox.position.y += birdPaddingY;
    birdHitbox.size.y -= 2 * birdPaddingY;


    for (const auto& pipe : pipes) {
        sf::FloatRect pipeHitbox = pipe.getGlobalBounds();
        
        // "Mengecilkan" bounding box pipa
        // (Kita hanya perlu mengecilkan sumbu X agar tidak terlalu sensitif di samping)
        float pipePaddingX = pipeHitbox.size.x * 0.10f; // Kecilkan 10% kiri/kanan
        pipeHitbox.position.x += pipePaddingX;
        pipeHitbox.size.x -= 2 * pipePaddingX;

        // Cek tabrakan dengan hitbox yang sudah dikecilkan
        if (birdHitbox.findIntersection(pipeHitbox).has_value()) {
            return true;
        }
    }
    return false;
}

bool Pipe::updateScore(const sf::FloatRect& birdBounds) {
    // Kita hanya cek pipa bawah (indeks genap: 0, 2, 4, ...)
    for (size_t i = 0; i < pipes.size(); i += 2) {
        // 'i' adalah pipa bawah, 'i+1' adalah pipa atas
        if (i / 2 < scoredPipes.size()) { // Pastikan indeks tidak keluar batas
            size_t scoreIndex = i / 2;
            
            // Jika pipa belum diskor DAN burung sudah melewatinya
            // (Gunakan .position.x dari bounds burung)
            if (!scoredPipes[scoreIndex] && pipes[i].getPosition().x < birdBounds.position.x) {
                scoredPipes[scoreIndex] = true; // Tandai sudah diskor
                return true; // Beri tahu 'Game' untuk menambah skor
            }
        }
    }
    return false; // Tidak ada skor baru
}

void Pipe::reset() {
    pipes.clear();
    scoredPipes.clear();
    spawnClock.restart();
}