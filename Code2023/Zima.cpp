#include "Zima.hpp"
#include <fstream>
#include <iostream>

using namespace std;






map* file_input(const char* file_name) {

    ifstream inputFile(file_name);

    // Make sure the file was opened successfully
    if (!inputFile) {
        cout << "Error: Unable to open file.\n";
        return nullptr;
    }

    // Read the file line by line
    
    map* novaMapa = new map;
  
 
    inputFile >> novaMapa->C >> novaMapa->R >> novaMapa->S;
    novaMapa->Snakes = new int[novaMapa->S];
    char c;
    for (int i = 0; i < novaMapa->S; i++) {
        inputFile >> novaMapa->Snakes[i];
    }
    novaMapa->Grid = new int*[novaMapa->R];
    novaMapa->WormholeGrid = new int* [novaMapa->R];
    novaMapa->Wormholes = new coord [novaMapa->R * novaMapa->C];

    novaMapa->W = 0;
  

    for(int i = 0; i < novaMapa->R; i++) {
        novaMapa->Grid[i] = new int[novaMapa->C];
        novaMapa->WormholeGrid[i] = new int[novaMapa->C];
        for (int j = 0; j < novaMapa->C; j++) {
            inputFile >> c;
            if (c == '*') {
                novaMapa->Grid[i][j] = 0;
                novaMapa->WormholeGrid[i][j] = 1;
                novaMapa->Wormholes[novaMapa->W] = {i, j};
                novaMapa->W++;
            }
            else {
                novaMapa->Grid[i][j] = c - 48;
                novaMapa->WormholeGrid[i][j] = 0;
            }
        }
    }

    // Close the file
    inputFile.close();

    cout << "Ide gas" << endl;
    return novaMapa;
}

void ispis_matrice(map* Mapa) {
    for (int i = 0; i < Mapa->R; i++) {
        for (int j = 0; j < Mapa->C; j++) {
            cout << Mapa->Grid[i][j] << " ";
        }
        cout << endl;
    }
}

/*
typedef struct Map {
    int C, R;
    int** Grid;
    int W, S;
    int** WormholeGrid;
    coord* Wormholes;
    int* Snakes;
}map;*/

result* stavi_zmije(map* Mapa, coord* pozicije) {
    result* R = new result;
    R->score = 0;
    for (int i = 0; i < Mapa->S; i++) {
        Mapa->WormholeGrid[pozicije[i].X][pozicije[i].Y] = -1;
        Mapa->Snakes[i]--;
        R->score += Mapa->Grid[pozicije[i].X][pozicije[i].Y];
    }

    return R;
}

void zaharije(map* Mapa, coord* pozicije) {

    coord* next_best = new coord[Mapa->S];
    int* value_best = new int[Mapa->S];
    bool* alive = new bool[Mapa->S];
    bool* moved = new bool[Mapa->S];

    //fnext_best = filip();
    int cur_l = 0;
    int v_best, i_best;
    for (int i = 0; i < Mapa->S; i++) {
        alive[i] = 1;
        moved[i] = 0;
       // next_best[i] = filip(Mapa, pozicija[i]);
        value_best[i] = Mapa->Grid[next_best[i].X][next_best[i].Y];
        if (i == 0) {
            v_best = value_best[i];
            i_best = 0;
        }
        else if (value_best[i] > v_best) {
            v_best = value_best[i];
            i_best = i;
        }
    }

    bool loop = true;

    while (loop) {
        bool loop = false;
        while (cur_l < Mapa->S) {
            if (Mapa->Snakes[cur_l] > 0) {
                loop = true;
                
            }
            cur_l++;
        }
    }
    


}


