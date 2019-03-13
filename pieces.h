//
//  pieces.h
//  Puzzle récursif
//
//  Created by Olivier Cuisenaire on 06.11.18.
//  Copyright © 2018 Olivier Cuisenaire. All rights reserved.
//

#ifndef pieces_h
#define pieces_h

#include <array>
#include <vector>

enum AttachementType { FILLE_HAUT, FILLE_BAS, DAME_HAUT, DAME_BAS, ARROSOIR_GAUCHE, ARROSOIR_DROIT, GATEAU_GAUCHE, GATEAU_DROIT,  ARROSOIR_INVERSE, NONE };
enum Sides {UP, RIGHT, DOWN, LEFT};


using Piece         = std::array<AttachementType,4>;
using Pieces        = std::vector<Piece>;
using Orientations  = std::vector<Sides>;
using MatchingAttachement = std::array<AttachementType,10>;



extern const Pieces PIECES;

const unsigned NB_SIDES = 4;
const unsigned PIECE_BY_LINE = 3;

void displayPiece(size_t pieceNb, const Orientations& PIECES_ORIENTATIONS);

void displayPieces(const Pieces& PIECES, const Orientations& PIECES_ORIENTATIONS);

bool pieceMatchesWithBoard(const Pieces& BOARD, const Piece &TO_INSERT, size_t position);

void turnPiece(const size_t PIECE_NB, Orientations& piecesOrientations);

void placePiece(Pieces used, Pieces available, Orientations orientations);

bool areMatchingPieces(const AttachementType fixedPiece, const AttachementType testPiece);

#endif /* pieces_h */
