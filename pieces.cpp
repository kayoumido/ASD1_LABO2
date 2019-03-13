//
//  pieces.cpp
//  Puzzle récursif
//
//  Created by Olivier Cuisenaire on 06.11.18.
//  Copyright © 2018 Olivier Cuisenaire. All rights reserved.
//

#include "pieces.h"

#include <iostream>

using namespace std;

const Pieces PIECES = {
  { DAME_HAUT, GATEAU_DROIT, ARROSOIR_GAUCHE, FILLE_HAUT },
  { DAME_BAS, ARROSOIR_GAUCHE, FILLE_HAUT, GATEAU_DROIT },
  { FILLE_BAS, GATEAU_GAUCHE, DAME_HAUT, ARROSOIR_DROIT },
  { ARROSOIR_DROIT, GATEAU_GAUCHE, DAME_HAUT, FILLE_HAUT},
  { FILLE_BAS, DAME_HAUT, ARROSOIR_DROIT, GATEAU_DROIT },
  { DAME_BAS, GATEAU_GAUCHE, FILLE_HAUT, ARROSOIR_DROIT},
  { FILLE_BAS, ARROSOIR_GAUCHE, DAME_HAUT, GATEAU_DROIT },
  { DAME_BAS, ARROSOIR_GAUCHE, GATEAU_DROIT, FILLE_HAUT },
  { ARROSOIR_INVERSE, DAME_HAUT, GATEAU_DROIT, FILLE_BAS },
};


void displayPiece(size_t pieceNb, const PiecesSides& PIECES_ORIENTATIONS) {
    char orientation = 'a' + PIECES_ORIENTATIONS.at(pieceNb);
    cout << ++pieceNb << orientation << " ";
}

void displayPieces(const Pieces& PIECES, const PiecesSides& PIECES_ORIENTATIONS) {
    for(size_t pieceNb = 0; pieceNb < PIECES.size(); ++pieceNb) {
        displayPiece(pieceNb, PIECES_ORIENTATIONS);
    }
    cout << endl;
}


bool pieceMatchesWithBoard(const Pieces& BOARD, const Piece &TO_INSERT) {

    size_t positionToInsertAt = BOARD.size();

    // check if we're in the first row
    if (positionToInsertAt < PIECE_BY_LINE) {
        // then we only need to check if we match with the piece on the left
        Piece leftPiece = BOARD.at(positionToInsertAt - 1);

        // return isTwoPiecesMatching(leftPiece.at(Sides::RIGHT), TO_INSERT.at(Sides::LEFT));
    }

    // check if we're in the first col
    if (positionToInsertAt % PIECE_BY_LINE == 0) {
        // then we only need to check if we match with the piece above
        Piece topPiece = BOARD.at(positionToInsertAt - PIECE_BY_LINE);

        // return isTwoPiecesMatching(topPiece.at(Sides::DOWN), TO_INSERT.at(Sides::UP));
    }

    // since we aren't in the first row or col, we need to check the piece on the left and above
    Piece topPiece = BOARD.at(positionToInsertAt - PIECE_BY_LINE);
    Piece leftPiece = BOARD.at(positionToInsertAt - 1);

    /*
    return  isTwoPiecesMatching(leftPiece.at(Sides::RIGHT), TO_INSERT.at(Sides::LEFT)) and
            isTwoPiecesMatching(topPiece.at(Sides::DOWN), TO_INSERT.at(Sides::UP));
    */
}