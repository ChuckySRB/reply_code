#pragma once
typedef struct Coordinate {
    int X, Y;
}coord;

typedef struct Map {
    int C, R;
    int** Grid;
    int W, S;
    int** WormholeGrid;
    coord* Wormholes;
    int* Snakes;
}map;
map* file_input(const char* file_name);