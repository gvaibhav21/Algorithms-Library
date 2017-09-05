// Code for problem 321 E on Codeforces, example usage of Divide and Conquer DP Optimization
#include<bits/stdc++.h>
using namespace std;
 
#define sd(mark) scanf("%d",&mark)
#define ss(mark) scanf("%s",&mark)
#define sl(mark) scanf("%lld",&mark)
#define clr(mark) memset(mark,0,sizeof(mark))
#define F first
#define S second
#define MP make_pair
#define pb push_back
#define ll long long
#define INF 1000000000
int u[4010][4010];
char s[8010];
int c[4010][4010];
int dp[4010][4010];
int best[4010][4010];
void divide_conquer(int i,int si,int sj,int l,int r)
{
	if(si>sj)
		return;
	int mid=(si+sj)/2,minn=INF,best;
	for(int j=l;j<min(mid,r+1);++j)
	{
		if(dp[i-1][j]+c[j+1][mid]<minn)
		{
			minn=dp[i-1][j]+c[j+1][mid];
			best=j;
		}
	}
	dp[i][mid]=minn;
	go(i,si,mid-1,l,best);
	go(i,mid+1,sj,best,r);
}
int main()
{
	int n,i,j,l;
	sd(n);sd(k);
	for(i=0;i<n;++i)
	{
		gets(s);
		for(j=0;j<n;++j)
			u[i][j]=s[2*j-2]-'0';
	}
	for(i=0;i<=n;++i)
		clr(c[i]);
	for(i=0;i<=n;++i)
		clr(dp[i]);
	for(l=1;l<n;++l)
		for(i=1;i+l<=n;++i)
		{
			j=i+l;
			c[i][j]=c[i][j-1]+c[i+1][j]-c[i+1][j-1]+u[i-1][j-1];
		}
	for(i=1;i<=k;++i)
		go(i,i,n,0,n);
	printf("%d\n",dp[k][n]);
}