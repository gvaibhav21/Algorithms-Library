// Code for problem 427 D on Codeforces, example usage of Suffix Automaton
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
#define INF 100000
// suffix automaton
#define N 100010
#define M 28
//alphabet size

int getint(char c)
{
	if(c>='a' && c<='z')
		return c-'a';
	if(c=='$')
		return 26;
	return 27;
}

struct suffix_automata
{
	vector<int> Next[2*N];
	int link[2*N],len[2*N],dp[2][2*N];
	bool mark[2*N];
	int node_cnt,last,ans;

	suffix_automata()
	{
		for(int i=0;i<2*N;++i)
			Next[i].resize(M,0);
		link[0]=-1;
		len[0]=0;
		last=0;
		node_cnt=1;
		ans=INF;
		clr(mark);
	}
	void add_letter(int c)
	{
		int cur=node_cnt++;
		int it=last;

		len[cur]=len[last]+1;
		last=cur;
		
		while(it!=-1)
		{
			if(Next[it][c]!=0)	break;
			Next[it][c]=cur;
			it=link[it];
		}
		if(it==-1)	return (void)(link[cur]=0);
		if(len[it]+1==len[Next[it][c]])	return (void)(link[cur]=Next[it][c]);
		
		int clone=node_cnt++,q=Next[it][c];
		link[clone]=link[q];
		for(int i=0;i<M;++i)
			Next[clone]=Next[q];
		len[clone]=len[it]+1;
		link[cur]=link[q]=clone;
		
		while(it!=-1)
		{
			if(Next[it][c]!=q)	break;
			Next[it][c]=clone;
			it=link[it];
		}
	}
	void go(int cur)
	{
		if(mark[cur])
			return;
		
		mark[cur]=1;
		dp[0][cur]=dp[1][cur]=0;
		
		for(int i=0;i<M;i++)
			if(Next[cur][i])
			{
				if(i==26)
					dp[0][cur]++;
				else if(i==27)
					dp[1][cur]++;
				
				go(Next[cur][i]);
				
				dp[0][cur]+=dp[0][Next[cur][i]];
				dp[1][cur]+=dp[1][Next[cur][i]];
			}
		
		if(dp[0][cur]==1 && dp[1][cur]==2)
			ans = min(ans,len[link[cur]]+1);
	}
}SA;
string s,s1,s2;
int main()
{
	cin>>s1>>s2;
	s = s1 + '$' +s2 + '#';

	for(int i=0;i<s.length();i++)
		SA.add_letter(getint(s[i]));
	SA.go(0);
	if(SA.ans==INF)
		SA.ans=-1;
	printf("%d\n",SA.ans);
}