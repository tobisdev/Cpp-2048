cmake_minimum_required(VERSION 3.26)
project(2048)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
set(SFML_DIR "SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

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
        src/Game/Gamestate/AImode.h
        src/Game/Gamestate/Menu.cpp
        src/Game/Gamestate/Menu.h)

# Link SFML libraries
target_link_libraries(2048 PUBLIC sfml-system sfml-window sfml-graphics)

# Copy SFML DLLs to the output directory
set(SFML_DLLS "${SFML_DIR}/../../../bin")
file(GLOB SFML_DLL_FILES "${SFML_DLLS}/*.dll")
foreach(DLL ${SFML_DLL_FILES})
    add_custom_command(TARGET 2048 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL}" $<TARGET_FILE_DIR:2048>)
endforeach()