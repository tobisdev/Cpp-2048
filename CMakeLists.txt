cmake_minimum_required(VERSION 3.26)
project(2048)

set(CMAKE_CXX_STANDARD 17)

# Use FetchContent to download SFML at configure time
include(FetchContent)

# Set up SFML FetchContent
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1  # The version of SFML you want to use, here 2.6.1
)

# Make SFML available
FetchContent_MakeAvailable(SFML)

# Glob all .cpp and .h files in src directory
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# Add the source files to your project
add_executable(2048 ${SOURCES}
        src/Grid/Grid.cpp
        src/Grid/Grid.h
        src/Grid/Tile/Tile.cpp
        src/Grid/Tile/Tile.h
        src/Game/Gamestate/Gamestate.cpp
        src/Game/Gamestate/Gamestate.h
        src/Game/Gamestate/Singleplayer.cpp
        src/Game/Gamestate/Singleplayer.h
        src/Game/Gamestate/AImode.cpp
        src/Game/Gamestate/AImode.h)

# Link SFML libraries
target_link_libraries(2048 PUBLIC sfml-system sfml-window sfml-graphics)

# Path to the folder where additional DLLs are stored
set(ADDITIONAL_DLL_PATH "path/to/dlls")  # Modify this to the correct path

# Copy SFML DLLs to the output directory
add_custom_command(TARGET 2048 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:2048> $<TARGET_FILE_DIR:2048>
        COMMAND_EXPAND_LISTS)

# Find MinGW libraries if applicable
if (MINGW)

    # Extract the directory where the g++ (MinGW) compiler resides
    get_filename_component(MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

    add_custom_command(TARGET 2048 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MINGW_BIN_DIR}/libstdc++-6.dll"
            "${MINGW_BIN_DIR}/libgcc_s_seh-1.dll"
            "${MINGW_BIN_DIR}/libwinpthread-1.dll"
            $<TARGET_FILE_DIR:2048>)
endif()