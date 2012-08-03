#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

typedef long long ll;

int z[100005];
int n;

void calc_Z(char* s)
{
	int L = 0, R = 0;
	for (int i = 1; i < n;i ++) 
	{
		if (i > R) 
		{
			L = R = i;
			while (R < n && s[R-L] == s[R]) R++;
			z[i] = R-L; R--;
		} 
		else 
		{
			int k = i-L;
			if (z[k] < R-i+1) z[i] = z[k];
			else 
				if(z[k] > R-i+1) z[i] = R-i+1;
				else
				{
					L = i;
					while (R < n && s[R-L] == s[R]) R++;
					z[i] = R-L; R--;
				}
		}
	}
}

char str[100005];

int main()
{
	int tc; scanf("%d", &tc);
	gets(str);
	while(tc--)
	{
		gets(str);
		n = strlen(str);
		calc_Z(str);
		ll res=0; int len = strlen(str);
		for(int i=1; i<len; i++) res += (long long)(z[i]);
		cout << res + n << endl;		
	}
	return 0;
}
