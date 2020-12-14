//
// Created by Lora Johns on 12/6/20.
//

#include "dayFour.h"
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <regex>
#include <unordered_map>

using namespace std;

/**
 * assumes file ends with a newline
 * @param inputFile
 * @return
 */
vector<string> readFile(string inputFile) {
    ifstream file(inputFile);
    vector<string> strings;

    while (!file.eof()) {

        string line;
        getline(file, line);

        strings.push_back(line);
    }
    return strings;
}

vector<vector<string>> splitRecords(vector<string> strings) {
    vector<vector<string>> records;
    vector<string> record;

    for (string s: strings) {
        if (!s.empty()) {
            record.push_back(s);
        } else {
            records.push_back(record);
            record.clear();
        }
    }
    return records;
}

/**
 * given a regular expression, split a string
 * @param str (string): string to split
 * @param delimiters (string&): regular expression to use to split the string into tokens
 * @return vector<string>: tokens
 */
vector<string> splitByDelimiters(string str, string& delimiters) {
    regex re(delimiters);
    // remove(str.begin(), str.end(), ' ');
    sregex_token_iterator first{str.begin(), str.end(), re, -1}, last;
    vector<string> tokens{first, last};

    return tokens;
}

/**
 *
 * @param record (vector<string>): strings of key::value pairs delimited by ":"
 * @return unordered_map<string, string>: mapping from keys to values
 */
unordered_map<string, string> recordToMap(vector<string> record) {

    string itemDelim = "[\\s ]";
    string keyValDelim = "[:]";

    unordered_map<string, string> map {};

    for (string s: record) {

        vector<string> keyValuePairs = splitByDelimiters(s, itemDelim);
        for (string i: keyValuePairs) {
            vector<string> keyValue = splitByDelimiters(i, keyValDelim);
            map[keyValue[0]] = keyValue[1];
        }
    }

    return map;
}

/**
 *
 * @param record unordered map of field::value pairs
 * @return set<string>: keys of the record
 */
set<string> getKeys(unordered_map<string, string> record) {
    set<string> keys {};
    for (pair<string, string> elem: record) {

        keys.emplace(elem.first);
        // string key = elem.first;
        // string val = elem.second;
    }
    return keys;
}

/**
 * (assumes that rec is a subset of fields)
 * @param rec
 * @return
 */
bool hasValidKeys(set<string> keys, bool excludeCid) {

    set<string> fields = {"byr", // (Birth Year)
                          "iyr", // (Issue Year)
                          "eyr", // (Expiration Year)
                          "hgt", // (Height)
                          "hcl", // (Hair Color)
                          "ecl", // (Eye Color)
                          "pid", // (Passport ID)
                          "cid" // (Country ID)
    };

    bool isValid = false;

    set<string> diff {};
    set_difference(fields.begin(), fields.end(), keys.begin(), keys.end(), inserter(diff, diff.end()));
    if (diff.size() == 0) {
        isValid = true;
    } else if (diff.size() > 1) {
        isValid = false;
    } else if ((diff.find("cid") != diff.end()) && excludeCid) {
        isValid = true;
    }

    return isValid;
}


/**
 * validate regex based fields on exact matching (hcl, pid)
 * @param val
 * @param expr
 * @return
 */
bool validateRegex(string val, string expr) {
    regex re(expr);
    return regex_match(val, re);
}

bool validateHgt(string val) {
    string expr = "(\\d+)(cm|in)";
    regex re(expr);

    smatch matches;

    regex_search(val, matches, re);

    // value is not valid if regex does not match
    if (matches.size() == 0) {
        return false;
    } else {
        // return true if 59-76 inches or 150-193 cm
        sub_match units = matches[matches.size()-1];
        int measure = stoi(matches.str(1));

        if (units.compare("in") == 0) {
            if ((measure >= 59) && (measure <= 76)) {
                return true;
            }
        } else if (units.compare("cm") == 0) {
            if ((measure >= 150) && (measure <= 193)) {
                return true;
            }
        }
        // else return false
        return false;
    }
}

bool validateEcl(string val) {
    set<string> colors = {"amb",
                          "blu",
                          "brn",
                          "gry",
                          "grn",
                          "hzl",
                          "oth"};
    if (colors.find(val) != colors.end()) {
        return true;
    }
    return false;
}

/**
 * validate year-range based fields (byr, iyr, eyr)
 * @param val
 * @param lower
 * @param upper
 * @return
 */
bool validateYear(int val, int lower, int upper) {
    if ((val >= lower) && (val <= upper)) {
        return true;
    }
    return false;
}



bool hasValidValues(unordered_map<string, string> rec) {
    for (pair<string, string> elem: rec) {
        string key = elem.first;
        string val = elem.second;

        if (key =="byr") {
            if (!validateYear(stoi(val), 1920, 2002)) {
                return false;
            }
        } else if (key == "iyr") {
             if (!validateYear(stoi(val), 2010, 2020)) {
                 return false;
             }
        } else if (key == "eyr") {
            if (!validateYear(stoi(val), 2020, 2030)) {
                return false;
            }
        } else if (key == "hgt") {
            if (!validateHgt(val)) {
                return false;
            }
        } else if (key == "hcl") {
            if (!validateRegex(val, "#[0-9a-f]{6}")) {
                return false;
            }
        } else if (key == "ecl") {
            if (!validateEcl(val)) {
                return false;
            }
        } else if (key == "pid") {
            if (!validateRegex(val, "\\d{9,9}")) {
                return false;
            }
        }
    }
    return true;
}

bool isValidRecord(unordered_map<string, string> rec, bool checkValues) {
    set<string> keys = getKeys(rec);
    if (hasValidKeys(keys, true)) {
        if (checkValues) {
            if (hasValidValues(rec)) {
                return true;
            } else {
                return false;
            }
        }
        return true;
    }
    return false;
}


int validateRecords(string inputFile, bool checkValues) {
    int numValid = 0;

    vector<string> strings = readFile(inputFile);
    vector<vector<string>> records = splitRecords(strings);

    vector<unordered_map<string, string>> maps {};

    for (vector<string> rec: records) {
        maps.push_back(recordToMap(rec));
    }

    for (unordered_map<string, string> rec: maps) {
        if (isValidRecord(rec, checkValues)) {
            numValid++;
        }
    }
    return numValid;
}



void dayFourDemo() {
    string inputFile = "/Users/lorajohns/CLionProjects/AOC2020/data/input4.txt";
    int numValid = validateRecords(inputFile, false);

    cout << "day 4 part 1" << endl;
    cout << "Number of valid records: " << numValid << endl;

//    vector<string> pidVec = {"000000001", "0123456789"};

//    for (string s: pidVec) {
//        string expr = "\\d{9,9}";
//        cout << validateRegex(s, expr) << endl;
//    }

//    vector<string> hclVec = {"#123abc", "#123abz", "#1f9c3c", "123abc"};
//    for (string s: hclVec) {
//        string expr = "#[0-9a-f]{6}";
//        cout << validateRegex(s, expr) << endl;
//    }

//    cout << validateHgt("cm160");
//    cout << validateHgt("70in");
//    cout << validateHgt("170cm");

    int numValidVals = validateRecords(inputFile, true);
    cout << "day 4 part 2" << endl;
    cout << "Number of valid records: " << numValidVals << endl;
}