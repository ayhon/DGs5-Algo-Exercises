//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

using Vertex = int;
using Weight = int;
using Edge = pair<Vertex,Vertex>;
using AdjList = vector<set<Vertex>>;

const int AIRPORTS_COST = 2;
const int TRAINS_COST = 1;

string solve(int num_cities, int source, int target, vector<int> const& is_airport, vector<Edge> const& train_routes){
	AdjList graph(num_cities);
	for(auto const& [u, v] : train_routes){
		graph[u].insert(v);
		graph[v].insert(u);
	}
	queue<pair<Vertex,int>> source_search;
	int source_distance_stop = -1;
	source_search.push({source,0});
	while(!source_search.empty()){
		auto const& [curr_city, curr_distance] = source_search.front();

		if(curr_city == target) return to_string(curr_distance);
		if(curr_distance == source_distance_stop) break;
		if(is_airport[curr_city]) source_distance_stop = curr_distance + 1;

		for(Vertex neigh_city : graph[curr_city])
			source_search.push({neigh_city, curr_distance + TRAINS_COST});

		source_search.pop();
	}
	if(source_distance_stop == -1) return "Impossible";

	vector<int> is_border_city(num_cities, 0);
	for(Vertex border_city = source_search.front().first; !source_search.empty(); source_search.pop())
		is_border_city[border_city] = 1;

	queue<pair<Vertex,int>> target_search;
	int target_distance_stop = -1;
	target_search.push({source,0});
	while(!target_search.empty()){
		auto [curr_city, curr_distance] = target_search.front();

		if(curr_distance == target_distance_stop) break;
		if(is_airport[curr_city]) target_distance_stop = curr_distance + AIRPORTS_COST-1;
		if(is_border_city[curr_city]) return to_string(curr_distance + source_distance_stop);

		for(Vertex neigh_city : graph[curr_city])
			target_search.push({neigh_city, curr_distance + TRAINS_COST});

		target_search.pop();
	}
	if(target_distance_stop == -1) return "Impossible"; // This one should actually never trigger.
	else return to_string(source_distance_stop + target_distance_stop);
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	Vertex s, t;
	cin >> s >> t;
	s--; t--; // We are 0-indexed here

	vector<int> is_airport(n,0);
	for(int _ = 0; _ < k; _++) {
		Vertex airport;
		cin >> airport;
		airport--; // We are 0-indexed here
		is_airport[airport] = 1;
	}

	vector<Edge> train_routes(m);
	for(Edge & route : train_routes){
		cin >> route.first >> route.second;
		route.first --; route.second--; // We are 0-indexed here
	}

	cout << solve(n,s,t,is_airport,train_routes) << '\n';
	return 0;
}

