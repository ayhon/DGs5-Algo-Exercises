//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;
/*
I: n c e 	# n <= 500; c,e <= 100
n↓ ai bi	# ai,bi <= 100

O: "Yes" | "No"
*/
const int MAX_MONEY = 100;
const int MAX_CALORIES = 100;
const int MAX_PRODUCTS = 500;

using Info = pair<int,int>;
int cost(Info const& info){ return info.first; }
int caloric_value(Info const& info){ return info.second; }

using vi = vector<int>;
using vvi = vector<vector<int>>;
vector<vvi> memo;
// memo[money][calories][from]
bool possible(int money, int calories, int curr, vector<Info> const& products){
	// BASE CASES
	if (money == 0 && calories == 0)
		return true;
	else if(money < 0 || calories < 0 || curr >= products.size())
		return false;

	// RECURSIVE CASE
	if(memo[money][calories][curr] == -1){
		memo[money][calories][curr] = 
			possible   (money - cost(products[curr]), calories - caloric_value(products[curr]), curr+1, products) 
			|| possible(money                       , calories                                , curr+1, products);
	}
	return (bool)memo[money][calories][curr];
}

int poss[MAX_MONEY+1][MAX_CALORIES+1];
bool bottom_up(vector<Info> const& info, int money, int calories){
	memset(poss, 0, (money+1)*(1+calories)*sizeof(int));

	poss[0][0] = 1;
	for(int m = 0; m <= money; m++)
		for(int c = 0; c <= calories; c++)
			if (poss[m][c]) 
				for(int i = 0; i < info.size(); i++) {
					const int x = m + info[i].first, 
							  y = c + info[i].second;	
					if(x <= money && y <= calories)
						poss[x][y] = 1;
				}

	return poss[money][calories];
}

bool solve(vector<Info> const& info, int money, int calories) {
	memo.clear();
	memo.resize(money+1, vvi(calories+1, vi(info.size(), -1))); 

	return possible(money, calories, 0, info);
}

int main() {
	ios::sync_with_stdio(false);

	int n, c, e;
	while(cin >> n >> c >> e){
		vector<Info> info(n); // first → cost, second → caloric value
		for(Info & p : info)
			cin >> p.first >> p.second;

		/* cout << (solve(info, c, e)? "Yes" : "No") << '\n'; */
		cout << (bottom_up(info, c, e)? "Yes" : "No") << '\n';
	}
	return 0;
}
