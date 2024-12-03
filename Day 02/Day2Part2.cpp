#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// dude i'm so fuckin washed at programming

// checks given report and returns if safe or not
bool checkReport(const vector<int>& report) {
    int currLevel = report.front();
    bool unsafe = false;

    // 0: default
    // 1: increasing
    // -1: decreasing
    int increasing = 0;

    int reportSize = report.size();
    // iterate through the levels and check if criteria are met
    for(int i = 1; i < reportSize; ++i) {
        int prevLevel = currLevel;
        currLevel = report[i];

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

        if(unsafe) return false;
    }

    return true;
}

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

                // send all levels into the report vector
                while(getline(stream, token, ' ')) {
                    currReport.push_back(stoi(token));
                }

                for(int i : currReport) {
                    cout << i << ", ";
                }

                // check if report is safe
                bool safe = checkReport(currReport);
                if(safe) {
                    sum++;
                    cout << "SAFE" << endl;
                }
                // check if safe when one level is removed
                else {
                    int reportSize = currReport.size();
                    for(int i = 0; i < reportSize; ++i) {
                        vector<int> tempReport = currReport;
                        tempReport.erase(tempReport.begin() + i);

                        safe = checkReport(tempReport);
                        if(safe) {
                            sum++;
                            cout << "SAFE [remove position " << i << "]" << endl;
                            break;
                        }
                    }
                }

                if(!safe) {
                    cout << "UNSAFE" << endl;
                }
        }
    }

    cout << endl << "Number of safe reports: " << sum << endl;

    return 0;
}