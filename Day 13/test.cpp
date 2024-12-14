#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// 

long long ADDPOS = 10000000000000;

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    unsigned long long sum = 0;

    while(in) {
        while(getline(in, line)) {
            if(line == "") continue;

            int a = 0;
            int b = 0;
            int c = 0;
            int d = 0;
            long long X = 0;
            long long Y = 0;
            
            istringstream stream(line);
            string token;
            getline(stream, token, '+');
            getline(stream, token, ',');
            a = stoi(token);
            getline(stream, token, '+');
            getline(stream, token);
            c = stoi(token);

            getline(in, line);
            stream = istringstream(line);
            getline(stream, token, '+');
            getline(stream, token, ',');
            b = stoi(token);
            getline(stream, token, '+');
            getline(stream, token);
            d = stoi(token);

            getline(in, line);
            stream = istringstream(line);
            getline(stream, token, '=');
            getline(stream, token, ',');
            X = stoi(token) + ADDPOS;
            getline(stream, token, '=');
            getline(stream, token);
            Y = stoi(token) + ADDPOS;

            int det = a*d - b*c;
            long long Anum = (d * X) - (b * Y);
            long long Bnum = (-c * X) + (a * Y);

            if((Anum % det) == 0 && (Bnum % det) == 0) {
                long long A = Anum / det;
                long long B = Bnum / det;
                sum += A * 3 + B;
                cout << "press A " << Anum / det << " times and B " << Bnum / det << " times" << endl;
            }
            else {
                cout << "machine is unbeatable" << endl;
            }
        }
    }

    cout << ": " << sum << endl;

    return 0;
}