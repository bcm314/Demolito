/*
 * Demolito, a UCI chess engine.
 * Copyright 2015 lucasart.
 *
 * Demolito is free software: you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Demolito is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program. If
 * not, see <http://www.gnu.org/licenses/>.
*/
#include "pst.h"
#include "tune.h"

const eval_t Material[NB_PIECE] = {{N, N}, {B, B}, {R, R}, {Q, Q}, {0, 0}, {OP, EP}};

eval_t pst[NB_COLOR][NB_PIECE][NB_SQUARE];

void eval_add(eval_t *e1, eval_t e2)
{
    e1->op += e2.op;
    e1->eg += e2.eg;
}

void eval_sub(eval_t *e1, eval_t e2)
{
    e1->op -= e2.op;
    e1->eg -= e2.eg;
}

void __attribute__((constructor)) pst_init()
{
    for (int color = WHITE; color <= BLACK; color++)
        for (int piece = KNIGHT; piece < NB_PIECE; piece++)
            for (int square = A1; square <= H8; square++) {
                const int file = file_of(square), file4 = file > FILE_D ? FILE_H - file : file;

                pst[color][piece][square] = Material[piece];
                eval_add(&pst[color][piece][square], pstSeed[piece][relative_rank_of(color, square)][file4]);

                if (color == BLACK) {
                    pst[color][piece][square].op *= -1;
                    pst[color][piece][square].eg *= -1;
                }
            }
}
