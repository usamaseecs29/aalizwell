// src/game.cpp
// Core game logic (uses helpers from functions.cpp and console.cpp)
// Project: Aal Iz Well - Tale of Seecs

#include "game.h"
#include "console.h"
#include "functions.h"
#include "constants.h"

#include <windows.h>
#include <conio.h>

#include <iostream>
#include <string>

using namespace std;

// GAME OVER
static void borders() {
    setColor(11);
    cout << "=================================================================\n";
    for (int i = 0; i < 28; ++i) cout << "I                                                               I\n";
    cout << "=================================================================\n";
    setColor(7);
}

static void gameOver(int score, int hopiumMeter) {
    system("cls");
    setColor(11);
    cout << "==================================================================\n";
    cout << "I                                                                I\n";
    setColor(12);
    cout << "I                           R . I . P                            I\n";
    setColor(11);
    cout << "I----------------------------------------------------------------I\n";
    cout << "I                                                                I\n";
    setColor(14);
    cout << "I       Here lies a SEECS student - Aal Iz Well's fallen hero.   I\n";
    cout << "I        Last words: 'It compiled... but at what cost?'          I\n";
    cout << "I                                                                I\n";
    setColor(11);
    cout << "I----------------------------------------------------------------I\n";
    setColor(10);
    cout << "I                 TOTAL HOPIUM COLLECTED: " << score;
    if (score < 10) cout << "                      I\n";
    else if (score < 100) cout << "                     I\n";
    else cout << "                    I\n";
    setColor(11);
    cout << "I----------------------------------------------------------------I\n";
    setColor(14);
    cout << "I     He didn't fail the semester - the semester failed him.     I\n";
    setColor(11);
    cout << "==================================================================\n";
    setColor(7);

    cout << "\nEnter name for leaderboard: ";
    string name;
    getline(cin, name);
    if (name.empty()) name = "Anonymous";
    if (name.size() > 18) name = name.substr(0, 18);

    LBEntry e{ name, score, hopiumMeter };
    writeLeaderboardAndShow(e);

    // Simple menu actions (Play again, Clear leaderboard, Main menu)
    gotoxy(3, 16);
    setColor(10);  cout << " [SPACE] "; setColor(7); cout << "Play Again   ";
    setColor(12);  cout << " [C] ";    setColor(7); cout << "Clear Leaderboard   ";
    setColor(11);  cout << " [M] ";    setColor(7); cout << "Main Menu\n\n";

menu:
    char c = _getch();
    if (c == ' ') { playGame(); return; } // play again immediately
    if (c == 'M' || c == 'n') return;
    if (c == 'C' || c == 'c') {
        setColor(12);
        cout << "\nAre you sure you want to clear the leaderboard? (Y/N): ";
        char confirm = _getch();
        if (confirm == 'y' || confirm == 'Y') {
            ofstream clearFile("leaderboard.txt", ios::trunc);
            if (clearFile.is_open()) {
                clearFile.close();
                setColor(10);
                cout << "\n\nLeaderboard cleared successfully!\n";
            }
            else {
                setColor(12);
                cout << "\n\nError: Unable to clear leaderboard file.\n";
            }
        }
        else {
            setColor(7);
            cout << "\n\nOperation cancelled. Leaderboard unchanged.\n";
        }
        goto menu;
    }
}

void playGame() {
    hidecursor();
    system("cls");

    setColor(14);
    cout << "\nBooting \"Aal Iz Well - Tale of Seecs\" simulator...\n";
    Sleep(700);
    cout << "Connecting to campus network... (Failed)\n";
    Sleep(700);
    cout << "Summoning enemies: LABS, TESTS, BUGS...\n";
    Sleep(700);
    cout << "Loading Hopium reserves...\n";
    Sleep(700);
    cout << "\nPress SPACE to inhale Hopium and begin your journey.\n";
    setColor(7);

    while (_getch() != ' ') {}

    system("cls");
    borders();

    // Player
    const string p1 = "    A";
    const string p2 = "  SEECS";
    const string p3 = " STUDENT";

    // Initial positions
    int px = 30, py = 25;
    int ex = ENEMY_MIN_X, ey = ENEMY_START_Y;         // enemy pos
    int bx = -1, by = -1;                             // player bullet
    int ebx = -1, eby = -1;                           // enemy bullet
    int score = 0;
    int hp = MAX_HP, maxhp = MAX_HP;
    int frame = 0;

    int kx = -1, ky = -1;                             // KHAPPA pickup pos
    int khappaTimer = 0;

    int hopiumMeter = MAX_HOPIUM;                     // current hopium level

    // Precompute integer hopium increments

    const int hopiumDrainPerTick = max(1, percentOf(MAX_HOPIUM, HOPIUM_DRAIN_PERCENT_PER_TICK));
    const int killHopiumInc = max(1, percentOf(MAX_HOPIUM, HOPIUM_KILL_GAIN_PERCENT));
    const int khappaHopiumInc = max(1, percentOf(MAX_HOPIUM, HOPIUM_KHAPPA_GAIN_PERCENT));
    const int pressSpaceInc = max(1, percentOf(MAX_HOPIUM, HOPIUM_PRESS_SPACE_GAIN_PERCENT));


    string dushman = "LABS!";
    string e1 = " <***> ";
    string e2 = "<" + dushman + "> ";
    string e3 = " <***> ";

    // Draw the player and scoreboard
    drawPlayer(px, py, p1, p2, p3, 10);
    scoreBoard(score, hp, maxhp, hopiumMeter);

    // --- MAIN GAME LOOP ---
    while (true) {
        // Periodic hopium drain
        if (frame % 10 == 0) {
            hopiumMeter -= hopiumDrainPerTick;
            if (hopiumMeter < 0) hopiumMeter = 0;
            scoreBoard(score, hp, maxhp, hopiumMeter);
        }

        // Compute hopium percent once per frame
        int hopiumPercent = (hopiumMeter * 100) / MAX_HOPIUM;
        bool randomTeleport = (hopiumPercent <= THRESH_TELEPORT_PERCENT);
        bool enemyAggro = (hopiumPercent <= THRESH_AGGRO_PERCENT);
        bool misfireBullets = (hopiumPercent <= THRESH_MISFIRE_PERCENT);

        // INPUT
        if (_kbhit()) {
            int k = _getch();
            if (k == 0 || k == 224) k = _getch(); // extended keys come in as two codes

            if (!(hopiumPercent <= 10 && (rand() % 100) < 15)) {
                // LEFT arrow
                if (k == 75 && px > PLAYER_LEFT_LIMIT) {
                    clearSprite(px, py);
                    px -= PLAYER_STEP;
                }
                // RIGHT arrow
                if (k == 77 && px < PLAYER_RIGHT_LIMIT) {
                    clearSprite(px, py);
                    px += PLAYER_STEP;
                }
                // SPACE: small hopium regain
                if (k == ' ' && hopiumMeter < MAX_HOPIUM) {
                    hopiumMeter += pressSpaceInc;
                    if (hopiumMeter > MAX_HOPIUM) hopiumMeter = MAX_HOPIUM;
                    scoreBoard(score, hp, maxhp, hopiumMeter);
                }
            }

            // When extremely drained, occasionally teleport the player
            if (randomTeleport && (rand() % 100) < 8) {
                clearSprite(px, py);
                px = rand() % ENEMY_X_RANGE + ENEMY_MIN_X;
            }

            // Re-draw player after movement
            drawPlayer(px, py, p1, p2, p3, 10);
        }

        // Fire
        if (by == -1) { bx = px + 4; by = py - 1; }

        // Move player's bullet
        if (by != -1) {
            gotoxy(bx, by); cout << " ";
            bool misfired = (misfireBullets && (rand() % 100) < 12);
            if (!misfired) by -= 2;
            if (!misfired) {
                if (by <= 1) by = -1;
                else { setColor(14); gotoxy(bx, by); cout << "^"; setColor(7); }
            }
        }

        // ENEMY MOVEMENT
        if (frame % (enemyAggro ? 4 : 6) == 0) {
            clearSprite(ex, ey);
            ey++;
            if (ey > ENEMY_DEATH_Y) { gameOver(score, hopiumMeter); return; }
        }

        // Draw the enemy
        drawEnemyStrings(ex, ey, e1, e2, e3, 12);

        // Enemy fires bullets
        if (frame % (enemyAggro ? 10 : 15) == 0 && eby == -1) {
            ebx = ex + 3;
            eby = ey + 3;
        }

        // Move enemy bullet
        if (eby != -1 && frame % 2 == 0) {
            gotoxy(ebx, eby); cout << " ";
            eby++;
            if (eby >= 28) eby = -1;
            else { setColor(12); gotoxy(ebx, eby); cout << "v"; setColor(7); }
        }

        // COLLISIONS: player bullet vs enemy
        if (by != -1 &&
            bx >= ex && bx <= ex + 6 &&
            by >= ey && by <= ey + 2) {
            // kill enemy: clear old, respawn new enemy, award hopium and score
            clearSprite(ex, ey);
            ex = rand() % ENEMY_X_RANGE + ENEMY_MIN_X;
            ey = ENEMY_START_Y;
            by = -1;

            // pick new enemy name and update middle line once
            dushman = dushmans[rand() % DUSHMANS_COUNT];
            e2 = "<" + dushman + "> ";
            ++score;

            hopiumMeter += killHopiumInc;
            if (hopiumMeter > MAX_HOPIUM) hopiumMeter = MAX_HOPIUM;
            scoreBoard(score, hp, maxhp, hopiumMeter);
        }

        // COLLISIONS: enemy bullet vs player
        if (eby != -1 &&
            ebx >= px && ebx <= px + 8 &&
            eby >= py && eby <= py + 2) {
            eby = -1;
            --hp;
            scoreBoard(score, hp, maxhp, hopiumMeter);
            if (hp <= 0) { gameOver(score, hopiumMeter); return; }
        }

        // KHAPPA
        if (khappaTimer == 0 && rand() % KHAPPA_SPAWN_CHANCE_DIV == 0) {
            kx = rand() % ENEMY_X_RANGE + ENEMY_MIN_X;
            ky = 2;
            khappaTimer = KHAPPA_TIMER_RESET;
        }

        if (kx != -1) {
            gotoxy(kx, ky - 1); cout << "          "; // clear previous line
            int pulse = frame % 6;
            int color = (pulse < 3) ? 10 : (pulse < 5 ? 14 : 11);
            printUnicode(kx, ky, L"★ KHAPPA ★", color);
            ky++;
            if (ky >= py && kx >= px && kx <= px + 8) {
                if (hp < maxhp) ++hp;
                scoreBoard(score, hp, maxhp, hopiumMeter);
                gotoxy(kx, ky - 1); cout << "          ";

                // Short chat message when KHAPPA picked
                gotoxy(70, 8 + chatLine);
                setColor(10); cout << "  KHAPPA consumed!  "; setColor(7);
                chatLine++;
                hopiumMeter += khappaHopiumInc;
                if (hopiumMeter > MAX_HOPIUM) hopiumMeter = MAX_HOPIUM;
                kx = -1;
            }
            if (ky >= 28) {
                gotoxy(kx, ky - 1); cout << "          ";
                kx = -1;
            }
        }
        if (khappaTimer > 0) --khappaTimer;

        // Chat updates
        if (frame % ((hopiumPercent < 20) ? 40 : 100) == 0) randomChatMessage();

        // If hopium hits zero there are random bad events
        if (hopiumMeter <= 0) {
            if ((rand() % 100) < 6) {
                gotoxy(70, 5);
                setColor(12);
                cout << "Hopium depleted. Panic strike!      ";
                setColor(7);
                --hp;
                scoreBoard(score, hp, maxhp, hopiumMeter);
                if (hp <= 0) { gameOver(score, hopiumMeter); return; }
            }
            if ((rand() % 1000) < 8) {
                gotoxy(70, 5);
                setColor(12);
                cout << "System collapse. You died of despair.";
                setColor(7);
                Sleep(700);
                gameOver(score, hopiumMeter);
                return;
            }
        }

        ++frame;
        Sleep(FRAME_SLEEP_MS);
    } // end main loop
}