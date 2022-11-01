//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

using Island = int;
using Happiness = int;
using Bridge = pair<Island, Island>;

const int NUM_BRIDGE_COMPANIES = 2;

enum BridgeCompany { RED, BLUE };
BridgeCompany stobc(string const& s){
	if(s == "red") return RED;
	else return BLUE;
}


vector<int> range(int n){
	vector<int> v(n);
	for(int i = 0; i <n; i++) v[i] = i;
	return v;
}

template <typename T>
class UFDS{
private:
	using Index = int;
	vector<T> elements;
	vector<int> parents;
	vector<int> rank;
	int num_sets;
public:
	UFDS(vector<T> const& v) 
	: elements(v.size()), rank(v.size(),0), num_sets(v.size()) {
		parents = range(v.size());
		copy(v.begin(),v.end(), elements.begin());
	}

	int size() const {
		return num_sets;
	}
	Index find(Index n) {
		return parents[n] = (parents[n] == n? n : find(parents[n]));
	}
	Index join(Index x, Index y){
		Index rx = find(x);
		Index ry = find(y);
		
		// Suppose that the representative of x has the lowest rank
		if(rank[rx] > rank[ry])
			swap(rx,ry);

		// Increase rank of y if it must grow
		rank[ry] += int(rank[ry] == rank[rx]);
		return parents[ry] = rx;
	}
};

vector<int> solve(int n, vector<priority_queue<pair<Happiness,Bridge>>> bridges){
	vector<int> results(NUM_BRIDGE_COMPANIES, 0);
	UFDS<int> ufds(range(n));
	for(int company = 0; company < NUM_BRIDGE_COMPANIES; company++){
		while(!bridges[company].empty()){
			auto [happiness, bridge] = bridges[company].top();
			auto [a, b] = bridge;
			bridges[company].pop();

			if(ufds.find(a) != ufds.find(b)){
				ufds.join(a,b);
				results[company] += happiness;
			}
		}
	}
	return results;
}

int main() {
	int n, m; 
	while(cin >> n >> m){ // n,m ∈ [1,1e5]
		vector<priority_queue<pair<Happiness,Bridge>>> bridges(NUM_BRIDGE_COMPANIES);
		for(int _ = 0; _ < m; _++){
			int a, b, c; cin >> a >> b >> c;
			a--; b--; // We are 0-indexed here
			string s; cin >> s;
			BridgeCompany company = stobc(s);
			bridges[company].push({c, {a,b}});
		}

		vector<int> sols = solve(n,bridges);
		for(int i = 0; i < NUM_BRIDGE_COMPANIES; i++){
			cout << sols[i] << " ";
		}
		cout << '\n';
	}
	return 0;
}

