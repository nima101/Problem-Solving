#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <set>

using namespace std;

typedef long long ll;
const int maxn = 1005;
const ll mod = 1000000007;

inline ll add(ll a, ll b) { return (a+b)%mod;     }
inline ll sub(ll a, ll b) { return (a-b+mod)%mod; }
inline ll mul(ll a, ll b) { return (a*b)%mod;     }

ll one[maxn], all[maxn], solid[maxn], gap[maxn];

ll power(ll base, ll p)
{
	if(p==0)
		return 1;
	ll res = power(base, p/2);
	res = mul(res, res);
	if(p%2==1)
		res = mul(res, base);
	return res;
}

int main()
{
	int tc;
	cin>>tc;

	memset(one, 0, sizeof one); one[0] = 1;
	for(int i=1; i<maxn; i++)
		for(int j=1; j<=4; j++)
			if(i-j>=0) 
				one[i] = add( one[i], one[i-j] );

	while(tc--)
	{
		int h, w;
		cin >> h >> w;

		for(int i=1; i<maxn; i++)
			all[i] = power(one[i], h);

		memset(gap, 0, sizeof gap);

		gap[1] = 0;	solid[1] = 1;
		for(int i=2; i<=w; i++)
		{
			gap[i] = 0;

			for(int j=1; j<i; j++)
				gap[i] = add (gap[i], mul(solid[j], all[i-j]) );

			solid[i] = sub ( all[i], gap[i] ) ;
		}

		cout<<solid[w]<<endl;
	}
	return 0;
}
