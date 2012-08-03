#include <iostream>
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
const int maxn = 100005;
int N; 

int x[maxn], y[maxn];

int dist(int i, int j) { return max(abs(x[i]-x[j]), abs(y[i]-y[j])); }

ll cost(int id)
{
	ll res = 0;
	for(int i=0; i<N; i++)
		res += (ll)dist(id, i);
	return res;
}

int main()
{
	double sumx=0, sumy=0;
	scanf("%d", &N);
	for(int i=0; i<N; i++)
	{
		scanf("%d", &(x[i]));
		scanf("%d", &(y[i]));
		sumx += x[i];
		sumy += y[i];
	}
	double meanx = sumx/N;
	double meany = sumy/N;

	vector< pair<double, int> > dists;
	set < pair<int, int> > houses;

	for(int i=0; i<N; i++)
	{
		if( houses.find(make_pair(x[i], y[i])) == houses.end() )
		{
			dists.push_back(make_pair( max( fabs( (double)(x[i]) - meanx ) , fabs( (double)(y[i]) - meany ) ) , i ));
			houses.insert( make_pair( x[i] , y[i] ) );
		}
	}
	

	sort(dists.begin(), dists.end());

	ll res = -1;
	int maxi = min(1000, (int)houses.size());
	for(int i=0; i<maxi; i++)
	{
		ll cur = cost(dists[i].second);
		if( res < 0 || res > cur )
			res = cur;
	}

	cout<<res<<endl;

	return 0;
}