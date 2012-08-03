#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <stdio.h>
#include <string.h>

using namespace std;

int d[101][101][3];
const int inf = 1000;

int dynamicSolve(const string &s)
{
	//initializing dynamic table
	int len = s.size();
	for(int i=0; i<len; i++)
		for(char c='a'; c<='c'; c++)
			if(c==s[i])
				d[i][i][c-'a'] = 1;
			else
				d[i][i][c-'a'] = inf;

	//dynamic recursion
	for(int L=2; L<=len; L++)
		for(int i=0; i+L-1<len; i++)
			for(char c='a'; c<='c'; c++)
			{
				int j = i+L-1;
				int &res = d[i][j][c-'a'];
				res = inf;
				for(int k=i; k<j; k++)
					for(int c1='a'; c1<='c'; c1++)
						for(int c2='a'; c2<='c'; c2++)
						{
							if(c1==c && c2==c)
								res = min(res, d[i][k][c1-'a']+d[k+1][j][c2-'a']);
							if(c1!=c && c2!=c && c1!=c2)
								res = min(res, d[i][k][c1-'a']+d[k+1][j][c2-'a'] - 1 );
						}
			}

			int finalResult = inf;
			//finding the answer
			for(char c='a'; c<='c'; c++)
				finalResult = min(finalResult, d[0][len-1][c-'a']);

			return finalResult;
}

int main()
{
	int tc;
	cin>>tc;

	while(tc--)
	{
		string input;
		cin >> input;
		cout << dynamicSolve( input ) << endl;
	}
	return 0;
}
