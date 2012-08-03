#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <set>
#include <fstream>
#include <sstream>

using namespace std;

#define M 1005
bool graph[M][M];
bool seen[M];
int matchL[M], matchR[M];
int n, k;

bool bpm( int u )
{
	for( int i = 0; i < n; i++ ) if( graph[u][i] )
	{
		if( seen[i] ) continue;
		seen[i] = true;

		if( matchR[i] < 0 || bpm( matchR[i] ) )
		{
			matchL[u] = i;
			matchR[i] = u;
			return true;
		}
	}
	return false;
}

int v[1005];

int main()
{
	int tc;
	cin>>tc;

	while(tc--)
	{
		cin >> n >> k;
		for(int i=0; i<n; i++)
			cin >> v[i];

		memset( matchL, -1, sizeof( matchL ) );
		memset( matchR, -1, sizeof( matchR ) );
		memset( graph ,  0, sizeof( graph  ) );

		//creating the bipartite DAG
		for(int i=0; i<n; i++)
			for(int j=i+1; j<n; j++)
				if( abs(v[j] - v[i]) >= k )
					graph[i][j] = 1;
	
		//find matching to solve path cover
		int cnt = 0;
		for( int i = 0; i < n; i++ )
		{
			memset( seen, 0, sizeof( seen ) );
			if( bpm( i ) ) cnt++;
		}

		cout << n - cnt << endl;
	}
	return 0;
}
