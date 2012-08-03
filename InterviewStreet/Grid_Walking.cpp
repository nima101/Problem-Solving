#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

typedef long long ll;

int N, M, tc, x[15], D[15];
const ll mod = 1000000007;
const int maxn = 305;
ll choose[maxn][maxn];

ll add(ll aa, ll bb) {return (aa+bb)%mod;}
ll mul(ll aa, ll bb) {return (aa*bb)%mod;}

ll dimCount[15][105][305]; //dim, pos, steps left
ll dp[15][305];

ll solve(int dim, int m)
{
	ll &res = dp[dim][m];
	if(res!=-1) return res;

	if(dim == N-1)
		return (res = dimCount[dim][x[dim]][m]);
	if( m == 0 )
		return (res = 1);

	res=0;
	for(int i=0; i<=m; i++)
		res = add(res, mul( mul( dimCount[dim][x[dim]][i] , solve(dim+1, m-i)) , choose[m][i] ) );

	return res;
}

int main()
{
	for(int i=1; i<maxn; i++)
		choose[i][i] = choose[i][0] = 1;
	for(int i=1; i<maxn; i++)
		for(int j=1; j<i; j++)
			choose[i][j] = add(choose[i-1][j-1], choose[i-1][j]);

	int tc; cin>>tc;
	while(tc--)
	{
		cin >> N >> M;
		for(int i=0; i<N; i++) {cin>>x[i]; x[i]--;}
		for(int i=0; i<N; i++) cin>>D[i];

		memset(dimCount, 0, sizeof dimCount);
		memset(dp, -1, sizeof dp);

		for(int dim=0; dim<N; dim++)
			for(int pos=0; pos<D[dim]; pos++)
				dimCount[dim][pos][0]=1;

		for(int dim=0; dim<N; dim++)
			for(int steps=1; steps<=M; steps++)
				for(int pos=0; pos<D[dim]; pos++)
				{
					ll &res = dimCount [dim][pos][steps];
					res = 0;
					if(pos-1 >= 0)     
						res = add(res, dimCount[dim][pos-1][steps-1]);
					if(pos+1 < D[dim]) 
						res = add(res, dimCount[dim][pos+1][steps-1]);
				}

		cout<< solve(0, M) <<endl;
	}
	return 0;
}
