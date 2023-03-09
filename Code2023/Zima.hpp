#pragma once
#include <vector>

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

typedef struct Result {
    long long score;
    vector<vector<string>> steps;
}result;

map* file_input(const char* file_name);
void ispis_matrice(map* Mapa);
result* stavi_zmije(map* Mapa, coord* pozicije);