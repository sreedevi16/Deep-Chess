#include "chess-library/src/include.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;        
using namespace chess;
using json = nlohmann::json;

string FirstMove(const string& fen) {
Board board(fen);
Movelist moves;
movegen::legalmoves(moves, board);
for (const Move& move1 : moves) {
board.makeMove(move1);

if (board.isCheckmate()) {
board.unmakeMove(move1);
return uci::moveToUci(move1);
}
if (board.isGameOver().second != GameResult::NONE) {
board.unmakeMove(move1);
continue;
}

bool bool1 = true;
Movelist blackMove;
movegen::legalmoves(blackMove, board);

for (const Move& move2 : blackMove) {
board.makeMove(move2);
bool bool2 = false;
Movelist whiteMove2;
movegen::legalmoves(whiteMove2, board);

for (const Move& move3 : whiteMove2) {
board.makeMove(move3);
if (board.isCheckmate()) {
bool2 = true;
board.unmakeMove(move3);
break;
}
board.unmakeMove(move3);
}

board.unmakeMove(move2);

if (!bool2) {
bool1 = false;
break;
}
}
board.unmakeMove(move1);
if (bool1) {
return uci::moveToUci(move1);
}
}
return "none";
}

