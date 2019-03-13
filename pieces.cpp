//
//  pieces.cpp
//  Puzzle récursif
//
//  Created by Olivier Cuisenaire on 06.11.18.
//  Copyright © 2018 Olivier Cuisenaire. All rights reserved.
//

#include "pieces.h"

#include <iostream>
#include <algorithm>

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

const MatchingAttachement MATCHING_ATTACHEMENT = {
  FILLE_BAS, FILLE_HAUT, DAME_BAS, DAME_HAUT, ARROSOIR_DROIT, ARROSOIR_GAUCHE, GATEAU_DROIT, GATEAU_GAUCHE, NONE, NONE
};

void displayPiece(size_t pieceNb, const Orientations& PIECES_ORIENTATIONS) {
    char orientation = 'a' + PIECES_ORIENTATIONS.at(pieceNb);
    cout << ++pieceNb << orientation << " ";
}

void displayPieces(const Pieces& PIECES, const Orientations& PIECES_ORIENTATIONS) {
    for(size_t pieceNb = 0; pieceNb < PIECES.size(); ++pieceNb) {
        displayPiece(pieceNb, PIECES_ORIENTATIONS);
    }
    cout << endl;
}

bool pieceMatchesWithBoard(const Pieces& BOARD, const Piece &TO_INSERT) {

    size_t position = BOARD.size();

    if (position == 0) {
        return true;
    }

    // check if we're in the first row
    if (position < PIECE_BY_LINE) {
        // then we only need to check if we match with the piece on the left
        Piece leftPiece = BOARD.at(position - 1);

        // return isTwoPiecesMatching(leftPiece.at(Sides::RIGHT), TO_INSERT.at(Sides::LEFT));
    }

    // check if we're in the first col
    if (position % PIECE_BY_LINE == 0) {
        // then we only need to check if we match with the piece above
        Piece topPiece = BOARD.at(position - PIECE_BY_LINE);

        // return isTwoPiecesMatching(topPiece.at(Sides::DOWN), TO_INSERT.at(Sides::UP));
    }

    // since we aren't in the first row or col, we need to check the piece on the left and above
    Piece topPiece = BOARD.at(position - PIECE_BY_LINE);
    Piece leftPiece = BOARD.at(position - 1);

    /*
    return  isTwoPiecesMatching(leftPiece.at(Sides::RIGHT), TO_INSERT.at(Sides::LEFT)) and
            isTwoPiecesMatching(topPiece.at(Sides::DOWN), TO_INSERT.at(Sides::UP));
    */
}

void placePiece(Pieces used, Pieces available, Orientations orientations) {

    Pieces imposibleToUse;

    if (available.empty()) {
        // displayPieces(used, orientations);
    } else {
        // loop through the available pieces
        for (size_t pieceNb = 0; pieceNb < available.size(); ++pieceNb) {

            Piece current = available.at(pieceNb);
            auto currentIt = available.begin() + pieceNb;

            // check if the current piece can be used
            if (find(imposibleToUse.begin(), imposibleToUse.end(), current) != imposibleToUse.end()) continue;

            // test all sides of the current piece
            for (size_t side = 0; side < NB_SIDES; ++side) {
                // check if we can add
                if (pieceMatchesWithBoard(used, current)) {
                    used.push_back(current);
                    available.erase(currentIt);
                    placePiece(used, available, orientations);
                }
            }

            // the current piece can't be used at the current position
            imposibleToUse.push_back(current);
            used.pop_back();
            available.insert(currentIt, current);

            // turn;
        }
    }
}

bool areMatchingPieces(const AttachementType fixedPiece,const AttachementType testPiece) {
  if( fixedPiece < 8 && testPiece < 8) {
    return MATCHING_ATTACHEMENT.at(testPiece) == fixedPiece ? true : false;
  }
  return false;
}

void turnPiece(const size_t PIECE_NB, Orientations& piecesOrientations) {
    Sides orientation = piecesOrientations.at(PIECE_NB);
    Sides newOrientation = (orientation == (NB_SIDES - 1) ? (Sides)0 : Sides(orientation + 1));
    piecesOrientations.at(PIECE_NB) = newOrientation;
}

