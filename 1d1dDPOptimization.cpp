// Code for problem ACQUIRE on spoj, example usage of 1D-1D DP Optimization
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
#define INF 100000000000000000ll
vector< pair<int,int> > s;

vector<pair<ll,ll> > v;
pair<ll,ll> a[500010];
ll dp[500010];
inline ll C(int i,int j)
{
	if(i>j)
		return 0;
	return v[i-1].F*v[j-1].S;
}
int main()
{
	int n,i,j,t=1;
	while(t--)
	{
		s.clear();
		v.clear();
		sd(n);
		for(i=0;i<n;++i)
		{
			sl(a[i].F);
			sl(a[i].S);
		}
		sort(a,a+n);
		int prev=0;
		for(i=n-1;i>=0;--i)
		{
			if(a[i].S>prev)
			{
				v.PB(a[i]);
				prev=a[i].S;
			}
		}


		// dp Calculation starts
		for(i=0;i<50010;++i)
			dp[i]=INF;
		dp[0]=0;
		s.push_back(MP(1,0));
		
		n=v.size();
		for(i=1;i<=n;++i)
			dp[i]=C(1,i);

		for(i=1;i<n;++i)
		{
			prev=n;
			while(true)
			{
				int pos=max(s.back().F,i+1);
				if(dp[s.back().S]+C(s.back().S+1,pos)>dp[i]+C(i+1,pos))
				{
					if(s.back().F<i+1)
					{
						s.push_back(MP(i+1,i));
						break;
					}
					else if(s.back().F==i+1)
					{
						s.pop_back();
						s.push_back(MP(i+1,i));
						break;
					}
					else
					{
						prev=s.back().F;
						s.pop_back();
					}
				}
				else
				{
					int lo=pos,hi=prev,mid;
					while(lo<hi)
					{
						mid=(lo+hi)/2;
						if(dp[s.back().S]+C(s.back().S+1,mid)>dp[i]+C(i+1,mid))
							hi=mid;
						else
							lo=mid+1;
					}
					mid=(lo+hi)/2;
					if(dp[s.back().S]+C(s.back().S+1,mid)>dp[i]+C(i+1,mid))
						s.push_back(MP(mid,i));
					break;
				}
			}
			int pos=lower_bound(s.begin(),s.end(),MP(i+1,1000000))-s.begin();
			int best=s[pos-1].S;
			dp[i+1]=min(dp[i+1],dp[best]+C(best+1,i+1));
		}
		printf("%lld\n",dp[n]);
	}
}

/*
20
3 98
23 66
44 59
46 30
73 28
87 15
87 9
90 6
99 1
100 1
100 1
100 1
100 1
100 1
100 1
100 1
100 1
100 1
100 1
100 1
*/