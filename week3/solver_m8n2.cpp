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

string findFirstMove(const string& fen) {
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

        bool allRepliesMated = true;
        Movelist blackMoves;
        movegen::legalmoves(blackMoves, board);

        for (const Move& move2 : blackMoves) {
            board.makeMove(move2);

            bool foundMate = false;
            Movelist whiteMoves2;
            movegen::legalmoves(whiteMoves2, board);

            for (const Move& move3 : whiteMoves2) {
                board.makeMove(move3);
                if (board.isCheckmate()) {
                    foundMate = true;
                    board.unmakeMove(move3);
                    break;
                }
                board.unmakeMove(move3);
            }

            board.unmakeMove(move2);

            if (!foundMate) {
                allRepliesMated = false;
                break;
            }
        }

        board.unmakeMove(move1);

        if (allRepliesMated) {
            return uci::moveToUci(move1);
        }
    }

    return "none";
}
