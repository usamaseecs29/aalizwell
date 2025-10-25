cmake_minimum_required(VERSION 3.15)
project("Aal Iz Well - Tale of Seecs" VERSION 1.0 LANGUAGES CXX)

# Single place for source files - keep in sync with repo layout.
set(SRC_FILES
    src/main.cpp
    src/game.cpp
    src/console.cpp
    src/functions.cpp
)

# Public include dir
include_directories(${PROJECT_SOURCE_DIR}/include)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to Release for single-config generators if not set
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

# Create executable (use a short target name)
add_executable(aalizwell ${SRC_FILES})

# Preprocessor defines
target_compile_definitions(aalizwell PRIVATE _CRT_SECURE_NO_WARNINGS UNICODE _UNICODE NOMINMAX)

# Platform / compiler specific flags
if(MSVC)
  # Use sensible warning level, enable C++ exceptions model and set UTF-8 source encoding where supported
  target_compile_options(aalizwell PRIVATE /W3 /EHsc /utf-8)
else()
  target_compile_options(aalizwell PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Ensure the include dir is an interface include for other targets (if any)
target_include_directories(aalizwell PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Make a convenient 'run' target: builds aalizwell then runs it.
add_custom_target(run
    COMMAND $<TARGET_FILE:aalizwell>
    DEPENDS aalizwell
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building and running Aal Iz Well - Tale of Seecs"
)

# Install rule (optional)
install(TARGETS aalizwell RUNTIME DESTINATION bin)

# Helpful messages
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Sources: ${SRC_FILES}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")