project(DeckLib)

add_library(DeckLib
src/Card.cpp src/Deck.cpp src/Hand.cpp src/Suit.cpp)

target_include_directories(DeckLib PUBLIC include)
target_link_directories(DeckLib PRIVATE PlayerLib)