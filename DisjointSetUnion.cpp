//SNIPPET FOR UNION-FIND-------------------------
#define N 100010
int parent[N];	//immediate parent of every node
int Rank[N];	//Rank of each subset, where a subset is identified by its root.

int find(int cur)
{
	if(parent[cur]==cur)
		return cur;
	return parent[cur]=find(parent[cur]);
}

void Union(int x,int y)
{
	int xroot=find(x);
	int yroot=find(y);
	if(xroot==yroot)
		return;
	if(Rank[xroot]<Rank[yroot])
		swap(xroot,yroot);
	parent[yroot]=xroot;
	if(Rank[xroot]==Rank[yroot])
		Rank[xroot]++;
}
void init(int n)
{
	int i;
	for(i=0;i<=n;++i)
	{
		Rank[i]=0;
		parent[i]=i;
	}
}
//---------END OF SNIPPET-------------
