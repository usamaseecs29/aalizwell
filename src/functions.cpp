// src/functions.cpp
// Helper implementations: small math helpers, chat, scoreboard, leaderboard.
// Project: Aal Iz Well - Tale of Seecs

#include "functions.h"
#include "console.h"
#include "constants.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include <io.h>
#include <fcntl.h>

using namespace std;

// HELPERS
int clampInt(int v, int lo, int hi) { return (v < lo) ? lo : (v > hi) ? hi : v; }
int percentOf(int value, int percent) { return (value * percent) / 100; }
int randRange(int lo, int hi) { return rand() % (hi - lo + 1) + lo; }

// MESSAGES

const vector<string> non_formals = {
    "Bro, that was straight chaos.", "Dude, your code needs CPR.", "That bug's a legend now.",
    "Sleep? What's that again?", "Bro, did you code blindfolded?", "Your code's a total mess.",
    "Bro, panic is your fuel.", "That fail hit different.", "Code's crying, help it out.",
    "Bro, even bugs run scared.", "You crashed harder than me.", "Bro, your logic took a hike.",
    "Error 404: Skills not found.", "Bro, your laptop gave up.", "That bug is personal now.",
    "Bro, your code's a drama.", "Sleep? Only myths remain.", "Bro, you ghosted the bug.",
    "Code broke. You're broken.", "Bro, panic is your friend.", "That miss was epic, bro.",
    "Bro, your code's on fire.", "Crash and burn again, bro.", "Bro, coding's not guessing.",
    "Bro, your bugs breed fast.", "Try harder or just quit.", "Bro, that fail was classic.",
    "Bro, chaos is your style.", "Code screams. Bro, listen.", "Bro, hope's on backorder.",
    "Bro, code's a disaster.", "That bug's a beast, bro.", "Bro, your logic vanished.",
    "Code's crying, fix it.", "Bro, sleep is for winners.", "That fail hit like a truck.",
    "Bro, your code's a meme.", "Panic mode: always on.", "Bro, you broke the code.",
    "That bug's stalking you.", "Bro, try not to break it.", "Code's screaming internally.",
    "Bro, that miss was brutal.", "Bugged out? Welcome to club.", "Bro, panic is your default.",
    "Your code needs CPR, bro.", "Bro, bugs found a home.", "That fail was pure art.",
    "Bro, logic fled the scene.", "Code crashed; so did you.", "Bro, bugs multiply fast.",
    "Sleep? Not in your world.", "Bro, crash and burn much?", "Code's chaos on steroids.",
    "Bro, logic called a timeout.", "Bug parade in your code.", "Bro, keep crashing hard.",
    "Code's crying for help.", "Bro, you lag in class.", "Bug count: out of control."
};

const vector<string> formals = {
    "Submission received. Noted.", "Please review rubric details.", "Errors found; review again.",
    "Performance below standard.", "Late submission accepted.", "Consider tutoring sessions.",
    "Logic requires refinement.", "Please read instructions.", "Grades posted. Check now.",
    "Consistency in errors noted.", "Attendance recorded; noted.", "Respect deadlines, please.",
    "Code compiles; needs work.", "Academic integrity matters.", "Improvement is encouraged.",
    "Attempt logged; improve.", "Collaboration must be honest.", "Tutor consultation advised.",
    "Effort appreciated; redo.", "Debug before resubmitting.", "Submission ineffective.",
    "Redefine success criteria.", "Syllabus expectations unmet.", "Late work accepted carefully.",
    "Please avoid repeated errors.", "Extensions are rare.", "Aim to improve quality.",
    "Plagiarism is monitored.", "Submit full answers.", "Grades reflect understanding.",
    "Submission noted; improve.", "Review rubric carefully.", "Errors need correction.",
    "Performance below par.", "Late work accepted once.", "Seek tutoring assistance.",
    "Logic needs polishing.", "Follow instructions next.", "Grades are available now.",
    "Error frequency concerning.", "Attendance was noted.", "Respect deadlines strictly.",
    "Code compiles; needs fix.", "Maintain academic honesty.", "Effort is appreciated.",
    "Attempt recorded; revise.", "Collaborate honestly only.", "Consult tutors regularly.",
    "Resubmit with corrections.", "Debug thoroughly first.", "Work lacks effectiveness.",
    "Redefine your approach.", "Meet syllabus standards.", "Late submissions limited.",
    "Avoid repeat mistakes.", "Extensions granted rarely.", "Strive for better quality.",
    "Plagiarism checks ongoing.", "Submit complete answers.", "Grades reflect mastery."
};

const vector<string> dushmans = {
    "LABS!", "SLEEP", "GRADE", "FAILS", "MIDS!", "TESTS", "CGPA!", "QUIZ!", "FEES!", "CODES", "BUGS!"
};

const vector<string> chatNames = {
    "Professor","Dean","HOD","Lab Instructor","Rector",
    "Classmate","Senior","GPA","Anonymous","Deadline","Assignment"
};

const size_t NON_FORMALS_COUNT = non_formals.size();
const size_t FORMALS_COUNT = formals.size();
const size_t DUSHMANS_COUNT = dushmans.size();
const size_t CHAT_NAMES_COUNT = chatNames.size();
const char* LEADERBOARD_FILE = "leaderboard.txt";
int chatLine = 0;

// UI / LEADERBOARD
void clearChatArea() {
    for (int i = 0; i < CHAT_LINES; ++i) {
        gotoxy(70, 8 + i);
        cout << "                                          ";
    }
    chatLine = 0;
}

void scoreBoard(int score, int hp, int maxhp, int hopiumMeter) {
    const int meterWidth = METER_WIDTH;
    int hopiumFill = (hopiumMeter * meterWidth) / MAX_HOPIUM;
    hopiumFill = clampInt(hopiumFill, 0, meterWidth);

    int hopiumPercent = (hopiumMeter * 100) / MAX_HOPIUM;

    setColor(10);
    gotoxy(70, 2); cout << "Score: " << setw(3) << score;
    gotoxy(70, 3); cout << "----------------------";
    gotoxy(70, 4);
    setColor(14);
    cout << "Hopium: ";
    setColor(9);
    _setmode(_fileno(stdout), _O_U16TEXT);
    for (int i = 0; i < meterWidth; ++i) wcout << (i < hopiumFill ? L"♦ " : L"  ");
    _setmode(_fileno(stdout), _O_TEXT);
    setColor(14);
    cout << setw(2) << hopiumMeter << "/" << MAX_HOPIUM << " (" << setw(3) << hopiumPercent << "%)";

    // hearts
    gotoxy(70, 6);
    setColor(14);
    cout << "Will to Live: ";
    int bars = (hp * 5) / maxhp;
    setColor(12);
    _setmode(_fileno(stdout), _O_U16TEXT);
    for (int i = 0; i < 5; ++i) wcout << (i < bars ? L"♥ " : L"  ");
    _setmode(_fileno(stdout), _O_TEXT);
    setColor(14);
    cout << hp << "/" << maxhp;
    setColor(7);
}

void appendLeaderboardRaw(const LBEntry& e) {
    ofstream ofs(LEADERBOARD_FILE, ios::app);
    if (ofs) ofs << e.name << "," << e.score << "," << e.hopium << "\n";
    ofs.close();
}

void writeLeaderboardAndShow(const LBEntry& e) {
    appendLeaderboardRaw(e);

    vector<LBEntry> v;
    ifstream ifs(LEADERBOARD_FILE);
    string line;
    while (getline(ifs, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string name, sc, hp;
        if (!getline(ss, name, ',')) continue;
        if (!getline(ss, sc, ',')) continue;
        if (!getline(ss, hp, ',')) continue;
        LBEntry tmp; tmp.name = name; tmp.score = stoi(sc); tmp.hopium = stoi(hp);
        v.push_back(tmp);
    }
    ifs.close();

    sort(v.begin(), v.end(), [](const LBEntry& a, const LBEntry& b) {
        if (a.score != b.score) return a.score > b.score;
        return a.hopium > b.hopium;
    });

    // Show top 5
    setColor(11);
    gotoxy(70, 2);
    cout << "================== LEADERBOARD ==================\n";
    setColor(15);
    gotoxy(70, 3);
    cout << " Rank  Name                Score  Hopium\n";
    gotoxy(70, 4);
    cout << " ---------------------------------------------\n";
    for (size_t i = 0; i < min<size_t>(5, v.size()); ++i) {
        gotoxy(70, 5 + (int)i);
        cout << "  " << setw(2) << (int)(i + 1) << "   ";
        cout << left << setw(18) << v[i].name << "  ";
        cout << right << setw(5) << v[i].score << "   ";
        int hp = v[i].hopium;
        int percent = (hp * 100) / MAX_HOPIUM;
        cout << setw(2) << hp << "/" << MAX_HOPIUM << " (" << setw(3) << percent << "%)\n";
    }
    gotoxy(70, 15);
    setColor(7);
}

// CHAT BOX
void randomChatMessage() {
    if (chatLine >= CHAT_LINES) clearChatArea();

    int idx = rand() % (int)CHAT_NAMES_COUNT;
    string name = chatNames[idx];
    string msg;
    // choose whether to use a "formal" or "informal" message
    if (idx < 5) msg = formals[rand() % FORMALS_COUNT];
    else msg = non_formals[rand() % NON_FORMALS_COUNT];

    gotoxy(70, 8 + chatLine);
    setColor(14);
    cout << name << ": ";
    setColor(7);

    // Print the message in one go (no per-character sleep).
    cout << msg << "\n";
    chatLine++;
}