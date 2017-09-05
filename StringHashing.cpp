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
#define LIM 1000010

ll mod[2]={1000000007,1000000009};
 
ll front[2][LIM];
ll back[2][LIM];
 
ll p[2][LIM];
ll pInv[2][LIM];

char s[LIM];

ll pow1(ll a,ll b,ll mod){
	if(b==0)	return 1;
	ll ret=pow1(a,b/2,mod);
	ret=(ret*ret)%mod;
	if(b&1)	ret=(a*ret)%mod;
	return ret;
}

void init()
{
	p[0][0]=p[1][0]=1;
	pInv[0][0]=pInv[1][0]=1;
	for(int i=0;i<2;++i)
	{
		for(int j=1;j<LIM;++j)
		{
			p[i][j]=(p[i][j-1]*29)%mod[i];
			pInv[i][j]=pow1(p[i][j],mod[i]-2,mod[i]);
		}
	}
}
void init_hash(int l)
{
	for(int j=0;j<2;++j)
	{
		front[j][0]=(s[0]-'a'+1);
		for(int k=1;k<l;++k)
		{
			front[j][k]=front[j][k-1];
			front[j][k]=(front[j][k]+(s[k]-'a'+1)*p[j][k]%mod[j])%mod[j];
		}
		back[j][l-1]=s[l-1]-'a'+1;
		for(int k=l-2;k>=0;--k)
		{
			back[j][k]=back[j][k+1];
			back[j][k]=(back[j][k]+(s[k]-'a'+1)*p[j][l-1-k]%mod[j])%mod[j];
		}
	}
}

inline ll HF(int l,int r,int f)
{
	ll val=front[f][r];
	if(l)
		val=(val-front[f][l-1]+mod[f])%mod[f];
	val=(val*pInv[f][l])%mod[f];
	return val;
}
 
inline ll HB(int l,int r,int f,int len)
{
	ll val=back[f][l];
	if(r<len-1)
		val=(val-back[f][r+1]+mod[f])%mod[f];
	val=(val*pInv[f][len-1-r])%mod[f];
	return val;
}
 
inline pair<int,int> calc_f(int l,int r)
{
	return MP(HF(l,r,0),HF(l,r,1));
}
inline pair<int,int> calc_b(int l,int r,int len)
{
	return MP(HB(l,r,0,len),HB(l,r,1,len));
}
int main()
{
	init();	
	ss(s);
	int l=strlen(s);
	init_hash(l);
}
