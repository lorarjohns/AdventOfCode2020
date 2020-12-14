//
// Created by Lora Johns on 12/6/20.
//

#include "aoc2020.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/**
 * Read numbers from an input file into a vector.
 * @param inputFile (string): filepath to input.
 * @return vector<int>: vector of integers from the input file.
 */
vector<int> getInput(string inputFile) {
    ifstream file(inputFile);
    vector<int> input;
    for (int x; file >> x;) {
        input.push_back(x);
    }
    return input;
}

