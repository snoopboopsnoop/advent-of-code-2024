#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

// zen garden

// returns price of region containing start coordinate
int getPrice(const pair<int, int>& start, const vector<string>& garden, set<pair<int, int>>& visitedGlobal) {
    vector<pair<int, int>> visited; // local visited, used for side counting later
    vector<pair<int, int>> queue; // holds coords to look at
    queue.push_back(start);

    char c = garden[start.first][start.second]; // region name
    int area = 0; // # of plots in region
    int sides = 0; // # of sides in region
    int rows = garden.size();
    int columns = garden[0].size();

    // make box around region
    int minRow = queue.front().first;
    int maxRow = minRow;
    int minCol = queue.front().second;
    int maxCol = minCol;

    while(queue.size() != 0) { // bfs (i think)
        pair<int, int> curr = queue.front();
        queue.erase(queue.begin());
        visited.push_back(curr);
        area++;

        // update region box
        if(curr.first < minRow) {
            minRow = curr.first;
        }
        else if(curr.first > maxRow) {
            maxRow = curr.first;
        }
        if(curr.second < minCol) {
            minCol = curr.second;
        }
        else if(curr.second > maxCol) {
            maxCol = curr.second;
        }

        // up
        pair<int, int> next;
        if(curr.first - 1 >= 0) {
            next = make_pair(curr.first - 1, curr.second);
            if(garden[next.first][next.second] == c) { // add plot to queue if in region and not yet visited
                if(find(visited.begin(), visited.end(), next) == visited.end() && find(queue.begin(), queue.end(), next) == queue.end()) {
                    queue.push_back(next);
                }
            }
        }

        // right
        if(curr.second + 1 < columns) {
            next = make_pair(curr.first, curr.second + 1);
            if(garden[next.first][next.second] == c) { // add plot to queue if in region and not yet visited
                if(find(visited.begin(), visited.end(), next) == visited.end() && find(queue.begin(), queue.end(), next) == queue.end()) {
                    queue.push_back(next);
                }
            }
        }

        // down
        if(curr.first + 1 < rows) {
            next = make_pair(curr.first + 1, curr.second);
            if(garden[next.first][next.second] == c) { // add plot to queue if in region and not yet visited
                if(find(visited.begin(), visited.end(), next) == visited.end() && find(queue.begin(), queue.end(), next) == queue.end()) {
                    queue.push_back(next);
                }
            }
        }

        // left
        if(curr.second - 1 >= 0) {
            next = make_pair(curr.first, curr.second - 1);
            if(garden[next.first][next.second] == c) { // add plot to queue if in region and not yet visited
                if(find(visited.begin(), visited.end(), next) == visited.end() && find(queue.begin(), queue.end(), next) == queue.end()) {
                    queue.push_back(next);
                }
            }
        }
    }

    // count horizontal edges
    for(int i = minRow; i <= maxRow; ++i) {
        bool onSideT = false;
        bool onSideB = false;

        for(int j = minCol; j <= maxCol; ++j) {
            if(find(visited.begin(), visited.end(), make_pair(i, j)) == visited.end()) {
                sides += onSideT + onSideB;
                onSideT = false;
                onSideB = false;
                continue;
            }
            const pair<int, int> plot = make_pair(i, j);

            // check if region continues above
            if(plot.first - 1 < 0 || garden[plot.first - 1][plot.second] != c) {
                onSideT = true;
            }
            else {
                sides += onSideT;
                onSideT = false;
            }

            // check if region continues below
            if(plot.first + 1 >= rows || garden[plot.first + 1][plot.second] != c) {
                onSideB = true;
            }
            else {
                sides += onSideB;
                onSideB = false;
            }
        }            
        sides += onSideT + onSideB;
    }

    // count vertical edges
    for(int i = minCol; i <= maxCol; ++i) {
        bool onSideL = false;
        bool onSideR = false;

        for(int j = minRow; j <= maxRow; j++) {
            if(find(visited.begin(), visited.end(), make_pair(j, i)) == visited.end()) {
                sides += onSideL + onSideR;
                onSideL = false;
                onSideR = false;
                continue;
            }
            const pair<int, int> plot = make_pair(j, i);

            // check if region continues left
            if(plot.second - 1 < 0 || garden[plot.first][plot.second - 1] != c) {
                onSideL = true;
            }
            else {
                sides += onSideL;
                onSideL = false;
            }

            // check if region continues right
            if(plot.second + 1 >= columns || garden[plot.first][plot.second + 1] != c) {
                onSideR = true;
            }
            else {
                sides += onSideR;
                onSideR = false;
            }
        }
        sides += onSideL + onSideR;
    }

    cout << "Region " << c << " has " << sides << " sides" << endl;

    visitedGlobal.insert(visited.begin(), visited.end());

    return sides * area;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;

    vector<string> garden;
    set<pair<int, int>> visited;

    // build garden
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;
            
            garden.push_back(line);
        }
    }

    for(int i = 0; i < garden.size(); ++i) {
        for(int j = 0; j < garden[0].size(); ++j) {
            // if not yet visited
            pair<int, int> curr(i, j);
            if(visited.find(curr) == visited.end()) {
                sum += getPrice(curr, garden, visited);
            }
        }
    }

    cout << endl << "Total price to fence the garden: $" << sum << endl;

    return 0;
}