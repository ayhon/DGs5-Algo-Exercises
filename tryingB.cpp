//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

using Vertex = int;
using Weight = int;
using Edge = pair<Vertex,Vertex>;
using AdjList = vector<set<Vertex>>;
struct WeightedEdge: pair<Edge,Weight> {
	Vertex first;
	Vertex end;
	Weight weight;
	WeightedEdge(Edge p, Weight w) pair<Edge,Wieght>{
		super(p.first,p.end);
	}
};

const int INFTY = INT_MAX;
const int AIRPORTS_COST = 2;
const int TRAINS_COST = 1;

template <typename T>
class UFDS{
private:
	using Index = int;
	vector<T> elements;
	vector<int> parents;
	vector<int> rank;
	int num_sets;
	vector<int> range(int n){
		vector<int> v(n);
		for(Index i = 0; i <n; i++) v[i] = i;
		return v;
	}
public:
	UFDS<int>(int n) : UFDS(range(n)){}
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
		Index px = find(x);
		Index py = find(y);
		
		// Suppose that x has the highest rank
		if(rank[x] < rank[y]){
			swap(x,y);
			swap(px,py);
		}

		// Increase rank of y if it must grow
		rank[y] += int(rank[y] == rank[x]);
		return parents[y] = px;
	}
};

vector<Edge> Kruskal(int num_cities, set<Vertex> const& airporsts, vector<Edge> const& train_routes){
	vector<Edge> paths;
	UFDS<Vertex> ufds(num_cities);
	for(auto & route : train_routes){
		if(ufds.size() == 1) break;

		auto [u,v] = route;
		if(ufds.find(u) != ufds.find(v))
			paths.push_back(route);
	}

	if(ufds.size() != 1){
		for(Vertex
	}

	if(ufds.size() != 1) 
		return {};
	else 
		return paths;
}

string solve(int num_cities, int source, int target, set<Vertex> const& airports, vector<Edge> const& train_routes){
	vector<Edge> paths = Kruskal(num_cities, airports, train_routes);
}

string solve2(int num_cities, int source, int target, set<Vertex> const& airports, vector<Edge> const& train_routes){
	// TODO: Take only the minimum spanning tree

	AdjList by_train(num_cities);
	for(Edge const& route : train_routes){ // O(m)
		auto const& [u,v] = route;
		by_train[u].insert(v);
		by_train[v].insert(u);
	}

	vector<Weight> distance(num_cities, INFTY);
	distance[source] = 0;

	using Node = pair<Vertex, Weight>;
	priority_queue<Node, vector<Node>, greater<Node>> toVisit;

	toVisit.push({0,source});
	while(!toVisit.empty()){ // O(m + k + n)
		auto [curr_cost, curr_city] = toVisit.top();
		toVisit.pop();

		if(curr_city == target) return to_string(curr_cost);

		if(distance[curr_city] < curr_cost) continue;

		// Consider cities accesible by train
		for (Vertex const& neigh_city : by_train[curr_city]){ // O(m)
			Weight neigh_cost = curr_cost + TRAINS_COST;
			if (neigh_cost < distance[neigh_city]){
				distance[neigh_city] = neigh_cost;
				toVisit.push({distance[neigh_city], neigh_city});
			}
		}

		auto it = airports.find(curr_city);
		if(it != airports.end()) { // curr_city is an airport 
			// Consider other airports
			for(Vertex const& airport : airports){ // O(m)
				Weight airport_cost = curr_cost + AIRPORTS_COST;
				if (airport_cost < distance[airport]){
					distance[airport] = airport_cost;
					toVisit.push({distance[airport], airport});
				}
			}
		}
	}
	return "Impossible";
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	Vertex s, t;
	cin >> s >> t;
	s--; t--; // We are 0-indexed here

	set<Vertex> airports;
	for(int _ = 0; _ < k; _++) {
		Vertex airport;
		cin >> airport;
		airport--; // We are 0-indexed here
		airports.insert(airport);
	}

	vector<Edge> train_routes(m);
	for(Edge & route : train_routes){
		cin >> route.first >> route.second;
		route.first --; route.second--; // We are 0-indexed here
	}

	cout << solve(n,s,t,airports,train_routes) << '\n';
	return 0;
}

