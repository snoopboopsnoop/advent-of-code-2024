#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <iomanip>

using namespace std;

// bro its only day 6

enum Direction {
    Up,
    Right,
    Down,
    Left 
};

// returns true if obstacle map results in loop
bool isLoop(const vector<pair<int, int>>& obstacles, const pair<int, int>& guardStart, int rows, int columns) {
    bool guardGone = false;
    bool loop = false;
    int dir = Up;

    pair<int, int> guard = guardStart;
    vector<pair<int, int>> endPos; // all ending positions after full 4 turns

    while(!guardGone && !loop) {
        for(int j = 0; j < 4 && !guardGone; j++) {
            switch(dir) {
                case Up: {
                    vector<pair<int, int>> path(obstacles.size());
                    // copies to path all obstacles in the correct column above guard
                    auto it = copy_if(obstacles.begin(), obstacles.end(), path.begin(), [guard](pair<int, int> p) {
                        return (p.second == guard.second && p.first < guard.first);
                    });
                    if(it == path.begin()) {
                        guardGone = true;
                        path.push_back(make_pair(-1, guard.second));
                    }
                    else {
                        path.erase(it, path.end());
                    }

                    // gets closest obstacle in guards way
                    it = min_element(path.begin(), path.end(), [guard](const pair<int, int>& a, const pair<int, int>& b) {
                        return abs(a.first - guard.first) < abs(b.first - guard.first);
                    });

                    // set guard to position under obstacle
                    guard = make_pair(it->first + 1, guard.second);

                    break;
                }

                case Right: {
                    vector<pair<int, int>> path(obstacles.size());
                    // copies to path all obstacles in the correct row to the right of guard
                    auto it = copy_if(obstacles.begin(), obstacles.end(), path.begin(), [guard](pair<int, int> p) {
                        return (p.first == guard.first && p.second > guard.second);
                    });
                    if(it == path.begin()) {
                        guardGone = true;
                        path.push_back(make_pair(guard.first, columns));
                    }
                    else {
                        path.erase(it, path.end());
                    }

                    // gets closest obstacle in guards way
                    it = min_element(path.begin(), path.end(), [guard](const pair<int, int>& a, const pair<int, int>& b) {
                        return abs(a.second - guard.second) < abs(b.second - guard.second);
                    });

                    // set guard to position left of obstacle
                    guard = make_pair(guard.first, it->second - 1);
                    
                    break;
                }

                case Down: {
                    vector<pair<int, int>> path(obstacles.size());
                    // copies to path all obstacles in the correct column under guard
                    auto it = copy_if(obstacles.begin(), obstacles.end(), path.begin(), [guard](pair<int, int> p) {
                        return (p.second == guard.second && p.first > guard.first);
                    });
                    if(it == path.begin()) {
                        guardGone = true;
                        path.push_back(make_pair(rows, guard.second));
                    }
                    else {
                        path.erase(it, path.end());
                    }

                    // gets closest obstacle in guards way
                    it = min_element(path.begin(), path.end(), [guard](const pair<int, int>& a, const pair<int, int>& b) {
                        return abs(a.first - guard.first) < abs(b.first - guard.first);
                    });

                    // set guard to position above obstacle
                    guard = make_pair(it->first - 1, guard.second);
                    
                    break;
                }

                case Left: {
                    vector<pair<int, int>> path(obstacles.size());
                    // copies to path all obstacles in the correct row to the left of guard
                    auto it = copy_if(obstacles.begin(), obstacles.end(), path.begin(), [guard](pair<int, int> p) {
                        return (p.first == guard.first && p.second < guard.second);
                    });
                    if(it == path.begin()) {
                        guardGone = true;
                        path.push_back(make_pair(guard.first, -1));
                    }
                    else {
                        path.erase(it, path.end());
                    }

                    // gets closest obstacle in guards way
                    it = min_element(path.begin(), path.end(), [guard](const pair<int, int>& a, const pair<int, int>& b) {
                        return abs(a.second - guard.second) < abs(b.second - guard.second);
                    });

                    // set guard to position to the right of obstacle
                    guard = make_pair(guard.first, it->second + 1);
                    
                    break;
                }
                
            }

            if(dir == Left) {
                dir = Up;
            }
            else dir++;
        }

        // if guard has returned to an existing starting position then we have a loop
        if(find(endPos.begin(), endPos.end(), guard) != endPos.end()) {
            loop = true;
        }
        else {
            endPos.push_back(guard);
        }
    }

    return loop;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;

    pair<int, int> guard; // position of guard
    vector<pair<int, int>> obstacles;

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
                }
            }
            rows++;
        }
    }

    int spaces = rows * columns;

    // place obstacle in each coordinate, check if loop
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            pair<int, int> tempPair(i, j);
            if(find(obstacles.begin(), obstacles.end(), tempPair) != obstacles.end()) {
                continue;
            }
            
            vector<pair<int, int>> tempObs = obstacles;
            tempObs.push_back(tempPair);
            bool loop = isLoop(tempObs, guard, rows, columns);
            if(loop) {
                cout << fixed << setprecision(1) << (double)(columns * (i) + j + 1) / (double)spaces * 100 << "% [" << sum << " LOOP LOCATIONS]\r"; 
                cout.flush();
                sum += 1;
            }
        }
    }

    cout << "Possible obstruction locations that cause a loop: " << sum << "\r";
    cout.flush();

    return 0;
}