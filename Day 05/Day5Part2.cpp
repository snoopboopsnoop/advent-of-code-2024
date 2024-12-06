#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// big day

struct Page {
    int page = 0; // page number of this page
    vector<int> before; // contains all pages that need to come after this page (this page before all pages in this vector)

    Page(int pageNum) {
        page = pageNum;
    }

    int getPage() const {
        return page;
    }

    void addPageBefore(int pageNum) {
        before.push_back(pageNum);
    }

    // returns true if this page comes before pageNum
    bool findBefore(int pageNum) const {
        if(find(before.begin(), before.end(), pageNum) != before.end()) {
            return true;
        }
        else return false;
    }

    void print() const {
        cout << page << " comes before ";
        for(int i : before) {
            cout << i << ", ";
        }
        cout << endl;
    }
};

// returns true if update is in correct ordering
bool checkUpdate(const vector<int>& update, const vector<Page>& pages) {
    int updateSize = update.size();
    for(int i = 0; i < updateSize; ++i) {
        const auto it = find_if(pages.begin(), pages.end(), [update, i](const Page& p){ return p.getPage() == update[i];});
        for(int j = i + 1; j < updateSize; ++j) {
            if(it->findBefore(update[j])) {
                return false;
            }
        }
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

    vector<Page> pages;
    vector<vector<int>> updates;

    while(in) {
        // create page structs based on input rule
        while(getline(in, line)) {
            if(line == "") break;

            int barPos = line.find("|");
            // first | second
            int first = stoi(line.substr(0, barPos));
            int second = stoi(line.substr(barPos+1));

            const auto it = find_if(pages.begin(), pages.end(), [second](const Page& p) { return (p.getPage() == second);});
            // if page does not exist, create new one
            if(it == pages.end()) {
                Page newPage = Page(second);
                newPage.addPageBefore(first);
                pages.push_back(newPage);
            }
            // set rule
            else {
                it->addPageBefore(first);
            }
        }

        // go through updates, send to updates vector
        while(getline(in, line)) {
            istringstream stream(line);
            string token;
            vector<int> update;
            while(getline(stream, token, ',')) {
                update.push_back(stoi(token));
            }

            updates.push_back(update);
        }
    }

    // prints rules
    for(const Page& p : pages) {
        p.print();
    }
    cout << endl;

    // prints valid vectors, sorts and prints invalid vectors
    for(vector<int>& v : updates) {
        cout << "(";
        for(int i = 0; i < v.size(); i++) {
            if(i == 0) {
                cout << v[i];
            }
            else cout << ", " << v[i];
        }
        cout << ") ";

        if(checkUpdate(v, pages)) {
            cout << "[VALID]" << endl;
        }
        else {
            cout << "[INVALID, SORTING]" << endl;
            // resort based on "before" values
            sort(v.begin(), v.end(), [pages](int a, int b) {
                const auto itb = find_if(pages.begin(), pages.end(), [b](const Page& p){ return p.getPage() == b;});
                
                return itb->findBefore(a);
            });

            cout << "[SORTED] (";
            for(int i = 0; i < v.size(); i++) {
                if(i == 0) {
                    cout << v[i];
                }
                else cout << ", " << v[i];
            }
            cout << ") " << endl;

            sum += v[v.size()/2];
        }
    }
    cout << endl;

    cout << "Sum of middles of invalid (and resorted) updates: " << sum << endl;

    return 0;
}