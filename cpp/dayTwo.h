//
// Created by Lora Johns on 12/6/20.
// Advent of Code Day 2
// https://adventofcode.com/2020/day/2
//

#ifndef AOC2020_DAYTWO_H
#define AOC2020_DAYTWO_H

#include <string>
using namespace std;

vector<string> splitString(string str, string &pattern);
int countValidPasswords(string& inputFile, int questionPart);
int countOccurrences(string& str, string& substring);
void dayTwoDemo();
bool meetsPartOneReqs(int letterCount, int lower, int upper);
bool containsCharAtPosition(string& str, char& c, int& pos);
bool meetsPartTwoReqs(string& password, char& c, int& firstPos, int& secondPos);
#endif //AOC2020_DAYTWO_H
