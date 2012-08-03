#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <set>
#include <fstream>
#include <sstream>

using namespace std;

int k, n;

int sweepMatch(int diff, const string &P, const string &Q)
{
	int best = 0;
	int i = 0, i_end = 0; // [inclusive, exclusive)
	int misMatch = 0;
	
	//detect diff region
	while( i_end+diff < n && (misMatch<k || P[i_end]==Q[i_end+diff]) )
	{
		misMatch += (P[i_end]!=Q[i_end+diff]);
		++i_end;
	}
	best = max(best, i_end - i);

	//sweep it...
	while( i_end + diff < n )
	{
		//move head
		while( i + diff + 1 < n && P[i] == Q[i+diff] ) 
			++ i;
		if( i + diff + 1 < n )
			++ i;

		//move tail
		++ i_end;
		while( i_end < n && P[ i_end ] == Q[ i_end + diff ] )
			++ i_end;
	
		//update
		best = max(best, i_end - i);
	}
	return best;
}

int main()
{
	string P, Q;
	int tc;
	cin>>tc;

	while(tc--)
	{
		cin >> k >> P >> Q;
		n = P.size();
	
		int maxLen = 0;

		for(int diff = 0; diff<n; diff++ )
			maxLen = max(maxLen, sweepMatch(diff, P, Q));

		for(int diff = 0; diff<n; diff++ )
			maxLen = max(maxLen, sweepMatch(diff, Q, P));

		cout << maxLen << endl;
	}

	return 0;
}
