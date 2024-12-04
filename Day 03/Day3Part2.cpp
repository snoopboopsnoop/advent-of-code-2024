#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

// regex is king

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;
    // are commands on
    bool on = true;

    while(in) {
        while(getline(in, line)) {
            if(line == "") break;

            smatch match;
            // matches for 'mul(___,___)' with any 1-3 digit inputs
            // or 'don't()' or 'do()'
            regex r("mul\\([0-9]{1,3},[0-9]{1,3}\\)|don't\\(\\)|do\\(\\)");

            // get each match
            while(regex_search(line, match, r)) {
                cout << "Matched: " << match.str(0) << " = ";

                string cmd = match.str(0);

                // check the command, process accordingly
                if(cmd == "do()") {
                    on = true;
                    cout << "[ENABLING MULTIPLICATION]" << endl;
                }
                else if(cmd == "don't()") {
                    on = false;
                    cout << "[DISABLING MULTIPLICATION]" << endl;
                }
                else {
                    if(on) {
                        // parsing indices
                        int startPos = cmd.find('(') + 1;
                        int comma = cmd.find(',');
                        int endPos = cmd.find(')');

                        // parse for numbres to multiply
                        int first = stoi(cmd.substr(startPos, comma-startPos));
                        int second = stoi(cmd.substr(comma+1, endPos - comma - 1));

                        // add to sum
                        sum += first * second;
                        cout << first * second << endl;
                    }
                    else {
                        cout << "[MULTIPLICATION IS DISABLED]" << endl;
                    }
                }

                // remove up to matched portion of string
                line = match.suffix().str();
            }
        }
    }

    cout << "Multiplication Results: " << sum << endl;

    return 0;
}