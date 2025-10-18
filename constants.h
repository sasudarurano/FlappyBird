// constants.h
#pragma once

// Pengaturan Layar
const unsigned int SCREEN_WIDTH  = 400;
const unsigned int SCREEN_HEIGHT = 600;

// Pengaturan Aset
const float BIRD_SCALE = 0.1f;
const float PIPE_SCALE = 0.2f;
const float BACKGROUND_SCALE_X = 1.4f; // Sesuaikan agar pas
const float BACKGROUND_SCALE_Y = 1.1f; // Sesuaikan agar pas

// Pengaturan Fisika
const float GRAVITY = 0.4f;
const float JUMP_FORCE = -8.0f;
const float PIPE_SPEED = -3.0f;
const float PIPE_SPAWN_TIME = 1.6f;
const int GAP_HEIGHT = 257; // Jarak antara pipa atas dan bawah