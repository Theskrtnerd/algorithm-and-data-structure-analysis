#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<pair<string, string>> v(26, {"", "never used"});
    string input;
    getline(cin, input);
    istringstream iss(input);
    string word;

    while (iss >> word) {
        char operation = word[0];
        string value = word.substr(1);

        if (operation == 'A') {
            int t = value[value.length()-1] - 'a';
            while(v[t].second == "occupied") {
                if (v[t].first == value) {
                    break;
                }
                else {
                    t = (t + 1) % 26;
                }
            }
            v[t].first = value;
            v[t].second = "occupied";
        } else if (operation == 'D') {
            int t = value[value.length()-1] - 'a';
            int start = t;
            while(v[t].first != value) {
                if (v[t].second == "never used") {
                    break;
                }
                else {
                    t = (t + 1) % 26;
                    if (t == start) {
                        break;
                    }
                }
            }
            if(v[t].first == value) {
                v[t].second = "tombstone";
            }
        }
    }

    for (const auto& p : v) {
        if (p.second == "occupied") {
            cout << p.first << " ";
        }
    }
    cout << endl;
    return 0;
}