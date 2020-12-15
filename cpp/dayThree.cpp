//
// Created by Lora Johns on 12/6/20.
//

#include "dayThree.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
vector<string> buildMap(string inputFile) {
    ifstream file(inputFile);
    vector<string> map;
    while(!file.eof()) {
        string line;
        file >> line;
        if (line.length() > 0) {
            map.push_back(line);
        }
    }
    return map;
}

GridLocation::GridLocation(int row, int col) {
    this->row = row;
    this->col = col;
}

bool isTree(GridLocation loc, vector<string>& map) {
    string c = map[loc.row].substr(loc.col, 1);
    if (c == "#") {
        return true;
    }
    return false;
}

GridLocation getNextLocation(GridLocation currentLocation, int maxCol, GridLocation tobogganStep) {
    // the toboggan goes right three and down 1.
    // to advance, add 3 to current col and add
    // 1 to current row.

    int nextRow = currentLocation.row + tobogganStep.row;
    int nextCol = (currentLocation.col + tobogganStep.col) % maxCol;

    return GridLocation(nextRow, nextCol);

}
int traverseGridForTrees(string inputFile, GridLocation tobogganStep) {
    vector<string> map = buildMap(inputFile);

    // get map size
    int numRows = map.size(); // 323
    int numCols = map[0].length(); // 31

    // define start location and exit
    GridLocation startLocation = {0, 0};
    GridLocation endLocation = {numRows - 1, numCols - 1};

    // cout << "End loc: (" << endLocation.row << ", " << endLocation.col << ")" << endl;

    // define a placeholder for the current step
    // and a variable to count trees
    GridLocation currentLocation = startLocation;
    int treeCount = 0;

    while ((currentLocation.row < numRows) && (currentLocation.col < numCols)) {
        // cout << "current: (" << currentLocation.row << ", " << currentLocation.col << ")" << endl;
        // check this location
        if (isTree(currentLocation, map)) {
            // cout << "tree found" << endl;
            treeCount++;
        }
        // go to the next location
        GridLocation nextLocation = getNextLocation(currentLocation, numCols, tobogganStep);
        currentLocation = nextLocation;
    }
    return treeCount;
}

long long productOfForest(string inputFile, vector<GridLocation> listOfSlopes) {
    long long product = 1;
    for (GridLocation tobogganStep: listOfSlopes) {
        int treeCount = traverseGridForTrees(inputFile, tobogganStep);
        product *= treeCount;
    }
    return product;
}

void dayThreeDemo() {
    string testFile = "/Users/lorajohns/CLionProjects/AOC2020/data/test3.2.txt";
    string inputFile = "/Users/lorajohns/CLionProjects/AOC2020/data/input3.txt";

    GridLocation tobogganStep = {1, 3};

    int numTrees = traverseGridForTrees(inputFile, tobogganStep);
    cout << "day 3, part 1" << endl;
    cout << "Number of trees: " << numTrees << endl;

    cout << "day 3, part 2" << endl;
    vector<GridLocation> slopes = {
            GridLocation(1, 1),
            GridLocation(1, 3),
            GridLocation(1, 5),
            GridLocation(1, 7),
            GridLocation(2, 1)
    };

    long long forestCount = productOfForest(inputFile, slopes);
    cout << "Product: " << forestCount << endl;

}
