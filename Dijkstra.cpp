//SNIPPET FOR Dijkstra's Algorithm----------------
#define N 100010 
#define INF 1000000000
bool mark[N];
vector<pair<int,int> > v[N];
int d[N];

int dijkstra(int st,int en)
{
	int i,cur;
	for(i=0;i<N;++i)
	{
		mark[i]=0;
		d[i]=INF;
	}
	priority_queue<pair<int,int> > q;
	d[st]=0;
	q.push(MP(0,st));
	while(!q.empty())
	{
		pair<int,int> p=q.top();
		cur=p.S;
		if(cur==en)
			return d[cur];
		q.pop();
		if(mark[cur])	continue;
		mark[cur]=1;
		for(i=0;i<v[cur].size();++i)
		{
			if(d[v[cur][i].F]>(d[cur]+v[cur][i].S))
			{
				d[v[cur][i].F]=(d[cur]+v[cur][i].S);
				q.push(MP(-d[v[cur][i].F],v[cur][i].F));
			}
		}
	}
	return d[en];
}
//------------------SNIPPET ENDS----------------------------------