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
        cerr << "[E] no move available" << endl;
        res.policy = POLICY_UNDEFINED;
        res.value = SCORE_UNDEFINED;
        return res;
    }
    int alpha = -SCORE_MAX, beta = SCORE_MAX, g;
    Flip flip;
    for (uint_fast8_t cell = first_bit(&legal); legal; cell = next_bit(&legal)){
        board.calc_flip(&flip, cell);
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
        cerr << "[E] no move available" << endl;
        res.policy = POLICY_UNDEFINED;
        res.value = SCORE_UNDEFINED;
        return res;
    }
    int alpha = -SCORE_MAX - 1, beta = SCORE_MAX, g;
    Flip flip;
    for (uint_fast8_t cell = first_bit(&legal); legal; cell = next_bit(&legal)){
        board.calc_flip(&flip, cell);
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
    if (board.n + end_depth >= HW2){
        cerr << "[I] endgame depth " << HW2 - board.n << endl;
        return ai_end(board);
    }
    cerr << "[I] midgame depth " << mid_depth << endl;
    return ai_mid(board, mid_depth);
}