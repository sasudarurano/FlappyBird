// main.cpp
#include "Game.h"
#include <ctime>
#include <cstdlib>

int main() {
    // Inisialisasi random seed sekali saja
    srand(static_cast<unsigned>(time(0)));

    Game game; // Buat objek game
    game.run(); // Jalankan game

    return 0; // Selesai
}