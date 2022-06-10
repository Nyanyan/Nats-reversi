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

        inline void calc_flip(Flip *flip, const uint_fast8_t policy){
            flip->calc_flip(player, opponent, policy);
        }
};


