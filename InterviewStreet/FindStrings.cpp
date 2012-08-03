#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

#define N 2000000
 
char str[N];
int H = 0, Bucket[N], nBucket[N], c;
int lcp[N], len[N];

struct Suffix{
	int idx; // Suffix starts at idx, i.e. it's str[ idx .. L-1 ]
	bool operator<(const Suffix& sfx) const
	// Compares two suffixes based on their first 2H symbols,
	// assuming we know the result for H symbols.
	{
		if(H == 0) return str[idx] < str[sfx.idx];
		else if(Bucket[idx] == Bucket[sfx.idx])
			return (Bucket[idx+H] < Bucket[sfx.idx+H]);
		else
			return (Bucket[idx] < Bucket[sfx.idx]);
	}
	bool operator==(const Suffix& sfx) const
	{
		return !(*this < sfx) && !(sfx < *this);
	}
} Pos[N];
 
int UpdateBuckets(int L)
{
	int start = 0, id = 0, c = 0;
	for(int i = 0; i < L; i++)
	{
		/*
			If Pos[i] is not equal to Pos[i-1], a new bucket has started.
		*/
		if(i != 0 && !(Pos[i] == Pos[i-1]))
		{
			start = i;
			id++;
		}
		if(i != start) // if there is bucket with size larger than 1, we should continue ...
			c = 1;
		nBucket[Pos[i].idx] = id; // Bucket for suffix starting at Pos[i].idx is id ...
	}
	memcpy(Bucket, nBucket, 4 * L);
	return c;
}
 
void SuffixSort(int L)
{
	for(int i = 0; i < L; i++) Pos[i].idx = i;
	// H == 0, Sort based on first Character.
	sort(Pos, Pos + L);
	// Create initial buckets
	c = UpdateBuckets(L);
	for(H=1;c;H *= 2) {
		// Sort based on first 2*H symbols, assuming that we have sorted based on first H character
		sort(Pos, Pos+L);
		// Update Buckets based on first 2*H symbols
		c = UpdateBuckets(L);
	}
}

//simple LCP calculation
//can be done faster in O(logn) (suffix array) and O(1) (suffix tree)
void calcLCPs(int L)
{
	lcp[0] = 0;
	for(int i=1; i<L; i++)
	{
		int s1 = Pos[i-1].idx;
		int s2 = Pos[i].idx;
		int j=0; lcp[i] = 0;
		while(s1+j<L && s2+j<L && str[s1+j]!='#' && str[s2+j]!='#' && str[s1+j]==str[s2+j] )
			lcp[i]++, j++;
	}
}


void calcSufLens(int L)
{
	len[L-1] == 0;
	for(int i=L-2; i>=0; i--)
		if(str[i]=='#')
			len[i] = 0;
		else
			len[i] = len[i+1]+1;
}

string kth_substr(int L, int k)
{
	int i=0;
	while(i<L && len[Pos[i].idx]-lcp[i]<k)
	{
		k-=len[Pos[i].idx]-lcp[i];
		i++;
	}
	if(i==L)
		return "#";
	else
	{
		string res = "";
		for(int t=Pos[i].idx; t < Pos[i].idx + lcp[i] + k; t++)
			res += char(str[t]);
		return res;
	}
}

int main()
{
	int n;
	cin>>n;
	string all="";
	string tmp;
	for(int i=0; i<n; i++)
	{
		cin>>tmp;
		all+= tmp + "#";
	}
	strcpy (str, all.c_str());
	int L = strlen(str) + 1;
	SuffixSort(L);
	calcSufLens(L);
	calcLCPs(L);

	int q;
	cin>>q;
	for(int i=0; i<q; i++)
	{
		int k;
		cin>>k;
		string res = kth_substr(L, k);
		if(res=="#")
			cout<<"INVALID"<<endl;
		else
			cout<<res<<endl;
	}

	return 0;
}
