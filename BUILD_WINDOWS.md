```markdown
# BUILD (Windows) — step-by-step

This guide shows exact commands to build with Visual Studio / CMake and how to use the helper batch files.

Prerequisites
- Visual Studio 2019/2022 with "Desktop development with C++", or Visual Studio Build Tools.
- CMake 3.15+
- Optional: MSYS2/MinGW if you want to attempt non-MSVC builds.

Using the helper batch (recommended for quick iteration)
- From a Developer Command Prompt:
  - Debug:
    ```
    build_and_play.bat debug
    ```
  - Release:
    ```
    build_and_play.bat release
    ```
  - New console (keeps window open):
    ```
    build_and_play.bat release newconsole
    ```

Manual (CMake + Visual Studio generator)
1. Create a build directory:
   ```
   mkdir build
   cd build
   ```
2. Configure (VS 2022 x64 example):
   ```
   cmake -G "Visual Studio 17 2022" -A x64 ..
   ```
3. Build:
   ```
   cmake --build . --config Release
   ```
4. Run:
   ```
   cmake --build . --config Release --target run
   ```
   or run the executable at `build\Release\aalizwell.exe`.

```