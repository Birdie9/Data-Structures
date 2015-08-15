#include <stdio.h>
#include <stdlib.h>
int n;
int median(int*a,int st,int mid,int en)
{
    if(a[mid]<=a[en] )
    {
        if(a[en]<=a[st]) return en;
        else if(a[st]<=a[mid])return mid;
        else return st;
    }
    else
    {
        if(a[mid]<=a[st]) return mid;
        else if(a[st]<=a[en])return en;
        else return st;
    }
}
void sort(int* a,int n)
{
int i,j;
    for(i=1;i<n;i++)
    {
        int key=a[i];
        for(j=i-1;j>=0 && a[j]>key;j--)
        {
            a[j+1]=a[j];
        }
        a[j+1]=key;
    }
}

void rselect(int* a,int len,int k)
{
    int i,st,temp;
    for(st=i=0;i<len-1;i++)
    {
        if(a[i]>a[len-1]) continue;
        temp=a[i];
        a[i]=a[st];
        a[st]=temp;
        st++;
    }
    temp=a[len-1];
        a[len-1]=a[st];
        a[st]=temp;
        if(k==st) return;
        if(st>k) rselect(a,st,k);
        else rselect(a+st,len-st,k-st);

}
int median_of_5(int* A)
{
        int B[3] = { 0, 1, 2 };
    int i;

    if (A[1] < A[0])            // Make sure that the first two
    {                           // are sorted with respect to
        B[0] = 1;               // each other
        B[1] = 0;
    }                           // Insert the other three
                                // elements in this sorted
    for (i=2; i<5; i++)         // index
    {
        if (A[i] < A[B[0]])           // If less than the first
        {                             // insert at beginning
            B[2] = B[1];
            B[1] = B[0];
            B[0] = i;
        }
        else if (A[i] < A[B[1]])      // If only less than the
        {                             // second, insert as
            B[2] = B[1];              // the second
            B[1] = i;
        }
        else if (A[i] < A[B[2]])      // If only less than the
            B[2] = i;                 // third, overwrite
    }                                 // the current third
    return B[2];
}
int med_med(int* a,int n)
{ if(n<5) return 0;
    int i;

        for(i=0;5*i<(n-4);i++)
        {
            int m=median_of_5(a+5*i);
            int temp=a[i];
            a[i]=a[5*i+m];
            a[5*i+m]=temp;
        }
         rselect(a,i,i/2);

    return i/2;
}

int partition(int* a,int st,int en)
{
      int pivotIndex= med_med( a+st,1-st+en);
pivotIndex+=st;
   int temp=a[en];
   int i;
 a[en]=a[pivotIndex];
   a[pivotIndex]=temp;
   int j=st-1;
   for(i=st;i<en;i++)
   {
       if(a[i]<=a[en])
       {
           int temp=a[++j];
           a[j]=a[i];
           a[i]=temp;
       }
   }
   temp=a[en];
   a[en]=a[j+1];
   a[j+1]=temp;
   return j+1;
}
void quisort(int* a,int st,int en)
{
if(st>=en)return;
int pivot=partition(a,st,en);
quisort(a,st,pivot-1);
quisort(a,pivot+1,en);
}
int a[100000];
int main(int argc,char* argv[])
{
   // int n;

    sscanf(argv[1],"%d",&n);
    n=100000;
    FILE* fp= fopen("input.txt","r");
    int i;
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%d",&a[i]);
    }
    quisort(a,0,n-1);
    for(i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
