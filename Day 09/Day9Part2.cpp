#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;

// programmer hell

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    unsigned long long sum = 0;

    // note for each index i the order is files[i] followed by gaps[i]
    vector<pair<int, int>> files; // <ID, length>
    vector<int> gaps; // length of gaps
    map<int, int> nextGap; // map of gap size -> closest pos (from left)

    getline(in, line);
    size_t size = line.size();

    // fill files, gaps, nextGap
    for(int i = 0; i < size; ++i) {
        if(i % 2 == 0) { // even indexes are files
            files.push_back(make_pair(i / 2, line[i] - '0'));
        }
        else { // odds are gaps
            int gapSize = line[i] - '0';
            gaps.push_back(gapSize);
            if(gapSize != 0) { // uniqueness of map elements keeps only leftmost gaps of length in nextGap
                nextGap.insert(make_pair(gapSize, i / 2));
            }
        }
    }

    // // Comment/Uncomment to print sorting (debug)
    // for(int j = 0; j < files.size(); ++j) {
    //     const pair<int, int>& p = files[j];
    //     cout << "[";
    //     for(int i = 0; i < p.second; ++i) {
    //         cout << p.first;
    //     }
    //     cout << "]";
    //     if(j < gaps.size()) {
    //         int gap = gaps[j];
    //         for(int i = 0; i < gap; ++i) {
    //             cout << ".";
    //         }
    //         if(gap == 0) {
    //             cout << "_";
    //         }
    //     }
    // }
    // cout << endl;

    auto it = files.end() - 1; // use iterator to go through files
    int currID = it->first; // current ID of file to look at

    while(it >= files.begin() && currID >= 0) {
        // ignore already moved files
        if(it->first > currID) {
            --it;
            continue;
        }

        // get position of first open gap
        auto gap = min_element(nextGap.begin(), nextGap.end(), [it](const pair<int, int>& a, const pair<int, int>& b) {
            if(a.first < it->second) return false;
            else if(b.first < it->second) return true;
            else return a.second < b.second;
        });

        // if valid gap found
        if(gap->first >= it->second && gap->second < it - files.begin()) {
            int pos = gap->second;

            // open gap for file
            gaps[pos] = 0; // no gap between files on the left
            int diff = gap->first - it->second;
            gaps.insert(gaps.begin() + pos + 1, diff); // leftover gap on the right

            // we inserted a gap so all positions in nextGap past pos have to be incremented
            auto nextIt = nextGap.begin();
            while(nextIt != nextGap.end()) {
                if(nextIt->second >= pos + 1)
                nextIt->second += 1;
                nextIt++;
            }

            // refresh nextGap
            auto newGap = find(gaps.begin(), gaps.end(), gap->first); // replace used gap with next open one
            if(newGap != gaps.end()) {
                gap->second = newGap - gaps.begin();
            }
            else { // erase open gap if no more gaps of correct length
                nextGap.erase(gap);
            }

            if(diff != 0) { // handle the possibility of diff being the new closest gap of length diff
                auto gapDiff = nextGap.find(diff);
                if(gapDiff == nextGap.end() || gapDiff->second >= pos + 1) { // diff is new closest
                    nextGap[diff] = pos + 1;
                }
            }

            // replace moved file with gap
            auto gapIt = gaps.begin() + (it - files.begin()); // gap before moved file
            // gapIt will change after file's gap is added so handle if gapIt is referenced in nextGap
            if(nextGap.find(*gapIt) != nextGap.end() && nextGap[*gapIt] == gapIt - gaps.begin()) { 
                nextGap.erase(*gapIt); // we've iterated past gapIt so who cares if its the closest gap of its length
            }
            if(gapIt + 1 < gaps.end()) { // gap after moved file (if statement handles moving file at end of disk)
                if(nextGap.find(*(gapIt + 1)) != nextGap.end() && nextGap[*(gapIt + 1)] == (gapIt + 1) - gaps.begin()) {
                    nextGap.erase(*(gapIt+1)); // same handling as above but for gapIt + 1
                }

                // combine gap before file, length of file, and gap after file into 1 gap
                *gapIt += it->second + *(gapIt + 1);
                gaps.erase(gapIt + 1);
            }
            else { // if no gap after file then just combined gap before file + length of file
                *gapIt += it->second;
            }

            // insert file at pos + 1
            files.insert(files.begin() + pos + 1, *it); // consequently, it will be pushed to the next file 
            files.erase(it + 1); // erase file from original position
        }
        else {
            it--;
        }
        --currID;

        // // Comment/Uncomment to print sorting (debug)
        // for(int j = 0; j < files.size(); ++j) {
        //     const pair<int, int>& p = files[j];
        //     cout << "[";
        //     for(int i = 0; i < p.second; ++i) {
        //         cout << p.first;
        //     }
        //     cout << "]";
        //     if(j < gaps.size()) {
        //         int gap = gaps[j];
        //         for(int i = 0; i < gap; ++i) {
        //             cout << ".";
        //         }
        //         if(gap == 0) {
        //             cout << "_";
        //         }
        //     }
        // }
        // cout << endl;
    }

    // get checksum
    int pos = 0;
    size_t fileSize = files.size();
    for(int i = 0; i < fileSize; ++i) {
        const pair<int, int>& file = files[i];
        for(int j = pos + file.second; pos < j; ++pos) {
            sum += pos * file.first;
        }
        pos += gaps[i];
    }

    cout << "Filesystem checksum: " << sum << endl;

    return 0;
}