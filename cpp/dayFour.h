//
// Created by Lora Johns on 12/6/20.
//

#ifndef AOC2020_DAYFOUR_H
#define AOC2020_DAYFOUR_H
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;
void dayFourDemo();
vector<string> readFile(string inputFile);
vector<vector<string>> splitRecords(vector<string> strings);
vector<string> splitByDelimiters(string str, string& delimiters);
unordered_map<string, string> recordToMap(vector<string> record);
set<string> getKeys(unordered_map<string, string> record);
bool isValidRecord(unordered_map<string, string> rec, bool excludeCid);
int validateRecords(string inputFile);

#endif //AOC2020_DAYFOUR_H
