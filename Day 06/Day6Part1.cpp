#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

// bro its only day 6

enum Direction {
    Up,
    Right,
    Down,
    Left 
};

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;

    pair<int, int> guard; // position of guard
    vector<pair<int, int>> obstacles;
    set<pair<int, int>> visited; // positions guard will visit

    int rows = 0;
    int columns = 0;
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;
            if(rows == 0) {
                columns = line.size();
            }

            int size = line.size();
            for(int i = 0; i < size; ++i) {
                // add obstacles
                if(line[i] == '#') {
                    obstacles.push_back(make_pair(rows, i));
                }
                // add guard
                else if(line[i] == '^') {
                    guard = make_pair(rows, i);
                    visited.insert(guard);
                }
            }
            rows++;
        }
    }

    bool guardGone = false;
    int dir = Up;

    while(!guardGone) {
        pair<int, int> endPos;
        switch(dir) {
            case Up: {
                // gets closest obstacle in guards way
                auto it = min_element(obstacles.begin(), obstacles.end(), [guard](const pair<int, int>& a, const pair<int, int>& b) {
                    if(a.second != guard.second || a.first > guard.first) {
                        return false;
                    }
                    else if(b.second != guard.second || b.first > guard.first) {
                        return true;
                    }
                    else {
                        return abs(a.first - guard.first) < abs(b.first - guard.first);
                    }
                });
                if(it->second != guard.second) {
                    guardGone = true;
                    endPos = make_pair(-1, guard.second);
                }
                else {
                    endPos = *it;
                }

                // adds all positions up to obstacle
                for(int i = guard.first - 1; i > endPos.first; --i) {
                    visited.insert(make_pair(i, guard.second));
                }
                // set guard to position under obstacle
                guard = make_pair(endPos.first + 1, guard.second);

                break;
            }

            case Right: {
                // gets closest obstacle in guards way
                auto it = min_element(obstacles.begin(), obstacles.end(), [guard](const pair<int, int>& a, const pair<int, int>& b) {
                    if(a.first != guard.first || a.second < guard.second) {
                        return false;
                    }
                    else if(b.first != guard.first || b.second < guard.second) {
                        return true;
                    }
                    else {
                        return abs(a.second - guard.second) < abs(b.second - guard.second);
                    }
                });
                if(it -> first != guard.first) {
                    guardGone = true;
                    endPos = make_pair(guard.first, columns);
                }
                else {
                    endPos = *it;
                }

                // adds all positions up to obstacle
                for(int i = guard.second + 1; i < endPos.second; ++i) {
                    visited.insert(make_pair(guard.first, i));
                }
                // set guard to position left of obstacle
                guard = make_pair(guard.first, endPos.second - 1);
                
                break;
            }

            case Down: {
                // gets closest obstacle in guards way
                auto it = min_element(obstacles.begin(), obstacles.end(), [guard](const pair<int, int>& a, const pair<int, int>& b) {
                    if(a.second != guard.second || a.first < guard.first) {
                        return false;
                    }
                    else if(b.second != guard.second || b.first < guard.first) {
                        return true;
                    }
                    else {
                        return abs(a.first - guard.first) < abs(b.first - guard.first);
                    }
                });
                if(it->second != guard.second) {
                    guardGone = true;
                    endPos = make_pair(rows, guard.second);
                }
                else {
                    endPos = *it;
                }

                // adds all positions up to obstacle
                for(int i = guard.first + 1; i < endPos.first; ++i) {
                    visited.insert(make_pair(i, guard.second));
                }
                // set guard to position above obstacle
                guard = make_pair(endPos.first - 1, guard.second);
                
                break;
            }

            case Left: {
                // gets closest obstacle in guards way
                auto it = min_element(obstacles.begin(), obstacles.end(), [guard](const pair<int, int>& a, const pair<int, int>& b) {
                    if(a.first != guard.first || a.second > guard.second) {
                        return false;
                    }
                    else if(b.first != guard.first || b.second > guard.second) {
                        return true;
                    }
                    else {
                        return abs(a.second - guard.second) < abs(b.second - guard.second);
                    }
                });
                if(it->first != guard.first) {
                    guardGone = true;
                    endPos = make_pair(guard.first, -1);
                }
                else {
                    endPos = *it;
                }

                // adds all positions up to obstacle
                for(int i = guard.second - 1; i > endPos.second; --i) {
                    visited.insert(make_pair(guard.first, i));
                }
                // set guard to position to the right of obstacle
                guard = make_pair(guard.first, endPos.second + 1);
                
                break;
            }
        }

        if(dir == Left) {
            dir = Up;
        }
        else dir++;
    }

    cout << "Guard visits " << visited.size() << " locations" << endl;

    return 0;
}