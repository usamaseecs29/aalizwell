#ifndef AALIZWELL_CONSTANTS_H
#define AALIZWELL_CONSTANTS_H

// Centralized configuration

constexpr int MAX_HP = 5;
constexpr int MAX_HOPIUM = 50;
constexpr int PLAYER_STEP = 3;
constexpr int PLAYER_LEFT_LIMIT = 3;
constexpr int PLAYER_RIGHT_LIMIT = 52;

constexpr int METER_WIDTH = 10;    // characters for hopium visual bar
constexpr int CHAT_LINES = 18;
constexpr int FRAME_SLEEP_MS = 40;

constexpr int ENEMY_MIN_X = 5;
constexpr int ENEMY_X_RANGE = 45;
constexpr int ENEMY_START_Y = 2;
constexpr int ENEMY_DEATH_Y = 25;

constexpr int KHAPPA_TIMER_RESET = 200;
constexpr int KHAPPA_SPAWN_CHANCE_DIV = 250; // 1 in 250 chance when timer is zero

// Hopium rates expressed as percentages of MAX_HOPIUM
constexpr int HOPIUM_DRAIN_PERCENT_PER_TICK = 2;
constexpr int HOPIUM_KILL_GAIN_PERCENT = 12;
constexpr int HOPIUM_KHAPPA_GAIN_PERCENT = 18;
constexpr int HOPIUM_PRESS_SPACE_GAIN_PERCENT = 2;

// Percent thresholds for degraded behavior
constexpr int THRESH_AGGRO_PERCENT = 40;
constexpr int THRESH_MISFIRE_PERCENT = 10;
constexpr int THRESH_TELEPORT_PERCENT = 5;

#endif