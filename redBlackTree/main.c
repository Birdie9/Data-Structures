#include <stdio.h>
#include <stdlib.h>

enum Color {BLACK,RED};

struct node{
int key;
struct node* left;
struct node* right;
struct node* p;
enum Color color;
};
typedef struct node node;

struct tree{
node* root;
node* nil;
};
node*  newNode(struct tree * T, int val)
{
    node* z = (node*) malloc(sizeof(node));
    z->left=T->nil;
    z->right=T->nil;
    z->p = T->nil;
    z->color=RED;
    z->key=val;
    return z;
}
void leftRotate(struct tree* T,node* x)
{
    node* y = x->right;
    y->p=x->p;
    if(T->root==x) T->root=y;
    else if(x->p->left==x) x->p->left=y;
    else if(x->p->right==x) x->p->right=y;
    x->right=y->left;
    if(y->left!=T->nil) y->left->p=x;
    y->left=x;
    x->p=y;


}
void rightRotate(struct tree* T,node* y)
{
    node* x=y->left;
    x->p=y->p;
    if(T->root==y) T->root=x;
    else if(y->p->left==y) y->p->left=x;
    else if(y->p->right==y) y->p->right=x;
    y->left=x->right;
    if(x->right!=T->nil) x->right->p=y;
    x->right=y;
    y->p=x;

}
void fix(struct tree* T,node* z)
{
    while(z->p->color == RED)
    {
        if(z->p==z->p->p->left)
        {
            node* y = z->p->p->right;
            if(y->color==RED)
            {
                z->p->color=BLACK;
                y->color=BLACK;
                y->p=RED;
                z=y->p;
            }
            else if(z==z->p->right)
            {
                z=z->p;
                leftRotate(T,z);
            }
            z->p->color=BLACK;
            z->p->p->color=RED;
            rightRotate(T,z->p->p);
        }
        else{
            node* y = z->p->p->left;
            if(y->color==RED)
            {
                z->p->color=BLACK;
                y->color=BLACK;
                y->p=RED;
                z=y->p;
            }
            else if(z==z->p->right)
            {
                z=z->p;
                leftRotate(T,z);
            }
            z->p->color=BLACK;
            z->p->p->color=RED;
            rightRotate(T,z->p->p);
        }
    }
    T->root->color= BLACK;
}

void insert ( struct tree * T,int val)
{
node* z=newNode(T, val);
node* cur= T->root;
node* prev = NULL;
while(cur!=T->nil){
    if(cur->key<val)
    {
        prev=cur;
        cur=cur->right;
    }
    else
    {
        prev=cur;
        cur=cur->left;
    }
}
if(prev!=NULL)
{
    if(prev->key<val)
    {
        prev->right=z;
    }
    else prev->left = z;
}
else T->root = z;

fix(T,z);
}
printN(node* rt)
{
    printf("%d ",rt->key);
}
void print(node* rt,struct tree * T)
{
if(rt==T->nil) return;
print(rt->left,T);
printN(rt);
print(rt->right,T);
}
void del(struct tree* T,int val)
{

}
int main()
{
    node* nil = ( node*)malloc(sizeof (node));
    nil->left=NULL;
    nil->right=NULL;
    nil->color= BLACK;

    struct tree * T;
    T=(struct tree*) malloc(sizeof (struct tree));
    T->nil = nil;
    T->root= nil;

    int val;
    while(scanf("%d",&val))
    {
        if(val==-999) break;
        else insert(T,val);
    }
    print(T->root,T);
     while(scanf("%d",&val))
    {
        if(val==-999) break;
        else del(T,val);
    }
    return 0;
}
