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

    // sort
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    // add the distances between list items to total sum
    int size = list1.size();
    for(int i = 0; i < size; ++i) {
        sum += abs(list1[i] - list2[i]);
    }

    cout << "Total distance between lists: " << sum << endl;

    return 0;
}