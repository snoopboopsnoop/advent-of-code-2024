#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <windows.h>

using namespace std;

// experimentally determined advent of code challenge

const int ROOM_ROWS = 103;
const int ROOM_COLS = 101;
const int TIME_ELAPSED = 7774; // experimentally determined (sat watching)

struct Robot {
    pair<int, int> pos;
    pair<int, int> vel;

    Robot(pair<int, int> pos, pair<int, int> vel) {
        this->pos = pos;
        this->vel = vel;
    }

    // updates to position after t seconds
    void updatePos(int t) {
        pos.first = (pos.first + (t * vel.first)) % ROOM_COLS; // use mod to wrap around
        pos.second = (pos.second + (t * vel.second)) % ROOM_ROWS; // same
        if(pos.first < 0) { // deal with negative mods (c++ implementation of mod)
            pos.first += ROOM_COLS;
        }
        if(pos.second < 0) { // same
            pos.second += ROOM_ROWS;
        }
    }
};

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    vector<Robot> robots;

    while(in) {
        while(getline(in, line)) {
            if(line == "") break;

            istringstream stream(line);
            string token;
            
            pair<int, int> pos;
            pair<int, int> vel;

            // once again too lazy to parse manually
            getline(stream, token, '=');
            getline(stream, token, ',');
            pos.first = stoi(token);
            getline(stream, token, ' ');
            pos.second = stoi(token);
            getline(stream, token, '=');
            getline(stream, token, ',');
            vel.first = stoi(token);
            getline(stream, token);
            vel.second = stoi(token);

            Robot robot(pos, vel);
            robot.updatePos(TIME_ELAPSED); 

            robots.push_back(robot);
        }
    }
    
    // // Process for finding the correct time
    // int i = 5199;
    // while(true) {
    //     for(Robot& r : robots) {
    //         r.updatePos(103);
    //     }

    //     cout << "After " << i << " seconds:" << endl;
    //     for(int j = 0; j < ROOM_ROWS; j++) {
    //         string row;
    //         for(int k = 0; k < ROOM_COLS; k++) {
    //             if(find_if(robots.begin(), robots.end(), [j, k](const Robot& r) {
    //                 return r.pos.first == k && r.pos.second == j;
    //             }) != robots.end()) {
    //                 row += "o";
    //             }
    //             else {
    //                 row += ".";
    //             }
    //         }
    //         cout << row << endl;
    //     }
    //     cout << endl;
    //     Sleep(100);
    //     i += 103;
    // }

    cout << "After " << TIME_ELAPSED << " seconds:" << endl;
    for(int j = 0; j < ROOM_ROWS; j++) { // print room
        string row;
        for(int k = 0; k < ROOM_COLS; k++) {
            if(find_if(robots.begin(), robots.end(), [j, k](const Robot& r) {
                return r.pos.first == k && r.pos.second == j;
            }) != robots.end()) {
                row += "o";
            }
            else {
                row += ".";
            }
        }
        cout << row << endl;
    }

    return 0;
}