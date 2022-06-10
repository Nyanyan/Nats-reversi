#include <iostream>
#include "ai.hpp"

using namespace std;

Board input_board(){
    Board res;
    char elem;
    res.player = 0;
    res.opponent = 0;
    for (int i = 0; i < HW2; ++i){
        cin >> elem;
        if (elem == '0' || elem == 'X' || elem == 'x' || elem == 'B' || elem == 'b' || elem == '*')
            res.player |= 1ULL << (HW2_M1 - i);
        else if (elem == '1' || elem == 'O' || elem == 'o' || elem == 'W' || elem == 'w')
            res.opponent |= 1ULL << (HW2_M1 - i);
    }
    cin >> elem;
    if (elem == '1' || elem == 'O' || elem == 'o' || elem == 'W' || elem == 'w')
        swap(res.player, res.opponent);
    res.n = pop_count_ull(res.player | res.opponent);
    res.print();
    return res;
}

string idx_to_coord(int idx){
    int y = HW_M1 - idx / HW;
    int x = HW_M1 - idx % HW;
    const string x_coord = "abcdefgh";
    return x_coord[x] + to_string(y + 1);
}

int main(int argc, char* argv[]){
    cerr << "[I] Nats Othello AI" << endl;
    cerr << "[I] (c) 2022 Takuto Yamana" << endl;
    int mid_depth = 4, end_depth = 8;
    if (argc == 1){
        cerr << "[I] usage" << endl;
        cerr << "[I] [executable] [midgame depth] [endgame depth]" << endl;
        cerr << "[i] use default depth" << endl;
    } else if (argc == 2){
        mid_depth = atoi(argv[1]);
        end_depth = mid_depth * 2;
    } else if (argc == 3){
        mid_depth = atoi(argv[1]);
        end_depth = atoi(argv[2]);
    }
    if (mid_depth <= 0 || end_depth <= 0){
        cerr << "[I] usage" << endl;
        cerr << "[I] [executable] [midgame depth] [endgame depth]" << endl;
        cerr << "[E] illegal depth" << endl;
        return 1;
    }
    cerr << "[I] depth mid:" << mid_depth << " end:" << end_depth << endl;
    bit_init();
    flip_init();
    cerr << "[I] initialized" << endl;
    Board board;
    Search_result search_result;
    uint64_t strt;
    while (true){
        board = input_board();
        strt = tim();
        search_result = ai(board, mid_depth, end_depth);
        cerr << "[I] time elapsed " << tim() - strt << " ms" << endl;
        if (search_result.policy != POLICY_UNDEFINED)
            cout << idx_to_coord(search_result.policy) << " " << search_result.value << endl;
        else
            cout << "ERROR" << endl;
    }
    return 0;
}