/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2015 Jayati                                                    */
/*                                                                            */
/*   Description                                                           */
/*                                                                            */
/* ========================================================================== */
#include<stdio.h>
#include<stdlib.h>
#define INF 1000000000
typedef struct heap{
	int arr[10001][2];
	int size;
	int idx[10001];
}heap;
int left(int i)
{
	return 2*i+1;
}
int right(int i)
{
	return 2*i+2;
}
int parent(int i)
{
	int temp=i/2;
	if(2*temp==i) return temp-1;
	else return temp;
}
void swap(heap* h,int a,int b)
{
	int (* arr)[10001][2];
	arr=&(h->arr);
	h->idx[(*arr)[a][0]]=b;
	h->idx[(*arr)[b][0]]=a;
	int temp1=(*arr)[a][0],temp2=(*arr)[a][1];

	(*arr)[a][0]=(*arr)[b][0];
	(*arr)[a][1]=(*arr)[b][1];

	(*arr)[b][0]=temp1;(*arr)[b][1]=temp2;

	return;
}

void minHeapify(heap* h,int i)
{
	int (* arr)[10001][2]=&(h->arr);
	int smallest;
	int lefta=left(i);
	int righta=right(i);
	if(lefta<(h->size) && (*arr)[lefta][1]<(*arr)[i][1]) smallest=lefta;
	else smallest=i;
	if(righta<(h->size) &&(*arr)[righta][1]<(*arr)[smallest][1]) smallest=righta;
	if(smallest!=i)
	{
		swap(h,i,smallest);
		minHeapify(h,smallest);
	}
}
void BuildHeap(heap* h,int size)
{
	int(* arr)[10001][2]=&(h->arr);
	int i;
	int cur=size-1;
	int par=parent(cur);
	for(i=par;i>=0;i--)
	{
		minHeapify(h,i);
	}
}

void insert(heap* h,int key,int u)
{
	h->size++;
	h->arr[h->size-1][1]=key;
	h->arr[h->size-1][0]=u;
	h->idx[u]=h->size-1;
	int cur=h->size-1;
	int par=parent(h->size-1);
	while(par>=0 && h->arr[par][1]>key)
	{
		swap(h,par,cur);
		cur=par;
		par=parent(cur);
	}
}
void deleteKey(heap* h,int i)
{
	int size=h->size;
	swap(h,i,size-1);
	(h->size)--;
	minHeapify(h,i);
}

void decreaseKey(heap* h , int u,int newKey)
{
	int idx=h->idx[u];
	h->arr[idx][1]=newKey;
	int cur=idx;
	int par=parent(cur);
	while(par>=0 && h->arr[par][1]>newKey)
	{
		swap(h,par,cur);
		cur=par;
		par=parent(cur);
	}
}
void extractMin(heap* h,int* a ){
	a[0]=h->arr[0][0];
	a[1]=h->arr[0][1];
	deleteKey(h,0);
}
int mat[10001][10001];
int marked[10001];
int dijkstra(heap* h,int t)
{
	int i,minNode[2],mind;
	while(!marked[t])
	{
		extractMin(h,minNode);
		int u=minNode[0];
		mind=minNode[1];
		if(mind==INF)break;
		marked[u]=1;
		for(i=0;i<10001;i++)
		{
			if(mat[u][i]!=INF)
			{
				int idx=h->idx[i];
				if(h->arr[idx][1]>mind+mat[u][i]) decreaseKey(h,i,mind+mat[u][i]);
			}
		}
	}
	if(marked[t] ) return mind;
	else return -1;
}
int main()
{

	int t,i,j,k;
	scanf("%d",&t);
	for(i=0;i<t;i++)
	{

		int v,m;
		scanf("%d%d",&v,&m);
		heap* h = (heap*)malloc(sizeof(heap));
		h->size=v;
		int q,z;
		for(q=0;q<10001;q++) marked[q]=0;
		for(z=0;z<10001;z++)for(q=0;q<10001;q++) mat[z][q]=INF;
		int k=0;
 		for(j=0;j<m;j++)
		{
			int a,b,c;
			scanf("%d",&a);
			scanf("%d",&b);
			scanf("%d",&c);
			mat[a][b]=c;
			if(!marked[a])
			{
				h->arr[k][0]=a;
				h->arr[k][1]=INF;
				h->idx[a]=k;
				marked[a]=1;
				k++;
			}
			if(!marked[b])
			{
				h->arr[k][0]=b;
				h->arr[k][1]=INF;
				h->idx[b]=k;
				marked[b]=1;
				k++;
			}
		}
		int s,t;
		scanf("%d %d",&s,&t);
		if(!marked[s]){marked[s]=1;h->arr[k][0]=s;h->arr[k][1]=INF;h->idx[s]=k;k++;}
		if(!marked[t]){marked[t]=1;h->arr[k][0]=t;h->arr[k][1]=INF;h->idx[t]=k;k++;}
		h->arr[h->idx[s]][1]=0;
		for(q=0;q<10001;q++) marked[q]=0;

		BuildHeap(h,v);
		int p=dijkstra(h,t);
		if(p!=-1)
		printf("%d\n",p);
		else printf("NO\n");
	}
	return 0;
}
