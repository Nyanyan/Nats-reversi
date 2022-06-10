#pragma once
#include <iostream>
#include "common.hpp"
#include "bit.hpp"

using namespace std;

uint_fast8_t flip_pre_calc[N_8BIT][N_8BIT][HW];


class Flip{
    public:
        uint_fast8_t pos;
        uint64_t flip;
    
    public:
        inline void copy(Flip *mob) const{
            mob->pos = pos;
            mob->flip = flip;
        }

        inline void calc_flip(const uint64_t player, const uint64_t opponent, const uint_fast8_t place){
            int_fast8_t t, u;
            uint8_t p, o;
            flip = 0;
            pos = place;
            t = place / HW;
            u = place % HW;
            p = (player >> (HW * t)) & 0b11111111;
            o = (opponent >> (HW * t)) & 0b11111111;
            flip |= (uint64_t)flip_pre_calc[p][o][u] << (HW * t);
            p = join_v_line(player, u);
            o = join_v_line(opponent, u);
            flip |= split_v_lines[flip_pre_calc[p][o][t]] << u;
            if (u + t >= 2 && u + t <= 12){
                p = join_d7_line(player, u + t) & d7_mask[place];
                o = join_d7_line(opponent, u + t) & d7_mask[place];
                flip |= split_d7_lines[flip_pre_calc[p][o][HW_M1 - t] & d7_mask[place]][u + t - 2];
            }
            if (u - t >= -5 && u - t <= 5){
                p = join_d9_line(player, u - t) & d9_mask[place];
                o = join_d9_line(opponent, u - t) & d9_mask[place];
                flip |= split_d9_lines[flip_pre_calc[p][o][t] & d9_mask[place]][u - t + 5];
            }
        }
};

void flip_init(){
    uint_fast16_t player, opponent, place;
    uint_fast8_t wh, put, m1, m2, m3, m4, m5, m6;
    for (player = 0; player < N_8BIT; ++player){
        for (opponent = 0; opponent < N_8BIT; ++opponent){
            for (place = 0; place < HW; ++place){
                flip_pre_calc[player][opponent][place] = 0;
                if ((1 & (player >> place)) == 0 && (1 & (opponent >> place)) == 0 && (player & opponent) == 0){
                    put = 1 << place;
                    wh = opponent & 0b01111110;
                    m1 = put >> 1;
                    if( (m1 & wh) != 0 ) {
                        if( ((m2 = m1 >> 1) & wh) == 0  ) {
                            if( (m2 & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1;
                        } else if( ((m3 = m2 >> 1) & wh) == 0 ) {
                            if( (m3 & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1 | m2;
                        } else if( ((m4 = m3 >> 1) & wh) == 0 ) {
                            if( (m4 & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1 | m2 | m3;
                        } else if( ((m5 = m4 >> 1) & wh) == 0 ) {
                            if( (m5 & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1 | m2 | m3 | m4;
                        } else if( ((m6 = m5 >> 1) & wh) == 0 ) {
                            if( (m6 & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1 | m2 | m3 | m4 | m5;
                        } else {
                            if( ((m6 >> 1) & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1 | m2 | m3 | m4 | m5 | m6;
                        }
                    }
                    m1 = put << 1;
                    if( (m1 & wh) != 0 ) {
                        if( ((m2 = m1 << 1) & wh) == 0  ) {
                            if( (m2 & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1;
                        } else if( ((m3 = m2 << 1) & wh) == 0 ) {
                            if( (m3 & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1 | m2;
                        } else if( ((m4 = m3 << 1) & wh) == 0 ) {
                            if( (m4 & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1 | m2 | m3;
                        } else if( ((m5 = m4 << 1) & wh) == 0 ) {
                            if( (m5 & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1 | m2 | m3 | m4;
                        } else if( ((m6 = m5 << 1) & wh) == 0 ) {
                            if( (m6 & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1 | m2 | m3 | m4 | m5;
                        } else {
                            if( ((m6 << 1) & player) != 0 )
                                flip_pre_calc[player][opponent][place] |= m1 | m2 | m3 | m4 | m5 | m6;
                        }
                    }
                }
            }
        }
    }
}
