#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;

inline int next(int i, int n){ if(i==n-1) return 0; else return i+1; }
inline int prev(int i, int n){ if(i==0) return n-1; else return i-1; }

struct Matrix
{
	inline int prev(int i){ if(i==0) return n-1; else return i-1; }
	inline int next(int i){ if(i==n-1) return 0; else return i+1; }

	ll *m;
	int n;
	inline ll& get(int i, int j){return (m[i*n+j]);}
	void allocate() { m = new ll[n*n]; }
	void clear() { memset(m, 0, n*n*8); }
	Matrix(int nn) { n=nn; allocate(); clear(); }
	Matrix(const Matrix &mat) { n = mat.n; allocate(); memcpy(m, mat.m, n*n*8); }

	Matrix(int nn, int index, int num) 
	{  
		n = nn;
		allocate(); clear();
		for(int i=0; i<n; i++) m[i*n+i] = 1;
		get(index, prev(index)) = num; 
		get(index, next(index)) = num;
	}

	Matrix operator = (const Matrix &mat)
	{
		n = mat.n;
		memcpy(m, mat.m, n*n*8);
		return *this;
	}

	inline ll MOD(ll num){ num = num % mod; return num; }

	Matrix operator * (Matrix &mat)
	{
		Matrix res(n);
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
			{
				ll & result = res.get(i, j);
				ll * p = &(get(i, 0));
				ll * q = &(mat.get(0, j));
				result = 0;
				for(int k=0; k<n; k++, q+=n)
					result = MOD(result + ( (*p++) * ( *q ) ) );
			}
		return res;
	}

	ll* operator * (ll *v)
	{
		ll *res = new ll[n];
		for(int i=0; i<n; i++)
		{
			res[i] = 0;
			for(int k=0; k<n; k++)
				res[i] = (res[i] + (get(i, k) * v[k])%mod)%mod;
		}
		return res;
	}

	void sanitize()
	{
		ll NN = n*n;
		for(int i=0; i<NN; i++)
			if( *(m+i)<0 )
				*(m+i) += mod;
	}

	static Matrix Identity(int nn)
	{
		Matrix I(nn);
		for(int i=0; i<nn; i++)
			I.get(i, i) = 1;
		return I;
	}

	Matrix pow (int p)
	{
		if(p==0)
			return Matrix::Identity(n);
		if(p==1)
			return *this;
		Matrix res(n);
		res = this->pow(p/2);
		res = res * res;
		if(p%2==1) res = res * (*this);
		return res;
	}

	~Matrix() { delete[] m; }
};



int main()
{
	int N, M;
	int tc; scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d %d", &N, &M);

		ll *a = new ll[N];
		for(int i=0; i<N; i++) 
		{
			int temp;
			scanf( "%d", &temp);
			a[i] = temp;
		}

		Matrix mat(N, 0, +1);
		for(int j=1; j!=0; j=next(j, N))
			mat = Matrix(N, j, +1) * mat;

		mat = mat.pow(M/N);
		
		mat.sanitize();

		for(int i=0; i<N; i++)
		{
			ll *vec = new ll[N];
			memcpy(vec, a, N*8);
			
			for(int k=i-1; k>=0; k--)
			{
				vec[k] = ( vec[k] - vec[next(k, N)] - vec[prev(k, N)] ) % mod;
				vec[k] = ( vec[k] + mod ) % mod;
			}	

			ll * res = mat * vec;

			for(int k=0; k<i; k++)
				res[k] = ( res[k] + res[next(k, N)] + res[prev(k, N)] ) % mod;


			for(int j=0; j < M % N; j++)
			{
				int idx = (i+j)%N;
				res[idx] = (res[idx] + res[next(idx, N)] + res[prev(idx, N)]) % mod;
			}

			for(int j=0; j<N; j++)
			{
				if(j!=0) printf(" ");
				printf("%d", (int)(res[j]));
			}
			printf("\n");
		}

		if(tc>0)
			printf("\n");
	}
	
	return 0;
}
