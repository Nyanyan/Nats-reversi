#pragma once
#include <iostream>
#include "search.hpp"

using namespace std;

#define POLICY_UNDEFINED -1
#define SCORE_UNDEFINED -INF

struct Search_result{
    int policy;
    int value;
};

Search_result ai_mid(Board board, int depth){
    Search_result res;
    uint64_t legal = board.get_legal();
    if (legal == 0ULL){
        res.policy = POLICY_UNDEFINED;
        res.value = SCORE_UNDEFINED;
        return res;
    }
    int alpha = -MID_SCORE_MAX, beta = MID_SCORE_MAX, g;
    Flip flip;
    for (uint_fast8_t cell = first_bit(&legal); legal; cell = next_bit(&legal)){
        calc_flip(&flip, &board, cell);
        board.move(&flip);
            g = -nega_alpha_mid(&board, -beta, -alpha, depth - 1, false);
        board.undo(&flip);
        if (alpha < g){
            alpha = g;
            res.value = g;
            res.policy = cell;
        }
    }
    return res;
}

Search_result ai_end(Board board){
    Search_result res;
    uint64_t legal = board.get_legal();
    if (legal == 0ULL){
        res.policy = POLICY_UNDEFINED;
        res.value = SCORE_UNDEFINED;
        return res;
    }
    int alpha = -END_SCORE_MAX - 1, beta = END_SCORE_MAX, g;
    Flip flip;
    for (uint_fast8_t cell = first_bit(&legal); legal; cell = next_bit(&legal)){
        calc_flip(&flip, &board, cell);
        board.move(&flip);
            g = -nega_alpha_end(&board, -beta, -alpha, false);
        board.undo(&flip);
        if (alpha < g){
            alpha = g;
            res.value = g;
            res.policy = cell;
        }
    }
    return res;
}

Search_result ai(Board board, int mid_depth, int end_depth){
    if (mid_depth <= 0 || end_depth <= 0)
        return (Search_result){POLICY_UNDEFINED, SCORE_UNDEFINED};
    if (board.n + end_depth >= HW2)
        return ai_end(board);
    return ai_mid(board, mid_depth);
}