// src/main.cpp
// Entry point and main menu for "Aal Iz Well - Tale of Seecs"
// Build (MSVC): cl /EHsc src\main.cpp src\game.cpp src\console.cpp src\functions.cpp

#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;


#include "game.h"
#include "console.h"

int main() {
    // Seed
    srand(static_cast<unsigned int>(time(0)));

    // Keep showing main menu
    while (1) {
        system("cls");

        setColor(11);
        cout << "=================================================================\n";
        cout << "I                                                               I\n";
        cout << "I            _    _   _     _  ___   _ _ _  ___  _    _         I\n";
        cout << "I           / \\  / \\ | |   | ||_ /  | | | || __|| |  | |        I\n";
        cout << "I          | o || o || |_  | | /(_  | V V || _| | |_ | |_       I\n";
        cout << "I          |_n_||_n_||___| |_|/___|  \\_n_/ |___||___||___|      I\n";
        cout << "I                                                               I\n";
        setColor(14);
        cout << "I            Aal Iz Well - Tale of Seecs                        I\n";
        cout << "I          Commander, you are the last hope of your batch.      I\n";
        cout << "I                                                               I\n";
        setColor(11);
        cout << "I---------------------------------------------------------------I\n";
        setColor(15);
        cout << "I                        MAIN MENU                              I\n";
        cout << "I                                                               I\n";
        setColor(10);
        cout << "I                     1.  Start Grind                           I\n";
        setColor(14);
        cout << "I                     2.  Survival Guide                        I\n";
        setColor(9);
        cout << "I                     3.  Credits                               I\n";
        setColor(12);
        cout << "I                     4.  Quit Life                             I\n";
        setColor(11);
        cout << "I                                                               I\n";
        cout << "I---------------------------------------------------------------I\n";
        setColor(10);
        cout << "I          Tip: Hopium restores sanity faster than sleep.       I\n";
        setColor(14);
        cout << "I                                                               I\n";
        cout << "I        Press a number key to delay your breakdown...          I\n";
        setColor(11);
        cout << "=================================================================\n";

        char choice = _getch();

        if (choice == '1') {
            system("cls");
            setColor(14);
            cout << "\nCompiling code...\n"; Sleep(600);
            cout << "Running debugger...\n"; Sleep(600);
            setColor(12);
            cout << "Oh no... segmentation fault. Nevermind, launching anyway... \n"; Sleep(800);
            setColor(7);
            playGame();
        }
        else if (choice == '2') {
            system("cls");
            setColor(14);
            cout << "==================================================================\n";
            cout << "I                    S E E C S   S U R V I V A L                 I\n";
            cout << "I                         P R O T O C O L                        I\n";
            cout << "I----------------------------------------------------------------I\n";
            setColor(10);
            cout << "I  STATUS: Campus infected with LABS, TESTS & QUIZS sightings.   I\n";
            cout << "I  OBJECTIVE: Survive the semester. Optional: Pass.              I\n";
            setColor(14);
            cout << "I----------------------------------------------------------------I\n";
            cout << "I  * ARROW KEYS  : Dodge everything - E.g. guilt, and bullets.   I\n";
            cout << "I  * AUTO-FIRE   : Shoot before they do. Mercy is deprecated.    I\n";
            cout << "I  * DAMAGE      : Every hit drains your Will to Live.           I\n";
            cout << "I  * HOPIUM GAIN : Press SPACE, Eat Khappa, Make a hit           I\n";
            cout << "I                                                                I\n";
            setColor(12);
            cout << "I  * When morale hits zero - your CGPA follows.                  I\n";
            setColor(14);
            cout << "I----------------------------------------------------------------I\n";
            cout << "I  REMINDER: You can't debug life. Only delay the crash.         I\n";
            cout << "==================================================================\n";
            setColor(7);
            while (_getch() != ' ');
        }
        else if (choice == '3') {
            system("cls");
            setColor(11);
            cout << "==================================================================\n";
            cout << "             A A L   I Z   W E L L   -   O R I G I N S            \n";
            cout << "==================================================================\n";
            setColor(7);
            cout << "                                                                  \n";
            cout << "   A student, armed with nothing but caffeine and delusion,       \n";
            cout << "   stood against the mighty enemies: GPA, QUIZZES, and EXAMS.     \n";
            cout << "   He did not win... but he compiled.                             \n";
            cout << "                                                                  \n";
            setColor(11);
            cout << "------------------------------------------------------------------\n";
            setColor(15);
            cout << "   C R E D I T S                                                  \n";
            setColor(11);
            cout << "------------------------------------------------------------------\n";
            setColor(10);
            cout << "   Developer       :  Usama Gulzar                                \n";
            cout << "                      CS @ SEECS | NUST '29                       \n";
            cout << "   Contact         :  usamaseecs29@gmail.com                      \n";
            setColor(11);
            cout << "------------------------------------------------------------------\n";
            setColor(14);
            cout << "   \"Not every bug gets fixed.                                    \n";
            cout << "    You just learn to live with them.\"                           \n";
            setColor(11);
            cout << "------------------------------------------------------------------\n";
            setColor(7);
            cout << "   Thank you for entering the codebase of chaos.                  \n";
            cout << "   Remember: Hopium is temporary. Regret is permanent.            \n";
            setColor(11);
            cout << "==================================================================\n";
            setColor(14);
            cout << "\nPress SPACE to return to the battlefield...\n";
            setColor(7);
            while (_getch() != ' ');
        }
        else if (choice == '4') {
            system("cls");
            setColor(12);
            cout << "\nShutting down simulator...\n"; Sleep(600);
            cout << "Saving unfinished assignments...\n"; Sleep(600);
            cout << "Logging out from NUST servers...\n"; Sleep(600);
            cout << "Goodbye, Warrior, Aal Iz Well.\n"; Sleep(1000);
            setColor(7);
            return 0;
        }
        else {
            system("cls");
            setColor(12);
            cout << "\nInvalid command. Even CMD feels your confusion.\n";
            Sleep(900);
            setColor(7);
        }
    }

    return 0;
}