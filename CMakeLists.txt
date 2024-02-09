cmake_minimum_required(VERSION 3.27)
project(game)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
)

FetchContent_MakeAvailable(SFML)

add_executable(game main.cpp
        src/server.cpp
        src/server.cpp
        src/server.h
        src/settings.h
        src/client.cpp
        src/client.h
        src/game/world.cpp
        src/game/world.h
        src/game/player.cpp
        src/game/player.h)

target_link_libraries(game PRIVATE sfml-network sfml-graphics)