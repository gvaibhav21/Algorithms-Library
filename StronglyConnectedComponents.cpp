/*-----------code for scc-----------*/
#define N 100010
stack<int> order;
bool mark[N];
vector<int> v1[N];//forward graph
vector<int> v2[N];//reverse graph
vector<int> nodeList[N];// List of nodes in each scc
int scc[N],sccCount;// id of scc each node belongs to
void dfs(int cur)
{
	int i;
	mark[cur]=1;
	for(i=0;i<v2[cur].size();++i)
		if(!mark[v2[cur][i]])
			dfs(v2[cur][i]);	
	order.push(cur);
}
void dfs1(int cur)
{
	int i;
	mark[cur]=1;
	scc[cur]=sccCount;
	nodeList[sccCount].PB(cur);
	for(i=0;i<v1[cur].size();++i)
		if(!mark[v1[cur][i]])
			dfs1(v1[cur][i]);
}
void computeScc(int n)
{
	int i;
	sccCount=0;
	while(!order.empty())
		order.pop();

	for(i=0;i<=n;++i)
	{
		nodeList[i].resize(0);
		mark[i]=0;
	}
	for(i=1;i<=n;++i)
		if(!mark[i])
			dfs(i);
	for(i=0;i<=n;++i)
		mark[i]=0;
	while(!order.empty())
	{
		if(!mark[order.top()])
		{
			dfs1(order.top());
			sccCount++;
		}
		order.pop();
	}
}
/*------------------------*/
