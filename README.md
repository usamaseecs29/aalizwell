
# Aal Iz Well - Tale of Seecs

A small Windows console game. This repository contains the game source, helper scripts and a CMakeLists configured for Windows builds.

This README covers:
- Quick start (Windows)
- Build options (MSVC, MinGW/CMake)
- Using provided scripts
- Troubleshooting & tips
- How to re-enable a cross-platform (curses) backend

---

## Requirements (Windows)

- Windows 10 / 11
- One of:
  - Visual Studio 2019/2022 with "Desktop development with C++" workload (recommended), OR
  - MSVC Build Tools, OR
  - MinGW/MSYS2 (for g++) if you prefer MinGW builds (see notes)
- CMake 3.15+
- Console font that supports Unicode (Consolas / Lucida Console recommended)

Note: The CMakeLists in this repository is configured to be Windows-only (checks `WIN32`). If you want cross-platform builds, see the "Curses backend" section below.

---

## Quick start (Developer Command Prompt — recommended)

1. Open "Developer Command Prompt for VS" (this sets up `cl.exe` on PATH).
2. From the repo root, run:
   - For debug:
     ```
     build_and_play.bat debug
     ```
   - For release:
     ```
     build_and_play.bat release
     ```
   - To launch the game in a new console window that stays open after exit:
     ```
     build_and_play.bat release newconsole
     ```

The script will compile and run the game, and keep the console open so you can read errors or logs.

---

## Using CMake + Visual Studio generator (manual flow)

If you prefer to use CMake directly:

1. Create a build directory:
   ```
   mkdir build
   cd build
   ```
2. Configure CMake for Visual Studio (example for VS 2022 x64):
   ```
   cmake -G "Visual Studio 17 2022" -A x64 ..
   ```
   For a 32-bit Win32 target:
   ```
   cmake -G "Visual Studio 17 2022" -A Win32 ..
   ```
3. Build with CMake:
   ```
   cmake --build . --config Release
   ```
4. Run the produced executable (e.g., `build\Release\aalizwell.exe`), or use the `run` target:
   ```
   cmake --build . --config Release --target run
   ```

Note: This CMake config intentionally aborts on non-Windows platforms (it checks WIN32 early).

---

## Controls & Gameplay (short)

- Main menu keys:
  - 1 — Start Grind
  - 2 — Survival Guide
  - 3 — Credits
  - 4 — Quit Life
- In-game:
  - Left / Right arrow — move
  - Auto-fire — the player autofires bullets
  - Space — inhale Hopium (small boost)
- Objective: Survive, kill enemies, collect KHAPPA pickups, manage Hopium & HP.

---

## Files of interest

- `src/console.cpp` — Win32 console backend (uses <windows.h>)
- `src/console_pdcurses.cpp` — optional curses backend (if you re-enable it later)
- `CMakeLists.txt` — project configuration (Windows-only by default)
- 
---

## License

This project is provided under the MIT License. See `LICENSE` for details.

---

Thanks
