#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;

// experimentally determined advent of code challenge

const int ROOM_ROWS = 103;
const int ROOM_COLS = 101;
const int TIME_ELAPSED = 100;

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

    int i = 0;
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
            cout << "Robot " << i << " after " << TIME_ELAPSED << " seconds: " << robot.pos.first << ", " << robot.pos.second << endl;

            robots.push_back(robot);
            ++i;
        }
    }

    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

    // get # of robots in each quarter
    for(const Robot& r : robots) {
        int halfY = ROOM_ROWS / 2;
        int halfX = ROOM_COLS / 2;

        if(r.pos.first < halfX) {
            if(r.pos.second < halfY) {
                q2++;
            }
            else if(r.pos.second > halfY) {
                q3++;
            }
        }
        else if(r.pos.first > halfX) {
            if(r.pos.second < halfY) {
                q1++;
            }
            else if(r.pos.second > halfY) {
                q4++;
            }
        }
    }

    cout << endl << q1 << " robots in Quarter 1 (top right)" << endl;
    cout << q2 << " robots in Quarter 2 (top left)" << endl;
    cout << q3 << " robots in Quarter 3 (bottom left)" << endl;
    cout << q4 << " robots in Quarter 4 (bottom right)" << endl;

    cout << "Safety factor after " << TIME_ELAPSED << " seconds have elapsed: " << q1 * q2 * q3 * q4 << endl;

    return 0;
}