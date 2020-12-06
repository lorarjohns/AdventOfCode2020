//
// Created by Lora Johns on 12/6/20.
// Advent of Code Day 1 https://adventofcode.com/2020/day/1
//

#include "dayOne.h"
#include "aoc2020.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

/**
 * Find two numbers in the input that sum to the target and return their product.
 * @param inputFile (string): filepath to input.
 * @return vector<long long>: vector of products of numbers that sum to the target.
 */
vector<long long> twoSum(string inputFile, int targetSum) {
    vector<int> input = getInput(inputFile);
    sort(input.begin(),  input.end());
    unique(input.begin(), input.end());

    int i = 0;
    int j = input.size() - 1;

    vector<long long> answers {};

    while (i < j) {

        if (input[i] + input[j] == targetSum) {
            cout << "Found pair: " << input[i] << " + " << input[j] << " = 2020" << "\n";

            answers.push_back(input[i] * input[j]);
            j--;
            i++;
        } else if (input[i] + input[j] > targetSum) {
            // if input[i] + input[j] > target, decrement j
            j--;
        } else {
            // if input[i] + input[j] < target, increment i
            i++;
        }
    }
    return answers;

}


vector<int> subsetSumHelper(vector<int> nums, int numItems, int sumLeft, vector<int> numsSoFar, unordered_map<string, vector<int>> lookup) {
    if (sumLeft == 0) {
        // subset found
        return numsSoFar;
    }

    // base case: if no items left or sum goes negative
    if (numItems < 0 || sumLeft < 0) {
        return {};
    }

    // build a map key
    string key = to_string(numItems) + "-" + to_string(sumLeft);

    // if this is the first time we've seen this, store it
    if (lookup.find(key) == lookup.end()) {
        // Case 1: include the current item in the subset
        // recurse for (n - 1) items with remaining sum (sum - nums[i])
        vector<int> numsPlusCurrent = numsSoFar;
        numsPlusCurrent.push_back(nums[numItems]);
        vector<int> includeCurrent = subsetSumHelper(nums, numItems - 1, sumLeft - nums[numItems], numsPlusCurrent, lookup);

        // Case 2: exclude the current item
        // recurse for (n - 1) items with remaining sum
        vector<int> excludeCurrent = subsetSumHelper(nums, numItems - 1, sumLeft, numsSoFar, lookup);

        if (includeCurrent.size() > 0) {
            lookup[key] = includeCurrent;
        } else if (excludeCurrent.size() > 0) {
            lookup[key] = excludeCurrent;
        } else {
            lookup[key] = {};
        }
    }
    // return solution to current subproblem
    return lookup[key];
}
vector<int> subsetSum(string inputFile, int targetSum) {
    vector<int> nums = getInput(inputFile);
    unordered_map<string, vector<int>> lookup {};
    vector<int> numsSoFar {};

    return subsetSumHelper(nums, nums.size() - 1, targetSum, numsSoFar, lookup);
}

void dayOneDemo() {
    // part one
    vector<long long> answers {};
    int targetSum = 2020;
    string inputFile = "/Users/lorajohns/AdventOfCode/data/input1.1.txt";

    cout << "Part 1 Answer" << endl;
    answers = twoSum(inputFile, targetSum);
    for (long long x: answers) {
        cout << "Product: " << x << "\n";
    }

    // part two
    cout << "Part 2 Answer" << endl;
    vector<int> subset = subsetSum(inputFile, targetSum);
    if (subset.size() > 0) {
        long long product = 1;
        cout << "Subset exists" << endl;
        cout << "{";

        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            product *= subset[i];

            if (i < subset.size() - 1) {
                cout << ", ";
            }
        }
        cout << "} \n" << endl;
        cout << "Product: " << product << endl;
    } else {
        cout << "No subset exists" << endl;
    }
}