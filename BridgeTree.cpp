// Code for problem 652 E on Codeforces, example usage of Bridge Tree
#include<bits/stdc++.h>
using namespace std;

#define sd(mark) scanf("%d",&mark)
#define ss(mark) scanf("%s",&mark)
#define sl(mark) scanf("%lld",&mark)
#define debug(mark) printf("check%d\n",mark)
#define clr(mark) memset(mark,0,sizeof(mark))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ll long long
#define INF 100000000
#define N 300010
vector<pair<int,int> > v[N];
pair<pair<int,int>,int> e[N];
int special[N];
int special_cnt[N]={0};
vector<pair<int,int> > tree[N];
int low[N];
int parent[N];
bool mark[N];
int disc[N];
int comp[N];
int t;
int bicompcnt;
int bicomp[N];
vector<int> out[N];
void dfs1(int cur)
{
	int i;
	mark[cur]=1;
	disc[cur]=t++;
	for(i=0;i<v[cur].size();++i)
	{
		if(!mark[v[cur][i].F])
		{
			parent[v[cur][i].F]=cur;
			dfs1(v[cur][i].F);
			low[cur]=min(low[cur],low[v[cur][i].F]);
			if(low[v[cur][i].F]>disc[cur])
			{
				e[v[cur][i].S].S=1;
			}
		}
		else if(v[cur][i].F!=parent[cur])
		{
			low[cur]=min(low[cur],disc[v[cur][i].F]);
		}
	}
}
void find_bridges(int n)
{
	int i;
	t=0;
	for(i=0;i<n;++i)
		low[i]=INF;
	for(i=0;i<n;++i)
		mark[i]=0;
	for(i=0;i<n;++i)
	{
		if(!mark[i])
		{
			parent[i]=-1;
			dfs1(i);
		}
	}
}
void dfs2(int cur)
{
	int i;
	mark[cur]=1;
	bicomp[cur]=bicompcnt;
	for(i=0;i<v[cur].size();++i)
	{
		if(e[v[cur][i].S].S)
			out[bicomp[cur]].PB(v[cur][i].S);
		else if(!mark[v[cur][i].F])
		{
			if(special[v[cur][i].S])
				special_cnt[bicompcnt]++;
			dfs2(v[cur][i].F);
		}
		else if(special[v[cur][i].S])
			special_cnt[bicompcnt]++;
	}
}
void build_bridge_tree(int n)
{
	int i,j;
	for(i=0;i<n;++i)
		mark[i]=0;
	bicompcnt=0;
	for(i=0;i<n;++i)
	{
		if(!mark[i])
		{
			dfs2(i);
			bicompcnt++;
		}
	}
	for(i=0;i<bicompcnt;++i)
	{
		for(j=0;j<out[i].size();++j)
		{
			if(bicomp[e[out[i][j]].F.F]!=i)
			{
				tree[i].PB(MP(bicomp[e[out[i][j]].F.F],out[i][j]));
			}
			else
				tree[i].PB(MP(bicomp[e[out[i][j]].F.S],out[i][j]));	
		}
	}
}
int temp=0;
void dfs(int cur,int par,int target,int cnt)
{
	cnt+=special_cnt[cur];
	if(cur==target)
	{
		temp=cnt;
		return;
	}
	for(int i=0;i<tree[cur].size();++i)
		if(tree[cur][i].F!=par)
		{
			if(special[tree[cur][i].S])
				cnt++;
			dfs(tree[cur][i].F,cur,target,cnt);
			if(special[tree[cur][i].S])
				cnt--;
		}
}
int main()
{
	int n,m,i,x,y,z;
	sd(n);sd(m);
	for(i=0;i<m;++i)
	{
		sd(x);sd(y);sd(z);--x;--y;
		v[x].PB(MP(y,i));
		v[y].PB(MP(x,i));
		e[i]=MP(MP(x,y),0);
		special[i]=z;
	}
	find_bridges(n);
	build_bridge_tree(n);
	int a,b;
	sd(a);sd(b);--a;--b;
	dfs(bicomp[a],-1,bicomp[b],0);
	if(temp>0)
		printf("YES\n");
	else
		printf("NO\n");
}