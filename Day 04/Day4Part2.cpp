#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// bad day :(

// returns positions of 'A' in any matches of 'MAS' or 'SAM' in given string
vector<int> getMas(const string& line) {
    vector<int> result;

    int pos = line.find("MAS");
    while(pos != string::npos) {
        result.push_back(pos + 1);
        pos = line.find("MAS", pos+1);
    }

    pos = line.find("SAM");
    while(pos != string::npos) {
        result.push_back(pos + 1);
        pos = line.find("SAM", pos+1);
    }

    return result;
} 

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;

    vector<string> wordsearch;
    vector<pair<int, int>> matches;

    // insert input into 2d vector
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;
            wordsearch.push_back(line);
        }
    }

    int colnum = wordsearch[0].size();
    int rownum = wordsearch.size();

    // check diagonals along columns
    for(int i = 0; i < colnum; i++) {
        int currCol = i;
        int currRow = 0;

        string temp;
        
        while(currCol < colnum && currRow < rownum) {
            temp.push_back(wordsearch[currRow][currCol]);
            currRow++;
            currCol++;
        }

        // checks all \ diagonals (starting from column)
        vector<int> result = getMas(temp);
        for(int pos : result) {
            pair<int, int> match = make_pair(pos, pos+i);
            if(find(matches.begin(), matches.end(), match) == matches.end()) {
                matches.push_back(match);
            }
            else {
                cout << "found x at (" << pos << ", " << pos + i << ")" << endl;
                sum++;
            }
        }

        currCol = i;
        currRow = 0;

        temp.clear();
        while(currCol >= 0 && currRow < rownum) {
            temp.push_back(wordsearch[currRow][currCol]);
            currRow++;
            currCol--;
        }

        // checks all / diagonals (starting from column)
        result = getMas(temp);
        for(int pos : result) {
            pair<int, int> match = make_pair(pos, i - pos);
            if(find(matches.begin(), matches.end(), match) == matches.end()) {
                matches.push_back(match);
            }
            else {
                cout << "found x at (" << pos << ", " << i - pos << ")" << endl;
                sum++;
            }
        }
    }

    // check diagonals along rows
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

        // checks all \ diagonals (starting from row)
        vector<int> result = getMas(temp);
        for(int pos : result) {
            pair<int, int> match = make_pair(pos + i, pos);
            if(find(matches.begin(), matches.end(), match) == matches.end()) {
                matches.push_back(match);
            }
            else {
                cout << "found x at (" << pos+i << ", " << pos << ")" << endl;
                sum++;
            }
        }

        currCol = colnum-1;
        currRow = i;

        temp.clear();

        while(currCol >= 0 && currRow < rownum) {
            temp.push_back(wordsearch[currRow][currCol]);
            currRow++;
            currCol--;
        }

        // checks all / diagonals (starting from row)
        result = getMas(temp);
        for(int pos : result) {
            pair<int, int> match = make_pair(pos + i, colnum - pos - 1);

            if(find(matches.begin(), matches.end(), match) == matches.end()) {
                matches.push_back(match);
            }
            else {
                cout << "found x at (" << pos + i << ", " << colnum - pos - 1 << ")" << endl;
                sum++;
            }
        }
    }

    cout << endl << "Number of Xs: " << sum << endl;

    return 0;
}