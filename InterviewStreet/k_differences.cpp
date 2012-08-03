#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;

int main()
{
	ll n, k;
	cin >> n >> k;
	map<ll, ll> m;
	vector<ll> v (n);
	for(int i=0; i<n; i++) 
	{
		cin>>v[i];
		m[v[i]] = m[v[i]]+1;
	}

	ll res = 0;
	for(map<ll,ll>::iterator it=m.begin(); it!=m.end(); ++it)
	{
		if(m.find(it->first + k) != m.end())
			res += m[it->first + k] * it->second;
		if(m.find(it->first - k) != m.end())
			res += m[it->first - k] * it->second;
	}
	cout<<res/2<<endl;
	return 0;
}