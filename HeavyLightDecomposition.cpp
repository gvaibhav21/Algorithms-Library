// Code for problem QTREE3 on spoj, example usage of Heavy-Light Decomposition
#include<bits/stdc++.h>
using namespace std;

#define sd(a) scanf("%d",&a)
#define ss(a) scanf("%s",&a)
#define sl(a) scanf("%lld",&a)
#define clr(a) memset(a,0,sizeof(a))
#define debug(a) printf("check%d\n",a)
#define rep(i)
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ll long long
#define N 100010

vector<int> v[N];
bool color[N]={0};
//----HEAVY-LIGHT----
vector<int> t[N];//segment-tree fr each chain 
vector<int> chain[N];//actual nodes contained in chain
int ch_pos[N];//position of node in its chain
int ch_id[N];//chain-id of node
int head[N];//head of chain
int par[N];
int sz[N];
int sp_child[N];//special child
int cur_id=0;//current chain id
void dfs(int cur,int p)
{
	sz[cur]=1;
	par[cur]=p;
	for(int i=0;i<v[cur].size();++i)
		if(v[cur][i]!=p)
		{
			dfs(v[cur][i],cur);
			sz[cur]+=sz[v[cur][i]];
		}
}
void dfs1(int cur,int pos)
{
	ch_id[cur]=cur_id;
	ch_pos[cur]=pos;
	chain[cur_id].PB(cur);
	if(!pos)
		head[cur_id]=cur;
	int maxx=0,max_ch;
	for(int i=0;i<v[cur].size();++i)
		if(v[cur][i]!=par[cur])
			if(sz[v[cur][i]]>maxx)
			{			
				maxx=sz[v[cur][i]];
				sp_child[cur]=v[cur][i];
			}
	if(!maxx)
	{
		t[ch_id[cur]].resize(4*(int)chain[ch_id[cur]].size(),0);
		return;
	}
	dfs1(sp_child[cur],pos+1);
	for(int i=0;i<v[cur].size();++i)
		if(v[cur][i]!=par[cur])
			if(v[cur][i]!=sp_child[cur])
			{	
				++cur_id;
				dfs1(v[cur][i],0);
			}
}
void heavy_light(int n)
{
	for(int i=0;i<=n;++i)
	{
		t[i].clear();
		chain[i].clear();
	}
	cur_id=0;
	dfs(1,0);
	dfs1(1,0);
}
//----END----

void update(int i,int j,int si,int sj,int pos,int val)
{
	if(si==sj)
	{
		t[i][j]=val;
		return;
	}
	if(pos<=(si+sj)/2)
		update(i,j*2,si,(si+sj)/2,pos,val);
	else
		update(i,j*2+1,(si+sj)/2+1,sj,pos,val);
	t[i][j]=t[i][j*2]+t[i][j*2+1];
}
int query(int i,int j,int si,int sj,int st,int en)
{
	if(si>en||sj<st||(!t[i][j]))
		return -1;
	if(si==sj)
		return chain[i][si];
	if(t[i][j*2])
		return query(i,j*2,si,(si+sj)/2,st,en);
	if(t[i][j*2+1])
		return query(i,j*2+1,(si+sj)/2+1,sj,st,en);
	return -1;
}

int query(int x)
{
	int v1=query(ch_id[x],1,0,(int)chain[ch_id[x]].size()-1,0,ch_pos[x]);
	int v2=-1,p=par[head[ch_id[x]]];
	if(p)
		v2=query(p);
	if(v2!=-1)
		return v2;
	return v1;
}

int main()
{
	int n,q,i;
	cin>>n>>q;
	for(i=0;i<n-1;++i)
	{
		int x,y;
		cin>>x>>y;
		v[x].PB(y);
		v[y].PB(x);
	}
	heavy_light(n);//yay!
	while(q--)
	{
		int ch,x;
		cin>>ch>>x;
		if(!ch)
		{
			color[x]=(!color[x]);
			update(ch_id[x],1,0,(int)chain[ch_id[x]].size()-1,ch_pos[x],color[x]);
		}
		else
			cout<<query(x)<<'\n';
	}
}