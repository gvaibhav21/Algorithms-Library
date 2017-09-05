#define N 100010

int maxx[4*N],l[4*N];

// merge
inline void refresh(int n)
{
	maxx[n]=max(maxx[n*2],maxx[n*2+1]);
}

void build_tree(int n,int si,int sj)
{
	l[n]=0;
	if(si==sj)
	{
		maxx[n]=0;
		return;
	}
	build_tree(n*2,si,(si+sj)/2);
	build_tree(n*2+1,(si+sj)/2+1,sj);
	refresh(n);
}

//propagate
inline void push(int n,int si,int sj)
{
	maxx[n]+=l[n];
	if(si!=sj)
	{
		l[n*2]+=l[n];
		l[n*2+1]+=l[n];
	}
	l[n]=0;
}
void update(int n,int si,int sj,int st,int en,int val)
{
	if(l[n])
		push(n,si,sj);
	if(si>en||sj<st)
		return;
	if(si>=st&&sj<=en)
	{
		l[n]+=val;
		push(n,si,sj);
		return;
	}
	update(n*2,si,(si+sj)/2,st,en,val);
	update(n*2+1,(si+sj)/2+1,sj,st,en,val);
	refresh(n);
}
int query(int n,int si,int sj,int st,int en)
{
	if(l[n])
		push(n,si,sj);
	if(si>en||sj<st)
		return -1;
	if(si>=st&&sj<=en)
		return maxx[n];
	int v1=query(n*2,si,(si+sj)/2,st,en);
	int v2=query(n*2+1,(si+sj)/2+1,sj,st,en);
	refresh(n);
	return max(v1,v2);
}