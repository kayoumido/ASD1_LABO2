#include <iostream>
#include <algorithm>
#include "pieces.h"

using namespace std;


int main() {

    Pieces availablePieces = PIECES;
    Pieces usedPieces;
    Orientations piecesOrientations;

    placePiece(usedPieces, availablePieces, piecesOrientations);

    return 0;
}
