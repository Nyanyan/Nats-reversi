#pragma once
#include <iostream>
#include "common.hpp"
#include "mobility.hpp"
#include "flip.hpp"

using namespace std;

class Board {
    public:
        uint64_t player;
        uint64_t opponent;
        uint_fast8_t n;
        uint_fast8_t parity;

    public:
        int operator == (Board a) {
            return player == a.player && opponent == a.opponent;
        }
        
        inline Board copy(){
            Board res;
            res.player = player;
            res.opponent = opponent;
            res.n = n;
            res.parity = parity;
            return res;
        }

        inline void copy(Board *res){
            res->player = player;
            res->opponent = opponent;
            res->n = n;
            res->parity = parity;
        }

        inline void print() const{
            for (int i = HW2_M1; i >= 0; --i){
                if (1 & (player >> i))
                    cerr << "X ";
                else if (1 & (opponent >> i))
                    cerr << "O ";
                else
                    cerr << ". ";
                if (i % HW == 0)
                    cerr << endl;
            }
        }

        inline uint64_t get_legal(){
            return calc_legal(player, opponent);
        }

        inline void move(const Flip *flip) {
            player ^= flip->flip;
            opponent ^= flip->flip;
            player ^= 1ULL << flip->pos;
            swap(player, opponent);
            ++n;
        }

        inline void move_copy(const Flip *flip, Board *res) {
            res->opponent = player ^ flip->flip;
            res->player = opponent ^ flip->flip;
            res->opponent ^= 1ULL << flip->pos;
            res->n = n + 1;
        }

        inline Board move_copy(const Flip *flip) {
            Board res;
            move_copy(flip, &res);
            return res;
        }

        inline void pass(){
            swap(player, opponent);
        }

        inline void undo(const Flip *flip){
            --n;
            swap(player, opponent);
            player ^= 1ULL << flip->pos;
            player ^= flip->flip;
            opponent ^= flip->flip;
        }

        inline int score(){
            int p_score = pop_count_ull(player), o_score = pop_count_ull(opponent);
            int score = p_score - o_score, vacant_score = HW2 - p_score - o_score;
            if (score > 0)
                score += vacant_score;
            else if (score < 0)
                score -= vacant_score;
            return score;
        }
};

inline void calc_flip(Flip *flip, const Board *b, const uint_fast8_t policy){
    flip->calc_flip(b->player, b->opponent, policy);
}

inline Flip calc_flip(const Board *b, const uint_fast8_t policy){
    Flip flip;
    flip.calc_flip(b->player, b->opponent, policy);
    return flip;
}
