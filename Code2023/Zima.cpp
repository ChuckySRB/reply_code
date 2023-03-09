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