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
const int maxn = 1002;
ll choose[maxn][maxn];

ll add(ll aa, ll bb) {return (aa+bb)%mod;}
ll sub(ll aa, ll bb) {return (aa-bb+mod)%mod;}

ll waysToSum[1001][1001];
ll periodicCount(int n, int k, const string &word, int L/*period length*/)
{
	int h = n/L;
	vector<int> change(L);
	for(int i=0; i<L; i++)
		for(int j=i; j<n; j+=L)
			change[i] += (word[j]=='1');

	for(int sum=0; sum<=k; sum++)
		waysToSum[sum][0] = (change[0]<=sum) + (h-change[0]<=sum);

	for(int i=1; i<L; i++)
		waysToSum[0][i] = (change[i]<=0)*(waysToSum[0][i-1]) + (h-change[i]<=0)*(waysToSum[0][i-1]);
		
	for(int sum=1; sum<=k; sum++)
		for(int i=1; i<L; i++)
		{
			waysToSum[sum][i] = 0;
			if(change[i]<=sum)   waysToSum[sum][i] = add ( waysToSum[sum][i] , waysToSum[  sum-change[i]  ][i-1] );
			if(h-change[i]<=sum) waysToSum[sum][i] = add ( waysToSum[sum][i] , waysToSum[sum-(h-change[i])][i-1] );
		}

	return waysToSum[k][L-1];
}

ll solve(int n, int k, const string &word)
{
	vector<int> divisors;
	for(int i=1; i<=n/2; i++)
		if(n%i==0)
			divisors.push_back(i);

	ll all = 0;
	for(int i=0; i<=k; i++) all = add(all, choose[n][i]);

	ll periodic[maxn]; 
	for(int i=0; i<divisors.size(); i++)
		periodic[i] = periodicCount(n, k, word, divisors[i]) ;

	for(int i=0; i<divisors.size(); i++)
		for(int j=0; j<i; j++)
			if(divisors[i] % divisors[j]==0)
				periodic[i] -= periodic[j];

	ll allp = 0;
	for(int i=0; i<divisors.size(); i++)
		allp = add(allp, periodic[i]);

	return sub(all, allp);
}

int main()
{
	int tc=1;
	cin>>tc;

	for(int i=1; i<maxn; i++)
		choose[i][i] = choose[i][0] = 1;
	for(int i=1; i<maxn; i++)
		for(int j=1; j<i; j++)
			choose[i][j] = add(choose[i-1][j-1], choose[i-1][j]);

	while(tc--)
	{
		string word;
		int n, k;
		cin>>n>>k>>word;

		cout << solve(n, k, word) <<endl;
	}
	return 0;
}
