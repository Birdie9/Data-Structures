#include <stdio.h>
#include<stdlib.h>
struct node
{
int data;
struct node* next;
};
typedef struct node node;

struct node *partition(struct node *head, struct node *end, struct node **newHead, struct node **newEnd,struct node** prevTopivot)
{
    *prevTopivot=NULL;
    struct node *pivot = end;
    struct node *prev = NULL, *cur = head, *tail = pivot;
    while (cur != pivot)
    {
        if (cur->data < pivot->data)
        {
            if ((*newHead) == NULL)
                (*newHead) = cur;
            prev = cur;
            *prevTopivot=cur;;
            cur = cur->next;
        }
        else
        {
            if (prev)
                prev->next = cur->next;
            struct node *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    if ((*newHead) == NULL)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

node** quickSortRecur(node* head,node* end)
{
    if (!head || head == end)

        {
            node* headNtail[]={head,end};
            return headNtail;
        }
    node *newHead = NULL, *newEnd = NULL,*prevTopivot;
    struct node *pivot = partition(head, end, &newHead, &newEnd,&prevTopivot);
    if (newHead != pivot)
    {
        prevTopivot->next=NULL;
        node** headNtail = quickSortRecur(newHead, prevTopivot);
        newHead=headNtail[0];
        node* newTail=headNtail[1];
        newTail->next =  pivot;
    }
    // Recur for the list after the pivot element
     node** headNtail= quickSortRecur(pivot->next, newEnd);
     pivot->next=headNtail[0];
     headNtail[0]=newHead;
    return headNtail;
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
   node** headNtail=quickSortRecur( head,prev);

  print(headNtail[0]);
    return 0;
}
