//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

using Vertex = int;
using Weight = int;
using Edge = pair<Vertex,Vertex>;
using AdjList = vector<set<Vertex>>;

const int INFTY = 1e7;
const int AIRPORTS_COST = 2;
const int TRAINS_COST = 1;

Weight bfs(AdjList const& graph, Vertex origin, function<bool(Vertex)> break_condition){
	// Initialize queue and set all vertices as unvisited
	queue<pair<Vertex,Weight>> q;
	vector<int> visited(graph.size(), 0);

	// Introduce the origin as a candidate
	q.push({origin,0});

	// Start processing the candidates
	while(!q.empty()){
		// Get current node
		auto [curr, dist] = q.front();
		q.pop();

		// Ignore if visited, mark if not
		if(visited[curr]) continue;
		else visited[curr] = true;

		// If break_condition, return the current distance
		if(break_condition(curr)) return dist;

		// Push all unvisited neighbours
		for(Vertex neigh : graph[curr])
			if(!visited[neigh]) 
				q.push({neigh,dist + TRAINS_COST});
	}
	return INFTY;
}

string solve(int num_cities, int source, int target, vector<int> const& is_airport, vector<Edge> const& train_routes){
	// Create train rails graph
	AdjList graph(num_cities);
	for(auto const& [u, v] : train_routes){
		graph[u].insert(v);
		graph[v].insert(u);
	}

	Weight source_to_airport = bfs(graph, source, [is_airport](Vertex v){ return is_airport[v];});
	Weight source_to_target = bfs(graph, source, [target](Vertex v){ return v == target;});
	Weight target_to_airport = bfs(graph, target, [is_airport](Vertex v){ return is_airport[v];});
	
	int res = min(source_to_airport + target_to_airport + AIRPORTS_COST, source_to_target);
	return (res >= INFTY? "Impossible" : to_string(res));
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

