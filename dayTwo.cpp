//
// Created by Lora Johns on 12/6/20.
//

#include "dayTwo.h"
#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <ostream>
#include <fstream>

using namespace std;

vector<string> splitString(string str, string& pattern) {
    // regex re(delimiters);
    // remove(str.begin(), str.end(), ' ');
    // sregex_token_iterator first{str.begin(), str.end(), re, -1}, last;
    // vector<string> tokens{first, last};

    regex re(pattern);
    sregex_token_iterator begin(str.begin(), str.end(), re), end;
    vector<string> tokens{begin, end};

    return tokens;
}

int countOccurrences(string& str, string& c) {
   int count = 0;
   size_t pos = str.find(c, 0);

   while (pos != string::npos) {
       count++;
       pos = str.find(c, pos + 1);
   }
   return count;
}

bool meetsPartOneReqs(int letterCount, int lower, int upper) {
    return ((letterCount >= lower) && (letterCount <= upper));
}

bool meetsPartTwoReqs(string& password, char& c, int& firstPos, int& secondPos) {
    bool charAtFirstPos = containsCharAtPosition(password, c, firstPos);
    bool charAtSecondPos = containsCharAtPosition(password, c, secondPos);

    if (charAtFirstPos != charAtSecondPos) {
        return true;
    }
    return false;
}

int countValidPasswords(string& inputFile, int questionPart) {
    string tokenRegex = "[\\w-]+";

    ifstream file(inputFile);
    string line;

    int validPasswordCount = 0;

    while (getline(file, line)) {
        // tokenize line
        vector<string> tokens = splitString(line, tokenRegex);
        // get lower and upper bounds

        string boundsRegex = "[\\d]+";
        vector<string> bounds = splitString(tokens[0], boundsRegex);

        int lower = stoi(bounds[0]);
        int upper = stoi(bounds[1]);

        string letter = tokens[1];
        char c = letter[0];
        string password = tokens[2];

        int letterCount = countOccurrences(password, letter);
        if (questionPart == 1) {
            if (meetsPartOneReqs(letterCount, lower, upper)) {
            validPasswordCount++;
            }
        } else if (questionPart == 2) {
            if (meetsPartTwoReqs(password, c, lower, upper)) {
                validPasswordCount++;
            }
        }
    }
    return validPasswordCount;
}

bool containsCharAtPosition(string& str, char& c, int& pos) {
    pos -= 1; // this is 1-indexed

    if (str[pos] == c) {
        return true;
    }
    return false;
}


void dayTwoDemo() {
    string inputFile = "/Users/lorajohns/CLionProjects/AOC2020/data/input2.txt";
    int resultOne = countValidPasswords(inputFile, 1);
    cout << "day 2, part 1" << endl;
    cout << "Number of valid passwords: " << resultOne << endl;

    int resultTwo = countValidPasswords(inputFile, 2);
    cout << "day 2, part 2" << endl;
    cout << "Number of valid passwords: " << resultTwo <<endl;

}