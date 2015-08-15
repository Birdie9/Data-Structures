#include <stdio.h>
#include <stdlib.h>
struct node;
typedef struct node node;
struct node {
int i;
node* left;
node* right;
node* succ;
};
int height(node* root){
if(root==NULL)return 0;
int h1= height(root->left);
int h2=height(root->right);
if(h1>h2) return (1+h1);
else return (1+h2);

}
node* balance(node* root)
{
    node* ret;
    int h1=height(root->left);
    int h2=height(root->right);
    while(h1-h2>1  )
    {
        node* cur=root->left;
        node* prev=root;
        while(cur->right)
        {
            prev=cur;
            cur=cur->right;
        }
        if(cur->left) {
            prev->right=cur->left;


        }

        cur->left=root->left;
            cur->right=root->right;
            root->left=NULL;
            root->right=NULL;
        insert(root,root->left);

    }

}
int main()
{

    return 0;
}
