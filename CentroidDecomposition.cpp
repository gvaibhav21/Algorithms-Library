// Code for problem 342 E on codeforces, example usage of Centroid Decomposition
#include<bits/stdc++.h>
using namespace std;
 
#define sd(a) scanf("%d",&a)
#define ss(a) scanf("%s",&a)
#define sl(a) scanf("%lld",&a)
#define clr(a) memset(a,0,sizeof(a))
#define debug(a) printf("check%d",a)
#define rep(i)
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ll long long
#define N 100010
#define LOGN 20
#define INF 1e9
vector<int> v[N];
int p[N][LOGN],l[N];

void dfs1(int cur,int par)
{
	int i;
	for(i=0;i<v[cur].size();++i)
	{
		if(v[cur][i]==par)	continue;
		l[v[cur][i]]=1+l[cur];
		p[v[cur][i]][0]=cur;
		dfs1(v[cur][i],cur);
	}
}
void pre(int n)
{
	int i,j;
	p[1][0]=l[1]=0;
	dfs1(1,0);
	for(j=1;j<LOGN;++j)
		p[0][j]=0;
	for(j=1;j<LOGN;++j)
		for(i=1;i<=n;++i)
			p[i][j]=p[p[i][j-1]][j-1];
}
int lca(int x,int y)
{
	int j;
	if(l[x]<l[y])
		swap(x,y);
	for(j=LOGN-1;j>=0;--j)
		if(l[p[x][j]]>=l[y])
			x=p[x][j];
	if(x==y)
		return x;
	for(j=LOGN-1;j>=0;--j)
		if(p[x][j]!=p[y][j])
		{
			x=p[x][j];
			y=p[y][j];
		}
	return p[x][0];
}
int dist(int x,int y)
{
	return l[x]+l[y]-2*l[lca(x,y)];
}
  //------CENTROID-DECOMPOSITION------
int sz[N],c_par[N];
int cnt;//no. of nodes in current part
bool mark[N]={0};//wether node has already been marked as centroid
void dfs2(int cur,int par)
{
	cnt++;
	sz[cur]=1;
	for(int i=0;i<v[cur].size();++i)
	{
		if(mark[v[cur][i]]||v[cur][i]==par)
			continue;
		dfs2(v[cur][i],cur);
		sz[cur]+=sz[v[cur][i]];
	}
}

int find_centroid(int cur,int par)  
{
	for(int i=0;i<v[cur].size();++i)
	{
		if(mark[v[cur][i]]||v[cur][i]==par)
			continue;
		if(sz[v[cur][i]]>cnt/2)
			return find_centroid(v[cur][i],cur);
	}
	return cur;
}
void decompose(int start,int par)
{
	cnt=0;
	dfs2(start,0);
	int cur=find_centroid(start,0);
	mark[cur]=1;
	c_par[cur]=0;
	if(par)
		c_par[cur]=par;
	for(int i=0;i<v[cur].size();++i)
		if(!mark[v[cur][i]])
			decompose(v[cur][i],cur);
}
//------END------
int minn[N];
void update(int cur,int x)
{
	minn[cur]=min(minn[cur],dist(cur,x));
	if(c_par[cur])
		update(c_par[cur],x);
}
int query(int x)
{
	int cur=x;
	int ret=INF;
	while(cur)
	{
		ret=min(ret,dist(x,cur)+minn[cur]);
		cur=c_par[cur];
	}
	return ret;
}
int main()
{
	int n,m,i;
	sd(n);sd(m);
	for(i=0;i<n-1;++i)
	{
		int x,y;
		sd(x);sd(y);
		v[x].PB(y);v[y].PB(x);
	}
	pre(n);
	decompose(1,0);
	for(i=1;i<=n;++i)
		minn[i]=INF;
	update(1,1);
	while(m--)
	{
		int ch,x;
		sd(ch);sd(x);
		if(ch==1)
			update(x,x);
		else
			printf("%d\n",query(x));
	}
}