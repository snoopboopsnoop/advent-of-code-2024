#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>

using namespace std;

// code optimization is so dumb like just let my code run like shit jeez

const int BLINKS = 25;

struct Stone {
    unsigned long long number = 0; // number marked on stone
    vector<Stone*> next;

    Stone() {
        number = 0;
    }

    Stone(unsigned long long num) {
        number = num;
    }

    // if next has been mapped, puts next into stones and returns true.
    // if not mapped, returns false
    bool getNext(vector<Stone*>& stones) {
        if(next.size() != 0) {
            stones = next;
            return true;
        }
        else {
            return false;
        }
    }
};

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    unsigned long long sum = 0;

    map<unsigned long long, Stone> lookUp; // stone number -> stone corresponding to it
    map<unsigned long long, unsigned long long> stones; // stone number -> # of that stone

    getline(in, line);
    istringstream stream(line);
    string token;

    lookUp[0] = Stone();
    lookUp[1] = Stone(1);

    while(getline(stream, token, ' ')) {
        int num = stoi(token);
        lookUp[num] = Stone(num);
        stones[num] += 1;
    }

    // // Comment/Uncomment to see starting stone lineup
    // for(const pair<unsigned long long, unsigned long long>& stone : stones) {
    //     cout << "stone " << stone.first << ": " << stone.second << endl;
    // }
    // cout << endl;

    for(int i = 0; i < BLINKS; ++i) {
        map<unsigned long long, unsigned long long> newStones;
        for(const pair<unsigned long long, unsigned long long>& stone : stones) { // go through each unique stone
            vector<Stone*> nextStones; // the replacement stones
            Stone currStone = lookUp[stone.first];

            if(currStone.next.size() == 0) { // if not yet mapped
                if(currStone.number == 0) { // turns 0 -> 1
                    nextStones.push_back(&(lookUp[1]));
                }
                else {
                    int digits = log10(currStone.number) + 1;
                    if(digits % 2 == 0) { // split stone in half
                        int half = digits / 2;
                        string num = to_string(currStone.number);

                        // first half of stone                        
                        unsigned long long newStone = stoull(num.substr(0, half));
                        if(lookUp.find(newStone) == lookUp.end()) { // if doesnt exist add to lookUp
                            lookUp[newStone] = Stone(newStone);
                        }
                        nextStones.push_back(&(lookUp[newStone]));

                        // second half of stone
                        newStone = stoull(num.substr(half));
                        if(lookUp.find(newStone) == lookUp.end()) {
                            lookUp[newStone] = Stone(newStone);
                        }
                        nextStones.push_back(&(lookUp[newStone]));
                    }
                    else { // mult by 2024
                        unsigned long long newStone = currStone.number * 2024;
                        if(lookUp.find(newStone) == lookUp.end()) {
                            lookUp[newStone] = Stone(newStone);
                        }
                        nextStones.push_back(&(lookUp[newStone]));
                    }
                }
                currStone.next = nextStones;
            }
            else { // if already mapped
                nextStones = currStone.next;
            }

            // add newly created stones to newStones
            for(Stone* s : nextStones) {
                newStones[s->number] += 1 * stone.second;
            }
        }
        stones = newStones;
    }

    // // Comment/Uncomment to see the total number of each stone
    // cout << "after " << BLINKS << " blinks" << endl;
    // for(const pair<unsigned long long, unsigned long long>& stone : stones) {
    //     cout << "stone " << stone.first << ": " << stone.second << endl;
    // }
    // cout << endl;

    for(const pair<unsigned long long, unsigned long long>& stone : stones) {
        sum += stone.second;
    }

    cout << sum << " stones after 25 blinks" << endl;

    return 0;
}