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
#include <cmath>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
const int maxn = 205;

string board [maxn];
ll count [2][maxn*3][maxn*3];
ll sum [maxn*3][maxn*3];

int main()
{
	int startR, startC;
	int tc, S, N, M;
	cin>>tc;
	while(tc--)
	{
		cin>>N>>M;
		cin>>S;

		memset(count, 0, sizeof count);
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) count[0][i+maxn][j+maxn] = 1;

		for(int i=0; i<N; i++)
		{	
			cin>>board[i];
			for(int j=0; j<N; j++)
			{
				if(board[i][j] == 'L')
					startR = maxn+i, startC = maxn+j;
				if(board[i][j] == 'P')
					count[0][i+maxn][j+maxn] = 0;
			}
		}

		//int t1=0, t2=0, t3=0;
		//double tt1=0, tt2=0, tt3=0;

		for(int step = 1; step <= M; step++)
		{
			int curStep = step&1;
			int prevStep = (step+1)&1;
			//calculate cumulative DP of the last step
			//t1 = clock();
			memset(sum, 0, sizeof sum);
			//tt1 += clock() - t1;

			//t2 = clock();
			//			for(int i=maxn; i<maxn+2*N+3; i++) for(int j=max(maxn-(i-maxn)-3, maxn-); j<maxn+2*N+3; j++)
			for(int i=maxn; i<maxn+N+S+3; i++)
			{
				int highj = min(maxn+N+S+3, N+i+3);
				for(int j=max(maxn-S-3, 2*maxn-i-3) ; j<highj; j++)
				{
					sum[i][j] = sum[i-1][j-1] + sum[i-1][j+1] + count[prevStep][i][j] - sum[i-2][j];
					sum[i][j] %= mod;
				}
			}
			//tt2 += clock() - t2;

			//t3 = clock();
			//calculate next step
			for(int r=maxn; r<maxn+N; r++) for(int c=maxn; c<maxn+N; c++)
			{
				ll &res = count[curStep][r][c];
				res = 0;
				if(board[r-maxn][c-maxn]=='P')
					continue;

				//blacks
				res += sum [r+S][c] - sum [r-1][c-S-1] - sum [r-1][c+S+1] + sum [r-S-2][c];
				//res %= mod;

				//whites
				res += sum [r+S-1][c] - sum [r-1][c-S] - sum [r-1][c+S] + sum [r-S-1][c];
				res %= mod;
			}
			//tt3 += clock() - t3;
		}
		while(count[M%2][startR][startC]<0) count[M%2][startR][startC]+=mod;
		cout<< count[M%2][startR][startC] <<endl;

		//tt1 /= CLOCKS_PER_SEC;
		//tt2 /= CLOCKS_PER_SEC;
		//tt3 /= CLOCKS_PER_SEC;

		//cerr<< tt1<<" "<< tt2<<" "<< tt3<<" "<<endl;
	}
	return 0;
}
