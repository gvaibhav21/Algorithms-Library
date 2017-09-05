// Code for problem 653 F on Codeforces, example usage for Suffix Array
#include<bits/stdc++.h>
using namespace std;

#define sd(a) scanf("%d",&a)
#define ss(a) scanf("%s",&a)
#define sl(a) scanf("%lld",&a)
#define debug(a) printf("check%d\n",a)
#define clr(a) memset(a,0,sizeof(a))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ll long long
#define N 500010
int sortindex[20][N];
pair<pair<int,int>,int> sa[N];
int lcp[N];
int n;
char s[N];
vector<int> pos_string[2*N];
vector<int> pos_sa[2*N];
int pre[N];
void buildSA()
{

	int i,j;
	for(i=0;i<n;++i)
		sortindex[0][i]=s[i]-'(';
	for(i=0;i<n;++i)
		sa[i].S=i;
	for(i=1;(1<<(i-1))<n;++i)
	{
		for(j=0;j<n;++j)
		{
			sa[j].F.F=sortindex[i-1][sa[j].S];
			if(sa[j].S+(1<<(i-1))<n)
				sa[j].F.S=sortindex[i-1][sa[j].S+(1<<(i-1))];
			else
				sa[j].F.S=-1;	
		}
		sort(sa,sa+n);
		int cnt=0;
		sortindex[i][sa[0].S]=0;
		for(j=1;j<n;++j)
		{
			if(sa[j].F==sa[j-1].F)
				sortindex[i][sa[j].S]=sortindex[i][sa[j-1].S];
			else
				sortindex[i][sa[j].S]=++cnt;
		}
	}
}
int findlcp(int x,int y)
{
	int i;
	int ret=0;
	for(i=0;(1<<(i-1))<n;++i);
	--i;
	for(;i>=0;--i)
	{
		if(sortindex[i][x]==sortindex[i][y])
		{
			ret+=(1<<i);
			x+=(1<<i);
			y+=(1<<i);
			if(x>=n||y>=n)
				break;
		}
	}
	return ret;
}
void buildlcp()
{
	int i;
	for(i=1;i<n;++i)
		lcp[i]=findlcp(sa[i-1].S,sa[i].S);
}
int bit[2][N];
inline void update(int i,int val,bool f)
{
	while(i<=n)
	{
		bit[f][i]+=val;
		i=i+(i&(-i));
	}
}
inline int query(int i,bool f)
{
	int ret=0;
	while(i)
	{
		ret+=bit[f][i];
		i=i-(i&(-i));
	}
	return ret;
}
inline int query(int i,int j,bool f)
{
	if(j<i)
		return 0;
	++i;++j;
	return query(j,f)-query(i-1,f);
}

int main()
{
	int i;
	sd(n);
	ss(s);
	buildSA();
	buildlcp();
	lcp[0]=0;
	pre[0]=0;
	for(i=1;i<=n;++i)
	{
		pre[i]=pre[i-1];
		if(s[i-1]=='(')
			pre[i]++;
		else
			pre[i]--;
		pos_string[pre[i]+n].PB(i-1);
	}
	for(i=0;i<n;++i)
		pos_sa[pre[sa[i].S]+n].PB(i);
	clr(bit[0]);
	clr(bit[1]);
	ll ans=0;
	for(i=0;i<2*n;++i)
	{
		for(auto j:pos_string[i])
			update(j+1,1,0);
		for(auto j:pos_sa[i])
		{
			int lo=sa[j].S,hi=n-1,mid;
			while(lo<hi)
			{
				mid=(lo+hi)/2;
				if(query(sa[j].S,mid,1))
					hi=mid;
				else
					lo=mid+1;
			}
			if(query(sa[j].S,lo,1))
				--lo;
			hi=min(lo,n-1);
			lo=sa[j].S+lcp[j];
			ans=ans+query(lo,hi,0);
		}
		for(auto j:pos_string[i])
		{
			update(j+1,-1,0);
			update(j+1,1,1);
		}
	}
	printf("%lld\n",ans);
}