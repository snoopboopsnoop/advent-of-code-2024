#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

// y = mx + b

struct Frequency {
    char frequency = '.';
    vector<pair<int, int>> antennas;

    Frequency(char f) {
        frequency = f;
    }

    void addAntenna(const pair<int, int>& loc) {
        antennas.push_back(loc);
    }

    void print() const {
        cout << frequency << ": { (" << antennas.begin()->first << ", " << antennas.begin()->second << ") ";
        for(auto it = antennas.begin() + 1; it != antennas.end(); ++it) {
            cout << ", (" << it->first << ", " << it->second << ") ";
        }
        cout << "}" << endl;
    }   

    // inserts antinode positions into loc parameter
    void getAntiNodes(set<pair<int, int>>& loc, int rows, int columns) const {
        auto it = antennas.begin();
        while(it != antennas.end()) {
            for(auto it2 = it + 1; it2 != antennas.end(); ++it2) {
                int dy = it->first - it2->first;
                int dx = it->second - it2->second;

                int newY = it->first;
                int newX = it->second;
                while(newX >=0 && newX < columns && newY >= 0 && newY < rows) {
                    loc.insert(make_pair(newY, newX));

                    newY = newY + dy;
                    newX = newX + dx;
                }
                
                newY = it->first - dy;
                newX = it->second - dx;
                while(newX >=0 && newX < columns && newY >= 0 && newY < rows) {
                    loc.insert(make_pair(newY, newX));

                    newY = newY - dy;
                    newX = newX - dx;
                }
            }

            it++;
        }
    }
};

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    map<char, Frequency> freqs;

    int rows = 0;
    int columns = 0;
    while(in) {
        while(getline(in, line)) {
            if(line == "") break;
            if(rows == 0) {
                columns = line.size();
            }

            // add all frequencies and positions to freqs
            for(int i = 0; i < line.size(); ++i) {
                if(line[i] != '.') {
                    auto it = freqs.insert(make_pair(line[i], Frequency(line[i]))).first;
                    it->second.addAntenna(make_pair(rows, i));
                }
            }
            ++rows;
        }
    }

    //get all unique antinodes
    set<pair<int, int>> antinodes;
    for(const pair<char, Frequency> f : freqs) {
        f.second.print();
        f.second.getAntiNodes(antinodes, rows, columns);
    }

    cout << endl << "Unique antinode positions: " << antinodes.size() << endl;

    return 0;
}