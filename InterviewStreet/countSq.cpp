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

const int maxn = 205;
const ll mod = 1000000007;

ll dp[maxn][maxn][maxn];
int last1[maxn], last2[maxn];

ll countSq (const string &s, int i1, int i2, int i1_end)
{
	ll &res = dp[i1][i2][i1_end];
	if(res!=-1) return res;
	
	//if(i1==i1_end && i2==s.size())
	//	return 1;
	if(i1==i1_end || i2==s.size())
		return res=1;
	
	res = 0;

//	if(s[i1]!=s[i2]){
	res += countSq ( s, i1+1, i2, i1_end );
	res += countSq ( s, i1, i2+1, i1_end );
	res -= countSq ( s, i1+1, i2+1, i1_end ); 
//	} else
	res += countSq ( s, i1+1, i2+1, i1_end) * ( 1 + (s[i1]==s[i2]) );

	res %= mod;
	return res;
}

int main()
{	
	int tc, N;
	cin>>tc;
	string line;
	getline(cin, line);

	while(tc--)
	{
		getline(cin, line);
		memset(dp, -1, sizeof dp);
		ll res = 0;
		for(int i1=0; i1<line.size(); i1++)
			for(int i2=i1+1; i2<line.size(); i2++)
				if(line[i1]==line[i2])
					res = (res + countSq(line, i1+1, i2+1, i2))%mod;
		cout << res << endl ;
	}
	return 0;
}
