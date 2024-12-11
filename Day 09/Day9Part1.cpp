#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// programmer hell

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    unsigned long long sum = 0; // big number today

    getline(in, line);
    size_t size = line.size();

    int currID = 0;
    int endID = (size + 1) / 2; // the ID range is half of the total size (other half is gaps)
    int queue = 0; // buffer for unassigned file blocks

    int pos = 0; // current position from left
    int endPos = size - 1; // current position from right
    for(int i = 0; i < size && i <= endPos; ++i) {
        int curr = line[i] - '0'; // length of current file
        
        // add left file blocks to sum
        for(int j = pos + curr; pos < j; ++pos) {
            sum += currID * pos;
        }
        ++currID;
        ++i;

        if(i >= endPos) {
            break;
        }

        // get current gap, fill with file blocks from right side
        curr = line[i] - '0';
        for(int j = pos + curr; pos < j; ++pos) {
            // if nothing left in queue refill with rightmost file
            if(queue == 0) {
                queue = line[endPos] - '0';
                --endID;
                endPos -= 2;
            }

            // take one from queue and put it in gap
            sum += endID * pos;
            --queue;
        }
    }

    // deal with possible overflow of file blocks, just add to end
    for(int i = 0; i < queue; ++i) {
        sum += endID * pos;
        ++pos;
    }

    cout << "Filesystem checksum: " << sum << endl;

    return 0;
}