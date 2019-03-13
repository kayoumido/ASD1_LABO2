#include <iostream>
#include <algorithm>
#include "pieces.h"

using namespace std;


//Enum des cotes d'une piece
enum class Sides {UP, RIGHT, DOWN, LEFT};
const unsigned ALL_SIDES_DEFINED = 4;
const unsigned PIECE_BY_LINE = 3;
const unsigned MAX_ID_TO_BE_A_PAIR = 7;


void turnPiece(Piece& piece) {
    std::rotate(piece.begin(), piece.begin() + 1, piece.end());
}

void displayPiece(const Piece& PIECE) {
    Pieces allPiecesDefined = PIECES;
    unsigned pieceNb = 1;
    for(auto it = allPiecesDefined.begin(); it < allPiecesDefined.end(); ++it) {
        char pos = 'a';
        for(unsigned side = 0; side < ALL_SIDES_DEFINED; ++side) {
            if(PIECE == *it) {
                cout << pieceNb << char(pos + side) << " ";
                break; // Don't forget to break because if the first side is correct, it will work all the time because we dont turn the piece
            } else {
                turnPiece(*it);
            }
        }

        ++pieceNb;
    }

 }

void displaySolution(const Pieces RESULT_PIECES) {
    for (Piece piece : RESULT_PIECES) {
        displayPiece(piece);
    }
    cout << endl;
}

bool isTwoPiecesMatching(Piece firstPiece, const Sides& FIRST_PIECE_SIDE_CHECK, Piece secondPiece, const Sides& SECOND_PIECE_SIDE_CHECK) {
    if(firstPiece.at((unsigned)FIRST_PIECE_SIDE_CHECK) > MAX_ID_TO_BE_A_PAIR or secondPiece.at((unsigned)SECOND_PIECE_SIDE_CHECK) > MAX_ID_TO_BE_A_PAIR) {
        return false;
    }

    bool isMatching = false;
    bool isMatchingInverse = false;

    // WIP
    if(firstPiece.at((unsigned)FIRST_PIECE_SIDE_CHECK) % 2 == 0) {


        isMatching = firstPiece.at((unsigned) FIRST_PIECE_SIDE_CHECK) ==
                     (secondPiece.at((unsigned) SECOND_PIECE_SIDE_CHECK) - 1);
        turnPiece(firstPiece);
        turnPiece(firstPiece);
        turnPiece(secondPiece);
        turnPiece(secondPiece);
        isMatchingInverse = secondPiece.at((unsigned) FIRST_PIECE_SIDE_CHECK) ==
                            (firstPiece.at((unsigned) SECOND_PIECE_SIDE_CHECK) - 1);
    }

    return (isMatching or isMatchingInverse);
}

bool pieceMatchWithBoard(const Pieces& BOARD, const Piece& PIECE_TO_ADD) {
    bool piecesIsMatching = false;
    // If the first line of the board is not full -> only check last board piece (right side) with new piece (left side)
    if(BOARD.size() < PIECE_BY_LINE) {
        piecesIsMatching = isTwoPiecesMatching(BOARD.back(), Sides::RIGHT, PIECE_TO_ADD, Sides::LEFT);
    }
    // Two other lines of the board
    else
    {
        const Piece PIECE_BOARD_UPPER_NEW = BOARD.at(BOARD.size() - PIECE_BY_LINE);
        // We will put the new piece in the first position in the line -> Pair to check : Piece on board upper (bottom side) with new piece (upper side)
        if((BOARD.size() % PIECE_BY_LINE) == 0) {
            piecesIsMatching = isTwoPiecesMatching(PIECE_BOARD_UPPER_NEW, Sides::DOWN, PIECE_TO_ADD, Sides::UP);
        }isTwoPiecesMatching
        // We will put the new piece every where else => Pairs to check :
        // 1. last piece on board (right side) with new piece (left side)
        // 2. Piece on board upper (bottom side) with new piece (upper side)
        else
        {
            piecesIsMatching = (isTwoPiecesMatching(BOARD.back(), Sides::RIGHT, PIECE_TO_ADD, Sides::LEFT)
                                and isTwoPiecesMatching(PIECE_BOARD_UPPER_NEW, Sides::DOWN, PIECE_TO_ADD, Sides::UP));
        }
    }

    return piecesIsMatching;
}

void putPieceOnBoard(Pieces usedPieces, Pieces availablePieces) {
    // Trivial case : if the game board is full
    if(availablePieces.size() == 0) {
        displaySolution(usedPieces);
    } else {
        for(auto i = availablePieces.begin(); i < availablePieces.end(); ++i) {
            // Piece currentPiece = (*i);
            for(unsigned side = 0; side < ALL_SIDES_DEFINED; ++side) {
                // If there is no piece already used, the first one is obligatory good. Otherwise test the piece we want to put
                if(usedPieces.size() == 0 or pieceMatchWithBoard(usedPieces, (*i))) {
                    usedPieces.push_back(*i);
                    availablePieces.erase(i);
                    putPieceOnBoard(usedPieces, availablePieces);
                }
                turnPiece(*i);

            }
            availablePieces.insert(i, usedPieces.back());
            usedPieces.pop_back();
        }
    }
}



int main() {

    Pieces availablePieces = PIECES;
    Pieces usedPieces;

    putPieceOnBoard(usedPieces, availablePieces);

    Piece p9 = PIECES.at(8);
    Piece p5 = PIECES.at(4);
    turnPiece(p9);
    turnPiece(p9);
    turnPiece(p9);
    displayPiece(p9);
    displayPiece(p5);
    cout << endl;
    cout << p9.at((unsigned)Sides::DOWN) << endl;
    cout << p5.at((unsigned)Sides::UP) << endl;
    cout << isTwoPiecesMatching(p9, Sides::DOWN, p5, Sides::UP);


    /*Piece p1 = PIECES.at(6);
    Piece p2 = PIECES.at(3);

    turnPiece(p1);
    turnPiece(p1);
    turnPiece(p1);
    turnPiece(p2);
    turnPiece(p2);
    turnPiece(p2);


    cout << p1.at((unsigned)Sides::RIGHT) << endl;
    cout << p2.at((unsigned)Sides::LEFT) << endl;

    displayPiece(p1);
    displayPiece(p2);
    cout << isTwoPiecesMatching(p1, Sides::RIGHT, p2, Sides::LEFT);

*/
    return 0;
}