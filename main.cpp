/*
-----------------------------------------------------------------------------------
Laboratoire : Labo02 - Puzzle impossible
Fichier     : main.cpp
Auteur(s)   : Gabrielle Thurnherr, Loic Dessaules, Doran Kayoumi
Date        : 18.03.2019
But         : Créer un algorithme récursif afin de trouver
              toutes les solutions de Djeco Puzzle impossible des princesses
              <www.djeco.com>
Remarque(s) : -
Compilateur : g++ <8.2.1>
-----------------------------------------------------------------------------------
 */


#include <iostream>
#include <algorithm>
#include "pieces.h"

using namespace std;


enum Sides {
    UP, RIGHT, DOWN, LEFT
};

using Orientations  = std::vector<Sides>;
using MatchingAttachement = std::array<AttachementType, 10>;

const unsigned NB_SIDES = 4;
const unsigned PIECE_BY_LINE = 3;


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


/**
 * @brief display the position and orientation of a piece
 *
 * @param piecePosition of the piece to display
 * @param pieceOrientation of the piece to display
 */
void displayPiece(size_t piecePosition, const Sides &pieceOrientation);

/**
 * @brief display the position and orientation of multiple pieces
 *
 * @param TO_DISPLAY all the pieces to display
 * @param PIECES_ORIENTATIONS orientation of all the pieces
 */
void displayPieces(const Pieces &TO_DISPLAY, const Orientations &PIECES_ORIENTATIONS);

/**
 * @brief check if a piece matches with the board
 *
 * @param BOARD with all the currently used pieces
 * @param orientations of all the curently used pieces
 * @param TO_INSERT piece to check if it matches with the board
 * @return true if the pieces matches otherwise false
 */
bool pieceMatchesWithBoard(const Pieces &BOARD, const Orientations &orientations, const Piece &TO_INSERT);

/**
 * @brief turn a piece, i.e change it's orientation
 *
 * @param PIECE_POSITION the position of the piece within the used pieces
 * @param piecesOrientations orientations off all the currently used pieces
 */
void turnPiece(const size_t PIECE_POSITION, Orientations &piecesOrientations);

/**
 * @brief place a piece on the game board
 *
 * @param used all the pieces currently in use
 * @param available all the availble pices
 * @param orientations of all the currently used pieces
 */
void placePiece(Pieces used, Pieces available, Orientations orientations);

/**
 * @brief   check if two pieces match
 *          i.e they have two matching attachement types
 * @example FILLE_HAUT matches with FILLE_BAS
 *
 * @param fixedPiece that's currently in the game board
 * @param testPiece that's currently being inserted
 * @return true if they match otherwise false
 */
bool areMatchingPieces(const AttachementType &fixedPiece, const AttachementType &testPiece);



int main() {

    Pieces availablePieces = PIECES;
    Pieces usedPieces;
    Orientations piecesOrientations;

    placePiece(usedPieces, availablePieces, piecesOrientations);

    return 0;
}


void displayPiece(size_t piecePosition, const Sides &pieceOrientation) {
    char orientation = 'a' + pieceOrientation;
    cout << ++piecePosition << orientation << " ";
}

void displayPieces(const Pieces &TO_DISPLAY, const Orientations &PIECES_ORIENTATIONS) {
    for (size_t piecePosition = 0; piecePosition < TO_DISPLAY.size(); ++piecePosition) {

        // get the default position of the current piece to display
        // i.e. it's position in the default vector.
        Piece currentPiece = TO_DISPLAY.at(piecePosition);
        Sides currentPieceOrientation = PIECES_ORIENTATIONS.at(piecePosition);
        auto pieceDefault = find(PIECES.begin(), PIECES.end(), currentPiece);
        size_t pieceDefaultPosition = (size_t) distance(PIECES.begin(), pieceDefault);

        displayPiece(pieceDefaultPosition, currentPieceOrientation);
    }
    cout << endl;
}

bool pieceMatchesWithBoard(const Pieces &BOARD, const Orientations &orientations, const Piece &TO_INSERT) {

    // get the position @ which we want to insert a new piece
    size_t position = BOARD.size() - 1;

    // check if we're wanting to insert the very first piece
    if (position == 0) {
        // yes, then we don't need to check anything and can just insert it
        return true;
    }

    // get the orientation and the different attachements of the piece we want to insert
    Sides pieceToInsertOrientation = orientations.at(position);
    AttachementType pieceToInsertLeftAttachement = TO_INSERT.at((Sides::LEFT + pieceToInsertOrientation) % NB_SIDES);
    AttachementType pieceToInsertTopAttachement = TO_INSERT.at((Sides::UP + pieceToInsertOrientation) % NB_SIDES);

    // check if we're in the first row
    if (position < PIECE_BY_LINE) {

        // then we only need to check if we match with the piece on the left
        Piece leftPiece = BOARD.at(position - 1);
        Sides leftPieceOrientation = orientations.at(position - 1);
        AttachementType leftPieceRightAttachement = leftPiece.at((Sides::RIGHT + leftPieceOrientation) % NB_SIDES);

        return areMatchingPieces(leftPieceRightAttachement, pieceToInsertLeftAttachement);
    }

    // check if we're in the first col
    if (position % PIECE_BY_LINE == 0) {

        // then we only need to check if we match with the piece above the one we want to insert
        Piece topPiece = BOARD.at(position - PIECE_BY_LINE);
        Sides topPieceOrientation = orientations.at(position - PIECE_BY_LINE);
        AttachementType topPieceBottomttachement = topPiece.at((Sides::DOWN + topPieceOrientation) % NB_SIDES);


        return areMatchingPieces(topPieceBottomttachement, pieceToInsertTopAttachement);
    }

    // since we aren't in the first row or col, we need to check with the pieces that are on the left and above
    //      the piece we want to insert.
    Piece topPiece = BOARD.at(position - PIECE_BY_LINE);
    Piece leftPiece = BOARD.at(position - 1);

    Sides leftPieceOrientation = orientations.at(position - 1);
    Sides topPieceOrientation = orientations.at(position - PIECE_BY_LINE);

    AttachementType leftPieceAttachement = leftPiece.at((Sides::RIGHT + leftPieceOrientation) % NB_SIDES);
    AttachementType topPieceAttachement = topPiece.at((Sides::DOWN + topPieceOrientation) % NB_SIDES);


    return areMatchingPieces(leftPieceAttachement, pieceToInsertLeftAttachement) and
           areMatchingPieces(topPieceAttachement, pieceToInsertTopAttachement);
}

void placePiece(Pieces used, Pieces available, Orientations orientations) {

    // Check if all pieces are already in use
    if (available.empty()) {
        // yes, then a solution to the puzzle was found.
        displayPieces(used, orientations);
    } else {

        // loop through all the available pieces
        for (size_t pieceNb = 0; pieceNb < available.size(); ++pieceNb) {

            Piece current = available.at(pieceNb);
            auto currentIt = available.begin() + pieceNb;

            // Insert the current piece with a default UP orientation and remove it from the available pieces
            // since it's already in use
            used.push_back(current);
            orientations.push_back(Sides::UP);
            available.erase(currentIt);

            // test all sides of the current piece
            for (size_t side = 0; side < NB_SIDES; ++side) {

                // Check if the newly inserted piece matches with the board
                if (pieceMatchesWithBoard(used, orientations, current)) {
                    // yes, then we can insert a new piece
                    placePiece(used, available, orientations);
                }

                // Turn the piece that is currently being checked (last piece inserted)
                turnPiece(used.size() - 1, orientations);
            }

            // The piece didn't match with the currently present pieces. It can be put back within the available
            // pieces and removed from the used pieces and remove it's orientation.
            used.pop_back();
            orientations.pop_back();
            available.insert(currentIt, current);
        }
    }
}

bool areMatchingPieces(const AttachementType &fixedPiece, const AttachementType &testPiece) {
    // check if the attachements that are being compared are within the pieces type
    //  In the enum defined in pieces.h, there are to pieces that don't have any matching pieces
    //  and don't need to be compared.
    if (fixedPiece < 8 && testPiece < 8) {
        return MATCHING_ATTACHEMENT.at(testPiece) == fixedPiece;
    }
    return false;
}

void turnPiece(const size_t PIECE_POSITION, Orientations &piecesOrientations) {
    Sides orientation = piecesOrientations.at(PIECE_POSITION);
    Sides newOrientation = (orientation == (NB_SIDES - 1) ? (Sides) 0 : Sides(orientation + 1));
    piecesOrientations.at(PIECE_POSITION) = newOrientation;
}
