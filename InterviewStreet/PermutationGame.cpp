#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <stdio.h>
#include <string.h>

using namespace std;

int a[20];

//dynamic table:
//if a player starts and the given mask is left does he win?
bool d[1<<15];

bool increasing(int mask, int n)
{
	int last = -1;
	for(int i=0; i<n; i++)
		if((mask & (1<<i)) != 0)
		{
			if(a[i]<last)
				return false;
			last = a[i];
		}
		return true;
}

int main()
{
	int tc;
	cin>>tc;

	while(tc--)
	{
		int n;
		cin>>n;
		for(int i=0; i<n; i++)
			cin>>a[i];

		for(int mask = 1; mask<(1<<n); mask++)
		{
			//base case of the dynamic
			if(increasing(mask, n))
				d[mask] = false;
			else
			{
				//dynamic recursion
				d[mask] = false;
				for(int i=0; i<n; i++)
					if((mask & (1<<i))!=0 && d[mask ^ (1<<i)]==false/*the opponent will lose*/ )
					{
						d[mask] = true;
						break;
					}
			}
		}

		if(d[(1<<n) - 1])
			cout<<"Alice"<<endl;
		else
			cout<<"Bob"<<endl;

	}
	return 0;
}
