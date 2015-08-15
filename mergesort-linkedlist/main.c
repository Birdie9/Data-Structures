#include <stdio.h>
#include <stdlib.h>
struct node;
typedef struct node node;
struct node{
int data;
node* next;
};
struct node* SortedMerge(struct node* a, struct node* b)
{
  node* head = NULL,*prevb=NULL,*preva=NULL;

  /* Base cases */
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);

if((a->data)>(b->data))
{
    head=b;
    b=b->next;
    head->next=a;
}
else head=a;
a=head;
while(b!=NULL && a!=NULL)
{
    if(a->data<=b->data)
    {
        preva=a;
        a=a->next;
    }
    else
    {
        node* temp=b->next;
        if(prevb)
            prevb->next=b->next;
        b->next=a;
        if(preva)
            preva->next=b;
        preva=b;
        b=temp;
    }
}
if(a==NULL)
    preva->next=b;
    return head;
}
void mergesort(node** headref)
{
    node* head = *headref;
    node* a=head;
    node* b=head;
    if((head==NULL)|| head->next==NULL)return;
    b=b->next;
    while(b->next && b->next->next)
    {
        b=b->next->next;
        a=a->next;
    }
    b=head;
    node*temp=a->next;
    a->next=NULL;
    a=temp;
    mergesort(&a);
    mergesort(&b);
    *headref=SortedMerge(a,b);
}
void print(node* head)
{
    node*cur=head;
    while(cur)
    {
        printf("%d\n",cur->data);
        cur=cur->next;
    }
}
int main()
{
    FILE* fp=fopen("input.txt","r");
    int i;
    node* head,*prev;
    head=(node*) malloc(sizeof(node));
    fscanf(fp,"%d",&i);
    head->data=i;
    prev=head;
    while(fscanf(fp,"%d",&i)!=EOF)
    {
        node* newnode=(node*) malloc(sizeof(node));
        prev->next=newnode;
        newnode->data=i;
        prev=newnode;
    }
    prev->next=NULL;
    fclose(fp);
  //  printf("closing");
   node** headref=&head;
   mergesort( headref);
  print(*headref);
    return 0;
}
