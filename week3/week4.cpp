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
return {max_player ? -1000 : +1000, Move()};
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
int main() {
ios::sync_with_stdio(false);
cin.tie(nullptr);
                
    Board board;
    string line;
                 
while (getline(cin, line)) {
 istringstream iss(line);
 string token;
 iss >> token;
                    
 if (token == "uci") {
 cout << "id name MyChessBot" << endl;
 cout << "id author YourName" << endl;
cout << "uciok" << endl;                
} else if (token == "isready") {
cout << "readyok" << endl;
                    
} else if (token == "ucinewgame") {
board = Board();
} else if (token == "position") {
string type;
 iss >> type;
            
  if (type == "startpos") {
board = Board();
  string movesToken;
 iss >> movesToken;
 string moveStr;
  while (iss >> moveStr) {
  Move move = uci::uciToMove(board, moveStr);
  board.makeMove(move);
                }
 } else if (type == "fen") {
 string fenStr, part;
 for (int i = 0; i < 6; i++) {
  iss >> part;
 fenStr += part + " ";
                }
  board = Board(fenStr);
 string movesToken;
 iss >> movesToken;
  string moveStr;
while (iss >> moveStr) {
    Move move = uci::uciToMove(board, moveStr);
  board.makeMove(move);
                }
 } else if (token == "go") {
 bool isWhite = (board.sideToMove() == Color::WHITE);
            
auto [score, bestMove] = minimax(board, 5, isWhite);
                
cout << "bestmove " << uci::moveToUci(bestMove) << endl;
                
  } else if (token == "quit") {
  break;
  }
  }
  return 0;
}
