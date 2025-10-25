#ifndef AALIZWELL_FUNCTIONS_H
#define AALIZWELL_FUNCTIONS_H

#include <string>
#include <vector>
#include <fstream>

//data struct for leaderboard entries.
struct LBEntry {
    std::string name;
    int score;
    int hopium;
};

// Small helpers
int clampInt(int v, int lo, int hi);
int percentOf(int value, int percent);
int randRange(int lo, int hi);

// UI / leaderboard helpers (declarations)
void clearChatArea();
void randomChatMessage();
void scoreBoard(int score, int hp, int maxhp, int hopiumMeter);
void writeLeaderboardAndShow(const LBEntry& e);

extern int chatLine;
extern const std::vector<std::string> dushmans;
extern const size_t DUSHMANS_COUNT;

#endif