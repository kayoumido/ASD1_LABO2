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
        {DAME_HAUT,        GATEAU_DROIT,    ARROSOIR_GAUCHE, FILLE_HAUT},
        {DAME_BAS,         ARROSOIR_GAUCHE, FILLE_HAUT,      GATEAU_DROIT},
        {FILLE_BAS,        GATEAU_GAUCHE,   DAME_HAUT,       ARROSOIR_DROIT},
        {ARROSOIR_DROIT,   GATEAU_GAUCHE,   DAME_HAUT,       FILLE_HAUT},
        {FILLE_BAS,        DAME_HAUT,       ARROSOIR_DROIT,  GATEAU_DROIT},
        {DAME_BAS,         GATEAU_GAUCHE,   FILLE_HAUT,      ARROSOIR_DROIT},
        {FILLE_BAS,        ARROSOIR_GAUCHE, DAME_HAUT,       GATEAU_DROIT},
        {DAME_BAS,         ARROSOIR_GAUCHE, GATEAU_DROIT,    FILLE_HAUT},
        {ARROSOIR_INVERSE, DAME_HAUT,       GATEAU_DROIT,    FILLE_BAS},
};

const MatchingAttachement MATCHING_ATTACHEMENT = {
        FILLE_BAS,
        FILLE_HAUT,
        DAME_BAS,
        DAME_HAUT,
        ARROSOIR_DROIT,
        ARROSOIR_GAUCHE,
        GATEAU_DROIT,
        GATEAU_GAUCHE,
        NONE,
        NONE
};


void displayPiece(size_t pieceNb, const Orientations &PIECES_ORIENTATIONS) {
    char orientation = 'a' + PIECES_ORIENTATIONS.at(pieceNb);
    cout << ++pieceNb << orientation << " ";
}

void displayPieces(const Pieces &TO_DISPLAY, const Orientations &PIECES_ORIENTATIONS) {
    for (size_t pieceNb = 0; pieceNb < TO_DISPLAY.size(); ++pieceNb) {
        if (TO_DISPLAY.at(pieceNb) != EMPTY) {

            Piece current = TO_DISPLAY.at(pieceNb);

            auto currentRealIt = find(TO_DISPLAY.begin(), TO_DISPLAY.end(), current);

            auto realPosition = distance(TO_DISPLAY.begin(), currentRealIt);

            displayPiece(realPosition, PIECES_ORIENTATIONS);
        }
    }
    cout << endl;
}

bool pieceMatchesWithBoard(const Pieces &BOARD, const Orientations &orientations, const Piece &TO_INSERT, size_t pos) {

    if (pos == 0) {
        return true;
    }

    // check if we're in the first row
    if (pos < PIECE_BY_LINE) {

        // then we only need to check if we match with the piece on the left
        Piece leftPiece = BOARD.at(pos - 1);

        Sides currentOrientation = orientations.at(pos);
        Sides leftOrientation = orientations.at(pos - 1);

        AttachementType currentAttachement = TO_INSERT.at((Sides::LEFT + currentOrientation) % NB_SIDES);
        AttachementType leftAttachement = leftPiece.at((Sides::RIGHT + leftOrientation) % NB_SIDES);

        return areMatchingPieces(leftAttachement, currentAttachement);
    }

    // check if we're in the first col
    if (pos % PIECE_BY_LINE == 0) {

        // then we only need to check if we match with the piece above
        Piece topPiece = BOARD.at(pos - PIECE_BY_LINE);

        Sides currentOrientation = orientations.at(pos);
        Sides topOrientation = orientations.at(pos - PIECE_BY_LINE);

        AttachementType currentAttachement = TO_INSERT.at((Sides::UP + currentOrientation) % NB_SIDES);
        AttachementType topAttachement = topPiece.at((Sides::DOWN + topOrientation) % NB_SIDES);

        return areMatchingPieces(topAttachement, currentAttachement);
    }

    // since we aren't in the first row or col, we need to check the piece on the left and above
    Piece topPiece = BOARD.at(pos - PIECE_BY_LINE);
    Piece leftPiece = BOARD.at(pos - 1);

    Sides currentOrientation = orientations.at(pos);
    Sides leftOrientation = orientations.at(pos - 1);
    Sides topOrientation = orientations.at(pos - PIECE_BY_LINE);

    AttachementType currentAttachement = TO_INSERT.at((Sides::LEFT + currentOrientation) % NB_SIDES);
    AttachementType leftAttachement = leftPiece.at((Sides::RIGHT + leftOrientation) % NB_SIDES);
    AttachementType topAttachement = topPiece.at((Sides::DOWN + topOrientation) % NB_SIDES);


    return areMatchingPieces(leftAttachement, currentAttachement) and
           areMatchingPieces(topAttachement, currentAttachement);
}

bool areMatchingPieces(const AttachementType fixedPiece, const AttachementType testPiece) {
    if (fixedPiece < 8 && testPiece < 8) {
        return MATCHING_ATTACHEMENT.at(testPiece) == fixedPiece;
    }
    return false;
}

void turnPiece(const size_t PIECE_NB, Orientations &piecesOrientations) {
    try {
        Sides orientation = piecesOrientations.at(PIECE_NB);
        Sides newOrientation = (orientation == (NB_SIDES - 1) ? (Sides) 0 : Sides(orientation + 1));
        piecesOrientations.at(PIECE_NB) = newOrientation;

    } catch (const std::exception &e) {
        cout << e.what();
    }
}

void placePiece(Pieces available, Pieces used, Orientations orientations, unsigned pos) {

    if (pos == 9) {
        displayPieces(used, orientations);
    } else {
        // loop through the available pieces
        for (size_t pieceNb = 0; pieceNb < 9; ++pieceNb) {

            Piece current = available.at(pieceNb);
            auto currentIt = available.begin() + pieceNb;

            if (current == EMPTY) continue;

            // test all sides of the current piece
            for (size_t side = 0; side < NB_SIDES; ++side) {
                orientations.at(pos) = (Sides)side;

                // check if we can add
                if (pieceMatchesWithBoard(used, orientations, current, pos)) {

                    used.at(pos)        = current;
                    Pieces tmpAvailable = available;

                    tmpAvailable.at(pieceNb) = EMPTY;
                    displayPieces(used, orientations);
                    placePiece(tmpAvailable, used, orientations, pos + 1);
                }

            }
        }
    }
}

