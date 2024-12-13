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
int getPrice(const pair<int, int>& start, const vector<string>& garden, set<pair<int, int>>& visited) {
    vector<pair<int, int>> queue; // holds coords to look at
    queue.push_back(start);

    char c = garden[start.first][start.second]; // region name
    int area = 0; // # of plots in region
    int perimeter = 0;
    int rows = garden.size();
    int columns = garden[0].size();

    while(queue.size() != 0) { // bfs (i think)
        pair<int, int> curr = queue.front();
        queue.erase(queue.begin());
        visited.insert(curr);
        area++;

        // up
        pair<int, int> next;
        if(curr.first - 1 >= 0) {
            next = make_pair(curr.first - 1, curr.second);
            if(garden[next.first][next.second] == c) { // add plot to queue if in region and not yet visited
                if(visited.find(next) == visited.end() && find(queue.begin(), queue.end(), next) == queue.end()) {
                    queue.push_back(next);
                }
            }
            else { // all sides that touch a different plot are perimeter sides
                perimeter++;
            }
        }
        else { // all sides that touch a different plot are perimeter sides
            perimeter++;
        }

        // right
        if(curr.second + 1 < columns) {
            next = make_pair(curr.first, curr.second + 1);
            if(garden[next.first][next.second] == c) { // add plot to queue if in region and not yet visited
                if(visited.find(next) == visited.end() && find(queue.begin(), queue.end(), next) == queue.end()) {
                    queue.push_back(next);
                }
            }
            else { // all sides that touch a different plot are perimeter sides
                perimeter++;
            }
        }
        else { // all sides that touch a different plot are perimeter sides
            perimeter++;
        }

        // down
        if(curr.first + 1 < rows) {
            next = make_pair(curr.first + 1, curr.second);
            if(garden[next.first][next.second] == c) { // add plot to queue if in region and not yet visited
                if(visited.find(next) == visited.end() && find(queue.begin(), queue.end(), next) == queue.end()) {
                    queue.push_back(next);
                }
            }
            else { // all sides that touch a different plot are perimeter sides
                perimeter++;
            }
        }
        else { // all sides that touch a different plot are perimeter sides
            perimeter++;
        }

        // left
        if(curr.second - 1 >= 0) {
            next = make_pair(curr.first, curr.second - 1);
            if(garden[next.first][next.second] == c) { // add plot to queue if in region and not yet visited
                if(visited.find(next) == visited.end() && find(queue.begin(), queue.end(), next) == queue.end()) {
                    queue.push_back(next);
                }
            }
            else { // all sides that touch a different plot are perimeter sides
                perimeter++;
            }
        }
        else { // all sides that touch a different plot are perimeter sides
            perimeter++;
        }
    }

    cout << "Region " << c << " has perimeter " << perimeter << " and area " << area << endl;
    return perimeter * area;
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