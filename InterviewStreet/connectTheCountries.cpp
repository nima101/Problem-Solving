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

const int maxn = 35;
ll dp[maxn], f[maxn];
ll comb[maxn][maxn];

int main()
{
	int n;
	cin>>n;

	for(int i=0; i<maxn; i++)
		comb[i][i] = comb[i][0] = 1;
	for(int i=1; i<maxn; i++)
		for(int j=1; j<i; j++)
			comb[i][j] = comb[i-1][j-1] + comb[i-1][j];

	f[1] = f[2] = 1;
	dp[0] = dp[1] = 1; //dp[2] = 4;

	for(int N=2; N<=30; N++)
	{
		dp[N] = 0;
		for(int Np = 1; Np<=N; Np++)
			dp[N] += ((1<<(Np))-1) * f[Np] * dp[N-Np] * comb[N-1][Np-1];
		f[N+1] = dp[N];
	}

	for(int i=0; i<=30; i++)
		cout<<i<<" "<<f[i]<<endl;

	//cout<<dp[n]<<endl;
	return 0;
}




/*
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

int main()
{
	int n;
	cin>>n;

	double ans = 1.25 * n * log10((double)(n)) + 0.5;
	cout<< (int) ans <<endl;
	return 0;
}
*/