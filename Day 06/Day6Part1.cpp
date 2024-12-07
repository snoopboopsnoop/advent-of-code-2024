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

                // adds all positions up to obstacle
                for(int i = guard.first - 1; i > it->first; --i) {
                    visited.insert(make_pair(i, guard.second));
                }
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

                // adds all positions up to obstacle
                for(int i = guard.second + 1; i < it->second; ++i) {
                    visited.insert(make_pair(guard.first, i));
                }
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

                // adds all positions up to obstacle
                for(int i = guard.first + 1; i < it->first; ++i) {
                    visited.insert(make_pair(i, guard.second));
                }
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

                // adds all positions up to obstacle
                for(int i = guard.second - 1; i > it->second; --i) {
                    visited.insert(make_pair(guard.first, i));
                }
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

    cout << "Guard visits " << visited.size() << " locations" << endl;

    return 0;
}