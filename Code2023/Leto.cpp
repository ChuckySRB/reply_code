#include "Leto.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void writeOutput(string filename, vector<vector<string>> steps) {
    ofstream outp_file;
    outp_file.open(filename);
    for (int i = 0; i < steps.size(); i++) {
        for (int j = 0; j < steps[i].size(); j++) {
            outp_file << steps[i][j];
            if (j != steps[i].size() - 1) outp_file << " ";
        } outp_file << endl;
    }
}

vector<int> snakes_scheduler(vector<int> snakes) {
    sort(snakes.begin(), snakes.end());
    vector <int> ret;
    int prev = 0;
    for (auto s : snakes) {
        ret.push_back(s - prev);
        prev = s;
    }
    return ret;