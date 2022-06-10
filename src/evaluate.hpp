#pragma once
#include <iostream>
#include "board.hpp"

using namespace std;

#define MID_SCORE_MAX INF
#define END_SCORE_MAX HW2

#define MID_END_WEIGHT 1000

// from https://uguisu.skr.jp/othello/5-1.html
#define N_WEIGHT 6
constexpr int cell_weight_score[N_WEIGHT] = {30, -12, 0, -1, -3, -15};
constexpr uint64_t cell_weight_mask[N_WEIGHT] = {
    0b10000001'00000000'00000000'00000000'00000000'00000000'00000000'10000001ULL,
    0b01000010'10000001'00000000'00000000'00000000'00000000'10000001'01000010ULL,
    0b00100100'00000000'10100101'00000000'00000000'10100101'00000000'00100100ULL,
    0b00011000'00000000'00011000'10111101'10111101'00011000'00000000'00011000ULL,
    0b00000000'00111100'01000010'01000010'01000010'01000010'00111100'00000000ULL,
    0b00000000'01000010'00000000'00000000'00000000'00000000'01000010'00000000ULL
};

inline int evaluate_one_player(uint64_t player){
    int res = 0;
    for (int i = 0; i < N_WEIGHT; ++i)
        res += cell_weight_score[i] * pop_count_ull(player & cell_weight_mask[i]);
    return res;
}

inline int evaluate(Board *board){
    return evaluate_one_player(board->player) - evaluate_one_player(board->opponent);
}