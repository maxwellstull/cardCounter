project(DeckLib)

add_library(PlayerLib
src/Counter.cpp src/Dealer.cpp src/Player.cpp)

target_include_directories(PlayerLib PUBLIC include)
target_link_libraries(PlayerLib PRIVATE DeckLib)