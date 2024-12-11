#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

// yo momma a graph the way i depth first search

int trailScore(const pair<int, int>& trailhead, const vector<vector<int>>& map); // returns trailscore starting from trailhead parameter
void checkNext(const pair<int, int>& curr, const pair<int, int>& next, const vector<vector<int>>& map, const vector<pair<int, int>>& visited); // checks if tile is valid, pushes to queue

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;

    vector<vector<int>> map;

    // create map
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;
            vector<int> temp;
            for(char c : line) {
                temp.push_back(c - '0');
            }
            map.push_back(temp);
        }
    }

    // go through all trail heads, sum scores
    for(int i = 0; i < map.size(); ++i) {
        for(int j = 0; j < map[0].size(); ++j) {
            if(map[i][j] == 0) {
                sum += trailScore(make_pair(i, j), map);
            }
        }
    }

    cout << "Total trailhead score: " << sum << endl;

    return 0;
}

// checks if tile is valid and adds to queue, returns true if added to queue
bool checkNext(const pair<int, int>& next, const pair<int, int>& curr, const vector<vector<int>>& map, vector<pair<int, int>>& visited, queue<pair<int, int>>& queue) {
    if(next.first >= map.size() || next.first < 0) return 0;
    if(next.second >= map[0].size() || next.second < 0) return 0;

    int tile = map[next.first][next.second];

    // check if valid tile to go to
    if (tile == map[curr.first][curr.second] + 1) {
        if(find(visited.begin(), visited.end(), next) == visited.end()) {
            queue.push(next);
            visited.push_back(next);
            return true;
        }
    }

    return false;
}

// returns number of 9s that can be reached from trailhead
int trailScore(const pair<int, int>& trailhead, const vector<vector<int>>& map) {
    queue<pair<int, int>> queue;
    vector<pair<int, int>> visited;
    queue.push(trailhead);
    int score = 0;

    while(queue.size() != 0) {
        const pair<int, int> curr = queue.front();
        visited.push_back(curr);
        queue.pop();
    
        if(map[curr.first][curr.second] == 9) {
            score++;
            continue;
        }

        // check up
        checkNext(make_pair(curr.first - 1, curr.second), curr, map, visited, queue);
        // check right
        checkNext(make_pair(curr.first, curr.second + 1), curr, map, visited, queue);
        // check down
        checkNext(make_pair(curr.first + 1, curr.second), curr, map, visited, queue);
        // check left
        checkNext(make_pair(curr.first, curr.second - 1), curr, map, visited, queue);
    }

    return score;
}