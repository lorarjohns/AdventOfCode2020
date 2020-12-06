//
// Created by Lora Johns on 12/6/20.
//

#ifndef AOC2020_DAYONE_H
#define AOC2020_DAYONE_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<long long> twoSum(string inputFile, int targetSum);
vector<int> subsetSumHelper(vector<int> nums, int numItems, int sumLeft, vector<int> numsSoFar, unordered_map<string, vector<int>> lookup);
vector<int> subsetSum(string inputFile, int targetSum);
void dayOneDemo();

#endif //AOC2020_DAYONE_H
