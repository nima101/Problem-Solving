#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <set>
#include <sstream>
#include <cmath>

using namespace std;

typedef long long ll;

const ll mod = 1000000000;
const int maxn = 10005;
int n, m;

vector<int> adj[maxn], radj[maxn];
enum VColor {black=0, gray, white};
VColor vcol[maxn];
ll dp[maxn];

bool loopFound;

//reverse dfs to throw away useless nodes
void rdfs(int v)
{
	vcol[v] = white;
	for(int i=0; i<radj[v].size(); i++)
		if(vcol[radj[v][i]] == black)
			rdfs(radj[v][i]);
}

//dfs to solve
ll dfs(int v)
{
	if(vcol[v]==gray)
	{
		loopFound = true;
		return 0;
	}

	if(vcol[v]==black)
		return dp[v];

	if(v == n-1) //destination
	{
		vcol[v] = black;
		return dp[v] = 1;
	}

	vcol[v] = gray;

	ll res = 0;
	for(int i=0; i<adj[v].size(); i++)
		res = (res + dfs(adj[v][i])) % mod;

	vcol[v] = black;

	return dp[v] = res;
}

int main()
{
	cin>>n>>m;
	memset(vcol, 0, sizeof vcol);
	memset(dp, 0, sizeof dp);
	for(int i=0; i<m; i++)
	{
		int aa, bb;
		cin>>aa>>bb;
		adj[aa-1].push_back(bb-1);
		radj[bb-1].push_back(aa-1);
	}

	loopFound = false;
	
	rdfs(n-1);
	ll res = dfs(0);

	if(vcol[n-1] == white)
		cout<< 0 <<endl;
	else
		if(loopFound)
			cout << "INFINITE PATHS" <<endl;
		else
			cout << res << endl;

	return 0;
}
