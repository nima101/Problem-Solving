
#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <cstdio>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long ll;

int main()
{
	const ll mod = 1000007;

	ll N;
	cin>>N;

	vector<ll> v;
	bool prime[1000001]; for(int i=0; i<=1000000; i++) prime[i]=true;
	for(ll i=2; i<=N; i++)
		if(prime[i])
		{
			v.push_back(i);
			for(ll j=2*i; j<=N; j+=i)
				prime[j] = false;
		}

		ll res = 1;
		for(ll i=0; i<v.size(); i++)
		{
			ll cur = 0;
			for(ll p=v[i]; p<=N; p*=v[i])
				cur = (cur + N/p) % mod;
			res = (res * ((2*cur+1)%mod)) % mod;
		}

		return res;
}
