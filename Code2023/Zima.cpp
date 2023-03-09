#include "Zima.hpp"
#include <fstream>
#include <iostream>

using namespace std;

bool file_input(const char* file_name) {

    ifstream inputFile(file_name);

    // Make sure the file was opened successfully
    if (!inputFile) {
        cout << "Error: Unable to open file.\n";
        return 1;
    }

    // Read the file line by line
    
    int* Pandora = new int[5];

    for (int i = 0; i < 5; i++) {
        inputFile >> Pandora[i];
    }

    // Close the file
    inputFile.close();

    return 0;
}