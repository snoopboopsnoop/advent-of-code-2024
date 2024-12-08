#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

// today i learned i cannot read

// returns true if there is a valid combination of +, * that satisfies equation
bool possible(unsigned long long num, const stack<int>& values) {
    bool result = false;
    bool failed = false;

    stack<int> newValues = values;
    newValues.pop();

    // check if * is a valid operator
    if(num % values.top() == 0) {
        // handle return case
        if(newValues.size() == 0) {
            if(num / values.top() == 1) {
                return true;
            }
        }
        else {
            result += possible(num / values.top(), newValues);
        }
    }
    else failed = true;

    // check if + is a valid operator
    if(num - values.top() >= 0) {
        // handle return case
        if(newValues.size() == 0) {
            if(num - values.top() == 0) {
                return true;
            }
            else {
                return false;
            }
        }
        result += possible(num - values.top(), newValues);
    }
    else {
        // return false if neither operator is valid
        if(failed == true) {
            return false;
        }
    }
    
    return result;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    unsigned long long sum = 0;

    while(in) {
        while(getline(in, line)) {
            if(line == "") break;

            // parse
            int pos = line.find(":");
            unsigned long long num = stoull(line.substr(0, pos));
            stack<int> values;

            // put numbers into stack (want to read right to left)
            istringstream stream(line.substr(pos+2));
            string token;
            while(getline(stream, token, ' ')) {
                values.push(stoi(token));
            }

            // check if a combination of operators works
            cout << "Checking " << num << ": ";
            if(possible(num, values)) {
                sum += num;
                cout << "[VALID]" << endl;
            }
            else {
                cout << "[INVALID]" << endl;
            }
        }
    }

    cout << endl << "Total calibration result: " << sum << endl;

    return 0;
}