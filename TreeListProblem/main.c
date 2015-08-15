#include <stdio.h>
#include <stdlib.h>
struct node{
int i;
struct node* left;
struct node* right;
};
typedef struct node node;
void printList(node* head)
{
    printf("**********************\n");
    node* cur=head;
    int idx=1;
    do
    {
        printf("%d. %d\n",idx,cur->i);
        cur=cur->right;
        idx++;

    }while(cur!=NULL);
}
node* newNode( int val)
{
    node* ret = (node*) malloc(sizeof (node));
    ret->i = val;
    ret->left=NULL;
    ret->right=NULL;
    return ret;
}
node* insert(node* root,node* new)
{
    if(root==NULL) return new;
    node* cur= root,*prev=NULL;
    while(cur!=NULL)
    {
        prev=cur;
        if(cur->i<new->i)
            cur=cur->right;
        else cur=cur->left;
    }
    if(prev->i<new->i) prev->right=new;
    else prev->left = new;
    return root;
}
void printTree(node* root)
{
    if(root==NULL) return;
    printTree(root->left);
    printf("%d\n",root->i);
    printTree(root->right);
}
node* travLeft(node* cur)
{
    if(cur==NULL ) return NULL;
    node* prev = NULL;
    while(cur!=NULL)
    {
        prev = cur;
        cur=cur->left;
    }
    return prev;
}
node* travRight(node* cur)
{
    if(cur==NULL ) return NULL;
    node* prev = NULL;
    while(cur!=NULL)
    {
        prev = cur;
        cur=cur->right;
    }
    return prev;
}
node* turnToList(node* root)
{
    if(root == NULL) return root;
    node* prev= turnToList(root->left);
    node* next = turnToList(root->right);
    root->left= travRight(prev);
    if(root->left) root->left->right=root;

    root->right= travLeft(next);
        if(root->right) root->right->left=root;

    return root;
}
int main()
{
    int i;
    node* Thead = NULL;
    for(i =0 ; i < 15; i ++ )
    {
        int val;
        scanf("%d",&val);
        node* new = newNode(val);
        Thead = insert(Thead,new);
    }
    //printTree(Thead);
    node* Lhead = turnToList(Thead);
    printList(travLeft(Lhead));
    return 0;
}
