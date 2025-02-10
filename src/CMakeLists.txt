add_library(Game
Game.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Game PRIVATE PlayerLib DeckLib)