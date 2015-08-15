#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define CSIZE 7
#define T_SIZE 11
#define p 13
struct Hash_item;
struct Hash_id;
struct node;
typedef struct Hash_item Hash_item;
typedef struct Hash_id Hash_id;
typedef struct node node;
int n;
struct Hash_item{
Hash_id* table[T_SIZE];
};
struct Hash_id{
node* table[CSIZE];
};
struct node{
int cust_id, item_cost;
char item_code[20];
node* next;
};

int hash1(char *key, int size)
    {
        int i,sum=0;
       for(i=0;key[i]!='\0';i++)
       {
           sum+=key[i];
       }
       return (sum%p)%size;
    }
int hash2(int key, int size)
   {
       int sum=0;
      while(key)
      {
          sum+= key%10;
          key/=10;
      }
      return sum%size;
   }
void insertHashtable(Hash_item* table1, int htsize, int cid, char *item, int price){
    static int cnt=0;
    int idx=hash1(item,htsize);
    int idx2=hash2(cid,CSIZE);
    node* newNode= (node*) malloc(sizeof(node));
    newNode->cust_id=cid;
    newNode->item_cost=price;
    strcpy(newNode->item_code,item);
    newNode->next=NULL;
    if(table1->table[idx])
    {
      if((table1->table[idx])->table[idx2])
     {
         node* temp= table1->table[idx]->table[idx2];
        table1->table[idx]->table[idx2]=newNode;
        newNode->next=temp;
     }
     else
      {
         table1->table[idx]->table[idx2]=newNode;
     }
    }
    else
    {
      table1->table[idx]=(Hash_id*) malloc(sizeof(Hash_id));
      memset(table1->table[idx]->table,0,sizeof(table1->table[idx]->table));
      table1->table[idx]->table[idx2]=newNode;
      newNode->next=NULL;
    }

    }
    Hash_item * populateHashtable( char * filename){
        Hash_item* table1=(Hash_item*) malloc(sizeof(Hash_id)*T_SIZE);
        memset(table1->table,0,sizeof(table1->table));
        FILE* fp= fopen(filename,"r");
        int cid,price;
        char item[20];
        while(fscanf(fp,"%d %s %d",&cid,item,&price)!=EOF){
            insertHashtable(table1,T_SIZE,cid,item,price);
        }
        return table1;
}

 void printHT(Hash_item ht, int htsize, FILE *fp){
     int i,j;
    for(i=0;i<htsize;i++)
    {
        if(ht.table[i])
        {
            for(j=0;j<CSIZE;j++)
            {
                node* temp=ht.table[i]->table[j];
                while(temp)
                {
                    fprintf(fp,"%d %s %d\n",temp->cust_id,temp->item_code,temp->item_cost);
                    temp=temp->next;

                }
            }
        }
    }
}


int findEntry(Hash_item ht, int htsize, int cust_id, char *item_code){
   // This function searches for an entry corresponding to customer's id, cust_id, and item_code. This function returns the cost of the item purchased by the customer if found; else it returns -1.
int idx=hash1(item_code,T_SIZE);
int idx2=hash2(cust_id,CSIZE);
node* temp=ht.table[idx]->table[idx2];
while(temp)
{
    if(temp->cust_id==cust_id && strcmp(temp->item_code,item_code)==0)
    {
        return temp->item_cost;
    }
    temp=temp->next;
}
return -1;
}
int purchasedby(Hash_item ht, int htsize, int cust_id){
   // This function traverses through the two hash tables and computes the total cost of the items purchased by the customer, cust_id.

int i;
int idx2=hash2(cust_id,CSIZE);
int sum=0;
for(i=0;i<T_SIZE;i++)
{
    if(ht.table[i])
    {
        if(ht.table[i]->table[idx2])
        {
            node* temp= ht.table[i]->table[idx2];
            if(temp->cust_id==cust_id) sum+= temp->item_cost;
        }
    }
}
return sum;
}

int main(int argc,char* argv[])
{

    Hash_item* hashtable=populateHashtable(argv[1]);
    FILE* fp=fopen(argv[2],"w");
    printHT(*hashtable,T_SIZE,fp);
    //printf("%d\n",findEntry(*hashtable,T_SIZE,4654,"LQWWRLLH"));
    return 0;
}
