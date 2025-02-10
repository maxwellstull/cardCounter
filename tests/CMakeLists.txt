add_executable(McTest test_card.cpp test_suit.cpp)

target_link_libraries(McTest PRIVATE gtest gtest_main DeckLib PlayerLib Game)