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

typedef long double ld;
const int maxn = 55;

int h[maxn], below[maxn];
ld fac[maxn], comb[maxn][maxn];


int main()
{
	int tc;
	cin>>tc;

	fac[0] = 1.0;
	for(int i=1; i<maxn; i++)
		fac[i] = (ld)(i) * fac[i-1]; 

	for(int i=0; i<maxn; i++)
		comb[i][i] = comb[i][0] = 1.0;
	for(int i=1; i<maxn; i++)
		for(int j=1; j<i; j++)
			comb[i][j] = comb[i-1][j-1] + comb[i-1][j];

	while(tc--)
	{
		int N;
		cin>>N;
		for(int i=0; i<N; i++)
			cin>>h[i];
		for(int i=0; i<N; i++)
		{
			below[i] = 0;
			for(int j=0; j<N; j++)
				if(i!=j && h[i] > h[j])
					below[i]++;
		}

		ld sum = 0;
		for(int x = 0; x < N; x++)
			for(int len=1; len<=N; len++)
			{
				if(below[x] < len-1)
					continue;
				
				//using a left tower
				if(len < N)
				sum += ( comb[ below[x] ][ len-1 ]/*choose below*/ * fac[len-1]/*below permutations*/ * (N-1-below[x])/*choose one high/equal as left tower*/ *
					     fac[N-2-(len-1)]/*outside permutation*/ * (N-2-(len-1)+1)/*rotations*/) * len;
				
				//using the y-axis as the left tower
				sum += ( comb[ below[x] ][ len-1 ]/*choose below*/ * fac[len-1]/*below permutations*/ * fac[N-1-(len-1)]/*outside permutations*/ ) * len;
			}

		ld res = sum / fac[N];
		printf("%.2f\n", (double)res);
	}

	return 0;
}
