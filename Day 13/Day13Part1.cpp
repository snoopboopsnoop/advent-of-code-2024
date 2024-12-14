#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// ludwig and connor at the arcade (https://www.youtube.com/watch?v=AEv02RYOwX0)

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int sum = 0;

    int machine = 1;
    while(in) {
        while(getline(in, line)) {
            if(line == "") { // end of machine
                machine++;
                continue;
            }

            int a = 0; 
            int b = 0; 
            int c = 0; // [ a b ] [ A ] = [ X ]
            int d = 0; // [ c d ] [ B ] = [ Y ]
            int X = 0;
            int Y = 0;
            
            // i didnt want to manually parse the strings
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
            X = stoi(token);
            getline(stream, token, '=');
            getline(stream, token);
            Y = stoi(token);

            // inverse of matrix to get A, B
            int det = a*d - b*c;
            int Anum = (d * X) - (b * Y);
            int Bnum = (-c * X) + (a * Y);

            cout << "Machine " << machine << ": ";
            if((Anum % det) == 0 && (Bnum % det) == 0) { // check that A, B are integers
                int A = Anum / det;
                int B = Bnum / det;
                sum += A * 3 + B;
                cout << "Press A " << Anum / det << " times and B " << Bnum / det << " times" << endl;
            }
            else {
                cout << "[UNBEATABLE]" << endl;
            }
        }
    }

    cout << endl << "It would cost $" << sum << " to win all the prizes" << endl;

    return 0;
}