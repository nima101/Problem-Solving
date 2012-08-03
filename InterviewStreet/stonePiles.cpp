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

const int maxn = 51;
int grundy[maxn];
set<int> zeroSet;
set<int> gSet[maxn][maxn];

set<int> grundySet(int n, int low)
{
	set<int> &result = gSet[n][low];
	if(result.size()!=0)
		return result;
	if(n==0)
		return zeroSet;

	set<int> res;
	for(int i=low; i+i<n; i++)
	{
		set<int> cur = grundySet ( n - i , i + 1 );
		for(set<int>::iterator it = cur.begin(); it!=cur.end(); ++it)
			res.insert((*it) ^ grundy[i]);
	}
	if(low > 1)
		res.insert(grundy[n]);
	return result = res;
}

int main()
{
	zeroSet.insert(0);
	int tc;
	cin>>tc;

	grundy[0] = grundy[1] = grundy [2] = 0;
	for(int i=3; i<maxn; i++)
	{
		set<int> s = grundySet(i, 1);
		grundy[i] = 0;
		while( s.find(grundy[i]) != s.end() )
			++ grundy[i];
	}

	while(tc--)
	{
		int n, tot=0;
		cin>>n;
		for(int i=1; i<=n; i++)
		{
			int stones;
			cin >> stones;
			tot ^= grundy[stones];
		}
		if(tot != 0)
			cout << "ALICE" << endl;
		else
			cout << "BOB" << endl;
	}
	return 0;
}
