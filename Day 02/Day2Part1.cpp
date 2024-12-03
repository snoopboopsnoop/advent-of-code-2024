#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// dude i'm so fuckin washed at programming

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;


    while(in) {
        // go through each report
        while(getline(in, line)) {
            if(line == "") break;
                // stream to read in the report
                istringstream stream(line);
                string token;
                vector<int> currReport;

                // save initial level
                getline(stream, token, ' ');
                int currLevel = stoi(token);
                cout << "(" << currLevel;

                // 0: default
                // 1: increasing
                // -1: decresing
                int increasing = 0;
                bool unsafe = false;

                // go through each level in report
                while(getline(stream, token, ' ') && unsafe == false) {
                    int prevLevel = currLevel;
                    currLevel = stoi(token);
                    cout << ", " << currLevel;

                    // check if change is gradual
                    int diff = abs(prevLevel - currLevel);

                    if(diff <= 3 && diff >= 1) {
                        // condition if change not set -- set increasing/decreasing
                        if(increasing == 0) {
                            if(currLevel < prevLevel) increasing = -1;
                            else if(currLevel > prevLevel) increasing = 1;
                            else unsafe = true;
                        }
                        // condition if increasing -- check if continues to increase
                        else if(increasing == 1) {
                            if(currLevel <= prevLevel) unsafe = true;
                        }
                        // condition if decreasing -- check if continues to decrease
                        else if(increasing == -1) {
                            if(currLevel >= prevLevel) unsafe = true;
                        }
                    }

                    else unsafe = true;
                }
                cout << "): ";
                // add number to sum if report was safe
                if(!unsafe) {
                    sum++;
                    cout << "SAFE" << endl;
                }
                else cout << "UNSAFE" << endl;
        }
    }

    cout << "Number of safe reports: " << sum << endl;

    return 0;
}