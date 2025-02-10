#pragma once
enum action {
    HIT=0,
    STAND=1,
    DOUBLE_HIT=2,
    DOUBLE_STAND=3,
    SPLIT=4,
};

enum strategies {
    HIT_16=0,
    HIT_17=1,
    HIT_18=2,
    LET_DEALER_BUST=3,
    COUNT=4,
    PERFECT_BASIC_HARD=5,
    PERFECT_BASIC=6,
};