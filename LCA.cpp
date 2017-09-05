// Example usage of LCA
#include<bits/stdc++.h>
using namespace std;

#define sd(a) scanf("%d",&a)
#define ss(a) scanf("%s",a)
#define sl(a) scanf("%lld",&a)
#define clr(a) memset(a,0,sizeof(a))
#define debug(a) printf("check%d\n",a)
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ll long long
#define N 1000010
#define logn 23

vector<int> v[N];
int p[N][logn], minn[N][logn], l[N];

inline void dfs(int cur,int par)
{
	l[cur]=l[par]+1;
	p[cur][0]=par;
	for(auto u:v[cur])
		if(u!=par)
			dfs(u,cur);
}
inline int lca(int x,int y)
{
	if(l[x]<l[y])
		swap(x,y);
	for(int i=logn-1;i>=0;--i)
		if(l[x]-(1<<i)>=l[y])
			x=p[x][i];
	if(x==y)
		return x;
	for(int i=logn-1;i>=0;--i)
		if(p[x][i]!=p[y][i])
		{
			x=p[x][i];
			y=p[y][i];
		}
	return p[x][0];
}
inline void pre_lca(int n)
{
	for(int i=1;i<logn;++i)
		for(int j=1;j<=n;++j)
			p[j][i]=p[p[j][i-1]][i-1];
}
int main()
{
	int n,m,i;

	// input tree
	sd(n);
	for(i=0;i<n-1;i++)
	{
		int x,y;
		sd(x);sd(y);
		v[x].PB(y);
		v[y].PB(x);
	}
	// precomputation
	l[1]=-1;
	dfs(1,1);
	pre_lca(n);

	int q;
	sd(q);
	while(q--)
	{
		int x,y;
		sd(x);sd(y);
		printf("%d\n",lca(x,y));
	}
}