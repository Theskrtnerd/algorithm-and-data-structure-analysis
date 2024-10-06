#include <bits/stdc++.h>

using namespace std;

class DSU { 
public: 
    int* parent; 
    int* rank; 
    DSU(int n) 
    { 
        parent = new int[n]; 
        rank = new int[n]; 
  
        for (int i = 0; i < n; i++) { 
            parent[i] = i; // Initialize each node to be its own parent
            rank[i] = 1; 
        } 
    } 
  
    int find(int i) 
    { 
        if (parent[i] == i) 
            return i; 
  
        return parent[i] = find(parent[i]); 
    } 
  
    void unite(int x, int y) 
    { 
        int s1 = find(x); 
        int s2 = find(y); 
  
        if (s1 != s2) { 
            if (rank[s1] < rank[s2]) { 
                parent[s1] = s2; 
            } 
            else if (rank[s1] > rank[s2]) { 
                parent[s2] = s1; 
            } 
            else { 
                parent[s2] = s1; 
                rank[s1] += 1; 
            } 
        } 
    } 
}; 

int main() {
    // Problem Setup
    string country_str, build_str, destroy_str;
    cin >> country_str >> build_str >> destroy_str;
    int N = count(country_str.begin(), country_str.end(), ',') + 1;
    vector<vector<int>> country(N, vector<int>(N));
    vector<vector<int>> build(N, vector<int>(N));
    vector<vector<int>> destroy(N, vector<int>(N));
    vector<vector<int>> costs(N, vector<int>(N));
    stringstream country_ss(country_str);
    stringstream build_ss(build_str);
    stringstream destroy_ss(destroy_str);
    string temp;
    for (int i = 0; i < N; ++i) {
        getline(country_ss, temp, ',');
        for (int j = 0; j < N; ++j) {
            country[i][j] = temp[j] - '0';
        }
    }
    for (int i = 0; i < N; ++i) {
        getline(build_ss, temp, ',');
        for (int j = 0; j < N; ++j) {
            build[i][j] = temp[j] - 'A';
        }
    }
    for (int i = 0; i < N; ++i) {
        getline(destroy_ss, temp, ',');
        for (int j = 0; j < N; ++j) {
            destroy[i][j] = temp[j] - 'A';
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (country[i][j] == 0) {
                costs[i][j] = build[i][j];
            } else {
                costs[i][j] = destroy[i][j];
            }
        }
    }

    // Kruskal's Algorithm
    int ans = 0;
    vector<pair<int, pair<int, int>>> bu_edges;
    vector<pair<int, pair<int, int>>> de_edges;


    for(int i = 0; i < N; ++i) {
        for(int j = i+1; j <N; ++j) {
            if (country[i][j] == 1) {
                de_edges.push_back({costs[i][j], {i, j}});
            }
            else {
                bu_edges.push_back({costs[i][j], {i, j}});
            }
        }
    }
    sort(bu_edges.begin(), bu_edges.end());
    sort(de_edges.begin(), de_edges.end(), greater<pair<int, pair<int, int>>>());

    DSU dsu(N);

    for(auto edge: de_edges) {
        int w = edge.first;
        int x = edge.second.first;
        int y = edge.second.second;
        if (dsu.find(x) != dsu.find(y)) {
            dsu.unite(x, y);
        }
        else {
            ans += w;
        }
    }

    for(auto edge: bu_edges) {
        int w = edge.first;
        int x = edge.second.first;
        int y = edge.second.second;
        if (dsu.find(x) != dsu.find(y)) {
            dsu.unite(x, y);
            ans += w;
        }
    }

    std::cout << ans << endl;

    return 0;
}