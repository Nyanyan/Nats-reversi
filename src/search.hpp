#pragma once
#include <iostream>
#include "board.hpp"
#include "evaluate.hpp"

using namespace std;

int nega_alpha_mid(Board *board, int alpha, int beta, int depth, bool passed){
    if (depth == 0)
        return evaluate(board);
    uint64_t legal = board->get_legal();
    int v = -INF, g;
    if (legal == 0ULL){
        if (passed)
            return board->score();
        board->pass();
            v = -nega_alpha_mid(board, -beta, -alpha, depth, true);
        board->pass();
        return v;
    }
    Flip flip;
    for (uint_fast8_t cell = first_bit(&legal); legal; cell = next_bit(&legal)){
        board->calc_flip(&flip, cell);
        board->move(&flip);
            g = -nega_alpha_mid(board, -beta, -alpha, depth - 1, false);
        board->undo(&flip);
        v = max(v, g);
        alpha = max(alpha, g);
        if (beta <= alpha)
            break;
    }
    return v;
}

int nega_alpha_end(Board *board, int alpha, int beta, bool passed){
    if (board->n == HW2)
        return board->score();
    uint64_t legal = board->get_legal();
    int v = -INF, g;
    if (legal == 0ULL){
        if (passed)
            return board->score();
        board->pass();
            v = -nega_alpha_end(board, -beta, -alpha, true);
        board->pass();
        return v;
    }
    Flip flip;
    for (uint_fast8_t cell = first_bit(&legal); legal; cell = next_bit(&legal)){
        board->calc_flip(&flip, cell);
        board->move(&flip);
            g = -nega_alpha_end(board, -beta, -alpha, false);
        board->undo(&flip);
        v = max(v, g);
        alpha = max(alpha, g);
        if (beta <= alpha)
            break;
    }
    return v;
}

