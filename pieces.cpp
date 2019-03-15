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
        {DAME_BAS,         ARROSOIR_GAUCHE, GATEAU_DROIT,    FILLE_HAUT},/*
        {ARROSOIR_INVERSE, DAME_HAUT,       GATEAU_DROIT,    FILLE_BAS},*/
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

        Piece current = TO_DISPLAY.at(pieceNb);

        auto realIt = find(PIECES.begin(), PIECES.end(), current);

        auto realPosition = distance(PIECES.begin(), realIt);

        displayPiece(realPosition, PIECES_ORIENTATIONS);
    }
    cout << endl;
}

bool pieceMatchesWithBoard(const Pieces &BOARD, const Orientations &orientations, const Piece &TO_INSERT) {

    size_t position = BOARD.size() - 1;

    if (position == 0) {
        return true;
    }

    // check if we're in the first row
    if (position < PIECE_BY_LINE) {

        // then we only need to check if we match with the piece on the left
        Piece leftPiece = BOARD.at(position - 1);

        Sides currentOrientation    = orientations.at(position);
        Sides leftOrientation       = orientations.at(position - 1);

        AttachementType currentAttachement  = TO_INSERT.at((Sides::LEFT + currentOrientation) % NB_SIDES);
        AttachementType leftAttachement     = leftPiece.at((Sides::RIGHT + leftOrientation) % NB_SIDES);

        return areMatchingPieces(leftAttachement, currentAttachement);
    }

    // check if we're in the first col
    if (position % PIECE_BY_LINE == 0) {

        // then we only need to check if we match with the piece above
        Piece topPiece = BOARD.at(position - PIECE_BY_LINE);

        Sides currentOrientation    = orientations.at(position);
        Sides topOrientation        = orientations.at(position - PIECE_BY_LINE);

        AttachementType currentAttachement  = TO_INSERT.at((Sides::UP + currentOrientation) % NB_SIDES);
        AttachementType topAttachement      = topPiece.at((Sides::DOWN + topOrientation) % NB_SIDES);

        return areMatchingPieces(topAttachement, currentAttachement);
    }

    // since we aren't in the first row or col, we need to check the piece on the left and above
    Piece topPiece = BOARD.at(position - PIECE_BY_LINE);
    Piece leftPiece = BOARD.at(position - 1);

    Sides currentOrientation    = orientations.at(position);
    Sides leftOrientation       = orientations.at(position - 1);
    Sides topOrientation        = orientations.at(position - PIECE_BY_LINE);

    AttachementType currentAttachement  = TO_INSERT.at((Sides::LEFT + currentOrientation) % NB_SIDES);
    AttachementType leftAttachement     = leftPiece.at((Sides::RIGHT + leftOrientation) % NB_SIDES);
    AttachementType topAttachement      = topPiece.at((Sides::DOWN + topOrientation) % NB_SIDES);


    return areMatchingPieces(leftAttachement, currentAttachement) and
           areMatchingPieces(topAttachement, currentAttachement);
}

void placePiece(Pieces used, Pieces available, Orientations orientations) {


    if (available.empty()) {
        displayPieces(used, orientations);
    } else {
        // loop through the available pieces
        for (size_t pieceNb = 0; pieceNb < available.size(); ++pieceNb) {
            //Pieces impossibleToUse;

            Piece current = available.at(pieceNb);
            auto currentIt = available.begin() + pieceNb;

            // check if the current piece can be used
            //if (find(impossibleToUse.begin(), impossibleToUse.end(), current) != impossibleToUse.end()) continue;

            used.push_back(current);
            orientations.push_back((Sides)0);
            available.erase(currentIt);

            // test all sides of the current piece
            for (size_t side = 0; side < NB_SIDES; ++side) {
                orientations.at(used.size() - 1) = (Sides)side;

                // check if we can add
                if (pieceMatchesWithBoard(used, orientations, current)) {
                    // add
                    placePiece(used, available, orientations);
                    // rem
                }

            }

            used.pop_back();
            orientations.pop_back();
            available.insert(currentIt, current);
        }
    }
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

    } catch (const std::exception& e) {
        cout << e.what();
    }
}

