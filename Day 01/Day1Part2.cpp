#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// uh oh i haven't programmed in c++ since last advent of code
// fucking math major

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    

    vector<int> list1;
    vector<int> list2;

    // format into the two lists
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;
                int end1 = line.find_first_of(" ");
                int start2 = line.find_last_of(" ");
                list1.push_back(stoi(line.substr(0, end1)));
                list2.push_back(stoi(line.substr(start2+1)));
        }
    }

    // add to total each number in list 1 * number of occurences in list 2
    int size = list1.size();
    for(int i = 0; i < size; ++i) {
        int curr = list1[i];
        sum += curr * count(list2.begin(), list2.end(), curr);
    }

    cout << "Similarity score: " << sum << endl;

    return 0;
}