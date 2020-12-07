//
// Created by Lora Johns on 12/6/20.
// Advent of Code Day 3.
// https://adventofcode.com/2020/day/3
//

#ifndef AOC2020_DAYTHREE_H
#define AOC2020_DAYTHREE_H
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct GridLocation {
public:
    GridLocation(int row = 0, int col = 0);
    int row;
    int col;
};

GridLocation getNextLocation(GridLocation currentLocation, int maxCol);
bool isTree(GridLocation loc, vector<string>& map);

vector<string> buildMap(string inputFile);
int traverseGridForTrees(string inputFile);
void dayThreeDemo();

#endif //AOC2020_DAYTHREE_H
