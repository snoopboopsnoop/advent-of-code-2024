#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

// bad day :(

// returns number of matched "XMAS" or "SAMX" in given string
int getMatches(const string& line) {
    smatch match;
    regex r("XMAS|SAMX");
    int sum = 0;

    string::const_iterator searchStart(line.begin());
    while(regex_search(searchStart, line.end(), match, r)) {
        sum++;
        searchStart = match.suffix().first - 1;
    }

    return sum;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;

    vector<string> wordsearch; // holds rows
    vector<string> columns; // holds columns
    vector<string> diagonals; // holds diagonals

    // insert input into 2d vector
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;
            wordsearch.push_back(line);
        }
    }

    // get columns into lines vector
    int colnum = wordsearch[0].size();
    int rownum = wordsearch.size();

    for(int i = 0; i < colnum; i++) {
        string temp;
        for(int j = 0; j < rownum; ++j) {
            temp.push_back(wordsearch[j][i]);
        }
        columns.push_back(temp);

        int currCol = i;
        int currRow = 0;

        temp.clear();
        
        while(currCol < colnum && currRow < rownum) {
            temp.push_back(wordsearch[currRow][currCol]);
            currRow++;
            currCol++;
        }

        diagonals.push_back(temp);

        currCol = i;
        currRow = 0;

        temp.clear();
        while(currCol >= 0 && currRow < rownum) {
            temp.push_back(wordsearch[currRow][currCol]);
            currRow++;
            currCol--;
        }

        diagonals.push_back(temp);
    }

    for(int i = 1; i < rownum; i++) {
        string temp;

        int currCol = 0;
        int currRow = i;

        temp.clear();
        while(currCol < colnum && currRow < rownum) {
            temp.push_back(wordsearch[currRow][currCol]);
            currRow++;
            currCol++;
        }

        diagonals.push_back(temp);

        currCol = colnum-1;
        currRow = i;

        temp.clear();

        while(currCol >= 0 && currRow < rownum) {
            temp.push_back(wordsearch[currRow][currCol]);
            currRow++;
            currCol--;
        }

        diagonals.push_back(temp);
    }

    // get all row matches
    for(const string& i : wordsearch) {
        sum += getMatches(i);
    }

    int rowMatches = sum;
    cout << rowMatches << " matches found in the rows" << endl;

    // get all column matches
    for(const string& i : columns) {
        sum += getMatches(i);
    }

    int colMatches = sum - rowMatches;
    cout << colMatches << " matches found in the columns" << endl;

    // get all diagonal matches
    for(const string& i : diagonals) {
        sum += getMatches(i);
    }

    int diagMatches = sum - colMatches - rowMatches;
    cout << diagMatches << " matches found in the diagonals" << endl;

    cout << "Total: " << sum << " matches" << endl;

    return 0;
}