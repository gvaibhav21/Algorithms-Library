// Code for problem 369 E on Codeforces, example usage of Persistent Segment Tree
#include <bits/stdc++.h>
using namespace std;
 
#define sd(a) scanf("%d",&a)
#define ss(a) scanf("%s",&a)
#define sl(a) scanf("%lld",&a)
#define clr(a) memset(a,0,sizeof(a))
#define debug(a) printf("check%d\n",a)
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ll long long
#define N 300010
#define LIM 1000010

struct node
{
    int lc,rc,s;
}t[N*100];

int root[LIM+10], node_cnt;
int build_tree(int si,int sj)
{
    int id=node_cnt++;
    if(si==sj)
    {
        t[id].s=0;
        return id;
    }
    t[id].lc=build_tree(si,(si+sj)/2);
    t[id].rc=build_tree((si+sj)/2+1,sj);
    t[id].s=t[t[id].lc].s+t[t[id].rc].s;
    return id;
}


int update(int id,int si,int sj,int pos)
{
    int new_id=node_cnt++;
    t[new_id].s=t[id].s+1;
    t[new_id].lc=t[id].lc;
    t[new_id].rc=t[id].rc;
    if(si==sj)
        return new_id;
    if(pos<=(si+sj)/2)
        t[new_id].lc=update(t[id].lc,si,(si+sj)/2,pos);
    else
        t[new_id].rc=update(t[id].rc,(si+sj)/2+1,sj,pos);
    return new_id;
}

int query(int id,int si,int sj,int st,int en)
{
    if(si>en||sj<st)
        return 0;
    if(si>=st&&sj<=en)
        return t[id].s;
    return query(t[id].lc,si,(si+sj)/2,st,en)+query(t[id].rc,(si+sj)/2+1,sj,st,en);
}

int l[N],r[N];
int mark[LIM];
vector<int> pts;
vector<int> v[N];
vector<int> Query[N];
int cnt[N],comp[LIM];

int main()
{
	int n,m,i,j;
	clr(mark);
	sd(n);sd(m);
	for(i=0;i<n;i++)
	{
		sd(l[i]);
		sd(r[i]);
	}
	for(i=0;i<m;i++)
	{
		sd(cnt[i]);
		Query[i].resize(cnt[i]+1);
		Query[i][0]=0;
		for(j=1;j<=cnt[i];j++)
		{
			sd(Query[i][j]);
			mark[Query[i][j]]=1;
		}
	}
	mark[0]=1;
	for(i=0;i<LIM;i++)
		if(mark[i])
			pts.PB(i);
	for(i=0;i<pts.size();++i)
		comp[pts[i]]=i;
	for(i=0;i<n;i++)
	{
		int x=lower_bound(pts.begin(),pts.end(),l[i])-pts.begin();
		int y=upper_bound(pts.begin(),pts.end(),r[i])-pts.begin()-1;
		v[x].PB(y);
	}
	int sz=(int)pts.size();
	root[0]=build_tree(0,sz);
	for(i=1;i<N;i++)
	{
		root[i]=root[i-1];
		for(j=0;j<v[i].size();j++)
			root[i]=update(root[i],0,sz,v[i][j]);
	}
	for(i=0;i<m;i++)
	{
		int ans=0;
		for(j=1;j<Query[i].size();j++)
		{
			ans+=query(root[comp[Query[i][j  ]]],0,sz,comp[Query[i][j]],sz);
			ans-=query(root[comp[Query[i][j-1]]],0,sz,comp[Query[i][j]],sz);
		}
		printf("%d\n",ans);
	}
}