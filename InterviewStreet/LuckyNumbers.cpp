#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <set>
#include <sstream>

using namespace std;

typedef long long ll;

const int maxn = 5000;
bool p[maxn]; // p[i] = is i prime?

const int maxDig  = 19;
const int maxSum  = 180;
const int maxSum2 = 1460;

int sumLen[20], sum2Len[20];

//normal DP
ll dp[maxDig][maxSum][maxSum2];

//cumulative DPs
ll cdp1[maxDig][maxSum][maxSum2];
ll cdp2[maxDig][maxSum][maxSum2];

ll lucky[maxDig];
vector<int> prime;
vector<int> sq[maxDig][maxSum];
vector<int> sq2[maxDig][maxSum];

// how many lucky numbers in 0..x ? [inclusive]
ll count(ll x)
{
	stringstream ss;
	ss<<x;
	string str;
	ss>>str;
	int D = str.size();
	ll res = 0;//lucky[D-1];

	int sofar = 0, sofar2 = 0;
	for(int i=0; i<D; i++)
	{
		int curDig = (str[i] - '0');
		for(int j=0; j<=curDig; j++)
		{
			if(j==curDig && i!=D-1)
				continue;

			res += cdp2[D - 1 -i] [sofar + j] [sofar2 + j*j];
		}
		sofar += curDig;
		sofar2 += curDig * curDig;
	}

	return res;
}

int main()
{
	//Sieve of Eratosthenes
	prime.clear();
	for(int i=0; i<maxn; i++) 
		p[i] = true;
	p[0] = p[1] = false;
	p[2] = true;
	for(int i=2; i<maxn; ++i)
	{
		if(p[i])
		{
			prime.push_back(i);
			for(int j=2*i; j<maxn; j+=i)
				p[j] = false;
		}
	}

	//initialize DP	
	memset(dp, 0, sizeof dp);
	memset(cdp1, 0, sizeof cdp1);
	memset(cdp2, 0, sizeof cdp2);
	lucky[0] = lucky[1] = 0;
	for(int i=0; i<maxSum; i++)
	{
		for(int j=0; j<maxSum2; j++)
		{
			dp[1][i][j] = ( i<10 && j==i*i );
			dp[0][i][j] = 0;
			if ( dp[1][i][j] != 0 ) sq[1][i].push_back(j);
		}
	}
	dp[0][0][0] = 1;
	sq[0][0].push_back(0);

	//calculate DP
	for(int dig=2; dig<maxDig; dig++)
	{
		lucky[dig] = 0;
		for(int sum=0; sum<maxSum; sum++)
		{
			sq[dig][sum].clear();
			for(int sum2=0; sum2<maxSum2; sum2++)
			{
				for(int i=0; i<=9; i++)
					if(sum>=i && sum2>=i*i)
						dp[dig][sum][sum2] += dp[dig-1][sum-i][sum2-i*i];

				if( dp[dig][sum][sum2] != 0 )
					sq[dig][sum].push_back(sum2);

				if(p[sum] && p[sum2])
					lucky[dig] += dp[dig][sum][sum2];
			}
		}
	}
			
	//new calculate cumulative DP 1
	for(int dig=0; dig<maxDig; dig++)
		for(int i=0; i<maxSum; i++)
			for(int j=0; j<sq[dig][i].size(); j++)
			{
				int &coSum = sq[dig][i][j];
				for(int z=0; prime[z] < maxSum2; z++)
					if( prime[z] >= coSum )
						cdp1[dig][i][ prime[z] - coSum ] += dp[dig][i][ coSum ];
			}

	for(int dig=0; dig<maxDig; dig++)
		for(int i=0; i<maxSum; i++)
			for(int j=0; j<maxSum2; j++)
				if(cdp1[dig][i][j]!=0)
					sq2[dig][i].push_back(j);

	//LAST DP 2
	for(int dig=0; dig<maxDig; dig++)
		for(int K=0; K<maxSum; K++)
			for(int j=0; prime[j]<maxSum; j++)
				if( prime[j] >= K )
				{
					for(int z=0; z<sq2[dig][prime[j] - K].size(); z++)
					{
						int &coSum = sq2[dig][prime[j] - K][z];
						cdp2[dig][K][coSum] += cdp1[dig][prime[j] - K][coSum];
					}
				}

	int tc;
	cin>>tc;
	while(tc--)
	{
		ll A, B;
		cin>>A>>B;
		cout<< count(B) - count(A-1) <<endl;
	}

	return 0;
}
