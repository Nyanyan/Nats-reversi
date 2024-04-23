#pragma once
#include <iostream>
#include "board.hpp"

using namespace std;

#define SCORE_MAX HW2

#define MID_END_WEIGHT 1000

// This evaluation weight was created by Takuto Yamana (Nyanyan)
// The evaluation value is fit by 256 * final score.
#define N_WEIGHT 10
constexpr int cell_weight_score[N_WEIGHT] = {
    2714,  147,   69,  -18,
          -577, -186, -153,
                -379, -122,
                      -169
};
constexpr uint64_t cell_weight_mask[N_WEIGHT] = {
    0x8100000000000081ULL,
    0x4281000000008142ULL,
    0x2400810000810024ULL,
    0x1800008181000018ULL,
    0x0042000000004200ULL,
    0x0024420000422400ULL,
    0x0018004242001800ULL,
    0x0000240000240000ULL,
    0x0000182424180000ULL,
    0x0000001818000000ULL
};

inline int evaluate_one_player(uint64_t player){
    int res = 0;
    for (int i = 0; i < N_WEIGHT; ++i)
        res += cell_weight_score[i] * pop_count_ull(player & cell_weight_mask[i]);
    return res;
}

inline int evaluate(Board *board){
    int value = evaluate_one_player(board->player) - evaluate_one_player(board->opponent);
    value += value >= 0 ? 128 : -128;
    value /= 256;
    if (value > SCORE_MAX)
        value = SCORE_MAX;
    else if (value < -SCORE_MAX)
        value = -SCORE_MAX;
    return value;
}