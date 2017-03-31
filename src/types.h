#pragma once
#include <assert.h>
#define __STDC_FORMAT_MACROS  // C++
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <chrono>

extern bool Chess960;

extern int64_t dbgCnt[2];

#define BOUNDS(v, ub) assert(unsigned(v) < ub)

enum {WHITE, BLACK, NB_COLOR};
enum {KNIGHT, BISHOP, ROOK, QUEEN, KING, PAWN, NB_PIECE};

inline int opposite(int c) { return c ^ BLACK; }

enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, NB_RANK};
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, NB_FILE};
enum {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    NB_SQUARE
};

int rank_of(int s);
int file_of(int s);
int relative_rank(int c, int r);
int relative_rank_of(int c, int s);
int square(int r, int f);

std::string square_to_string(int s);
int string_to_square(const std::string& s);

/* Directions */

enum {UP = 8, DOWN = -8, LEFT = -1, RIGHT = 1};

int push_inc(int c);    // pawn push increment

/* Material values */

enum {
    OP = 158, EP = 200, P = (OP+EP)/2,
    N = 640, B = 640,
    R = 1046, Q = 1980
};

/* Eval */

enum {OPENING, ENDGAME, NB_PHASE};

/*#ifdef __clang__
typedef int eval_t __attribute__ (( ext_vector_type(2) ));
#else
typedef int eval_t __attribute__ (( vector_size(8) ));
#endif*/

struct eval_t {
    int op, eg;

    operator bool() const { return op || eg; }
    bool operator==(eval_t e) const { return op == e.op && eg == e.eg; }
    bool operator!=(eval_t e) const { return !(*this == e); }

    eval_t operator+(eval_t e) const { return {op + e.op, eg + e.eg}; }
    eval_t operator-(eval_t e) const { return {op - e.op, eg - e.eg}; }
    eval_t operator*(int x) const { return {op * x, eg * x}; }
    eval_t operator/(int x) const { return {op / x, eg / x}; }

    eval_t& operator+=(eval_t e) { return op += e.op, eg += e.eg, *this; }
    eval_t& operator-=(eval_t e) { return op -= e.op, eg -= e.eg, *this; }
    eval_t& operator*=(int x) { return op *= x, eg *= x, *this; }
    eval_t& operator/=(int x) { return op /= x, eg /= x, *this; }
};

extern const eval_t Material[NB_PIECE];

#define INF    32767
#define MATE    32000
#define MAX_DEPTH    127
#define MIN_DEPTH    -8
#define MAX_PLY        (MAX_DEPTH - MIN_DEPTH + 2)
#define MAX_GAME_PLY    1024

/* Clock */

class Clock {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
    void reset();
    std::chrono::milliseconds::rep elapsed();
};

bool score_ok(int score);
bool is_mate_score(int score);
int mated_in(int ply);
int mate_in(int ply);

/* Display */

extern const std::string PieceLabel[NB_COLOR];
