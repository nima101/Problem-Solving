#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <cstdio>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

const int maxn = 100001;
int p[maxn];
int c[4];
int up[maxn];//
int rt[maxn];//

struct Quad
{
	int c[4];
	Quad(int c1=0, int c2=0, int c3=0, int c4=0) { c[0] = c1; c[1] = c2; c[2] = c3; c[3] = c4; }
	Quad(const Quad& q) { for(int i=0; i<4; i++) c[i] = q.c[i]; }
	void print(){cout<<c[0]<<" "<<c[1]<<" "<<c[2]<<" "<<c[3]<<endl;}
	Quad operator + (const Quad& q) { return Quad(c[0]+q.c[0], c[1]+q.c[1], c[2]+q.c[2], c[3]+q.c[3]); }
	Quad operator - (const Quad& q) { return Quad(c[0]-q.c[0], c[1]-q.c[1], c[2]-q.c[2], c[3]-q.c[3]); }
}
q[maxn];


void insert(set<int> &s, int value)
{
	set<int>::iterator it = s.find(value);
	if(it != s.end())
		s.erase(it);
	else
		s.insert(value);
}

Quad reflectX(Quad q){return Quad(q.c[3], q.c[2], q.c[1], q.c[0]);}
Quad reflectY(Quad q){return Quad(q.c[1], q.c[0], q.c[3], q.c[2]);}

Quad range(int i, int j)
{
	if(i>j) return Quad(0,0,0,0);
	if(i<=0)  return q[j];
	return q[j] - q[i-1];
}


int main()
{
	set<int> X, Y;
	int N, Q; cin>>N;
	for(int i=0; i<N; i++)
	{
		int x,y;
		cin>>x>>y;
		memset(c, 0, sizeof c);
		Quad cur (x>0 && y>0, x<0 && y>0, x<0 && y<0, x>0 && y<0);
		if(i==0)
			q[i] = cur;
		else
			q[i] = q[i-1]+cur;
	}
	cin>>Q;
	for(int k=0; k<Q; k++)
	{
		char ch; int i,j;
		cin>>ch>>i>>j;
		i--; j--;

		if (ch=='C')
		{
			set<int>::iterator it;
			bool yes;
			Quad cur(0,0,0,0), tot(0,0,0,0);
			int last = i-1;
			for( it = X.begin(), yes=(X.size()%2); it != X.end(); ++it, yes=!yes )
			{
				if((*it)<i) continue;
				if(*it<=j)
				{
					Quad cur = range(last+1, *it);
					last = *it;
					if(yes)	tot = tot + reflectX(cur);
					else	tot = tot + cur;
				}
				else
					tot = reflectX(tot);
			}
			if(last<j) tot = tot + range(last+1, j);

			Quad cur2(0,0,0,0), tot2(0,0,0,0);
			last = i-1;
			for( it = Y.begin(), yes=(Y.size()%2); it != Y.end(); ++it, yes=!yes )
			{
				if((*it)<i) continue;
				if(*it<=j)
				{
					Quad cur2 = range(last+1, *it);
					last = *it;
					if(yes)	tot2 = tot2 + reflectY(cur2);
					else	tot2 = tot2 + cur2;
				}
				else
					tot2 = reflectY(tot2);
			}
			if(last<j) tot2 = tot2 + range(last+1, j);
			tot = tot + (tot2 - range(i,j));
			tot.print();

		}

		if(ch== 'X') {insert(X, j); if(i>0) insert(X, i-1);	}
		if(ch== 'Y') {insert(Y, j); if(i>0) insert(Y, i-1);}
	}
	return 0;
}
