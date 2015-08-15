#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node* next;
} node;
void print(node* head)
{
    node*cur=head;
    while(cur)
    {
        printf("%d\n",cur->data);
        cur=cur->next;
    }
}
node* insertionsort(node* head)
{
    node* cur=head->next;
    node* prev=head;
    while(cur)
    {
        //printf("%d\n",cur->data);
        if(cur->data>=prev->data)
        {
            prev=cur;
            cur=cur->next;
        }
        else
        {
            node*temp=cur->next;
            prev->next=cur->next;
            node* cur2=head;
            if(head->data > cur ->data)
            {
                cur->next=head;
                head=cur;
            }
            else
            {
                while(cur2->next->data <= cur->data) {
                        cur2= cur2->next;

                }
                cur->next=cur2->next;
                cur2->next=cur;
            }
            cur=temp;
        }
    }
    return head;
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
    head=insertionsort(head);
    print(head);
    return 0;
}
