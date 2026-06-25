#include "chess-library/src/include.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <climits>
using namespace std;
using namespace chess;

pair<int, Move> minimax(Board& board, int depth, bool max_player){
                
Movelist moves; 
movegen::legalmoves(moves,board);
if (board.inCheck() && moves.empty()) {
return {max_player ? -100 : +100, Move()};
}
if (depth == 0 || moves.empty()) {
 return {0, Move()};
}                   
int bestScore = max_player ? INT_MIN : INT_MAX;
Move bestMove = *moves.begin();
for (const Move& move : moves) {
 board.makeMove(move);
auto [score, _] = minimax(board, depth - 1, !max_player);
board.unmakeMove(move);
if (max_player && score > bestScore) {
bestScore = score;  
bestMove  = move;
}
else if (!max_player && score < bestScore) {
bestScore = score;
  bestMove  = move;
}
}           
return {bestScore, bestMove};
}
int main(){
  Board  board("fen");
pair<int, Move> opt = minimax(board,3,true);
cout<< uci::moveToUci(opt.second);
board.makeMove(opt.second);
}
