#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long ll;

const ll mod = 1000000007;
const int inf = 20;
bool col[16][16][16];


struct Vec2
{
	int x, y;
	Vec2(int x=0, int y=0) {this->x = x; this->y = y;}
	Vec2 operator - (const Vec2 &v){return Vec2(x-v.x, y-v.y);}
} 
p[100];

int cross(Vec2 v1, Vec2 v2){ return v1.x*v2.y - v1.y*v2.x; }
bool collinear(int i, int j, int k){ return (cross(p[i] - p[j], p[i]-p[k])==0); }
bool one[1<<16];
int firstOne[1<<16];

//number of ways to solve a mask
int minT[1<<16];
ll cnt[1<<16];

// return the min number of turns
void calcMinTurn(int n)
{
	minT[0] = 0;
	for(int mask = 1; mask<(1<<n); mask++)
	{
		if(one[mask])
		{
			minT[mask] = 1;
			continue;
		}

		minT[mask] = inf;

		int i = firstOne[mask];
		{
			for(int j=i+1; j<n; j++)
			{
				if(i==j)
					continue;

				//remove all points that are on line pi--pj
				int newMask = mask;
				for(int k=0; k<n; k++)
					if(col[i][j][k])
						newMask &= ~(1<<k);

				minT[mask] = min( minT[mask], minT[newMask] + 1 );
			}
		}
	}
}

ll countBest(int mask, int n)
{
	ll &result = cnt[mask];
	if(result != -1)
		return result;

	if(mask==0)
		return result = 1;

	result = 0;

	int i = firstOne[mask];
	{
		{
			int newMask = mask & ~(1<<i);
			if(minT[mask] == minT[newMask]+1)
				result += countBest(newMask, n);
		}
		for(int j=i+1; j<n; j++)
			if( mask & (1<<j) )
			{
				// add all the points that lie on line pi--pj
				int potMask = 0;
				bool skip = false;
				for(int k=0; k<n; k++)
				{
					if(col[i][j][k] && (mask & (1<<k)))
					{
						if(k < i || k > j)
						{
							skip = true;
							break;
						}
						potMask |= 1<<k;
					}
				}
				if(skip)
					continue;

				//iterate all subsets of potMask
				for( int m = potMask; m!=0; m = (m-1) & potMask )
				{
					if( one[m] || ((1<<i)&m)==0 )
						continue;

					//newMask = remaining points
					int newMask = mask & ~(m);
					if(minT[mask] == minT[newMask]+1)
					{
						result += countBest(newMask, n);
					}
				}

			}
	}
	return result;
}

ll fact(ll num)
{
	ll res = 1;
	for(ll i=2; i<=num; i++)
		res = (res * i) % mod;
	return res; 
}

int main()
{
	int tc;
	cin>>tc;

	memset(one, 0, sizeof one);
	for(int i=0; i<16; i++)
		one[1<<i] = true;

	firstOne[0] = -1;
	for(int i=1; i<(1<<16); i++)
	{
		for(int j=0; j<16; j++)
			if(i & (1<<j))
			{
				firstOne[i] = j;
				break;
			}

	}

	while(tc--)
	{
		int n;
		cin>>n;
		for(int i=0; i<n; i++)
			cin>>p[i].x>>p[i].y;

		if(n==1)
		{
			cout<<1<<" "<<1<<endl;
			continue;
		}

		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				for(int k=0; k<n; k++)
					col[i][j][k] = collinear(i,j,k);
		calcMinTurn(n);

		int minTurns = minT[(1<<n)-1];

		memset(cnt, -1, sizeof cnt);
		int minTurnsCount = countBest((1<<n)-1, n);

		cout << minTurns << " " << minTurnsCount*fact(minTurns) << endl;
	}
	return 0;
}
