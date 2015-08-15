#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define MAX1 11
#define MAX2 23
typedef short IP[4];
typedef enum{TRUE = 1,FALSE = 0}boolean;
typedef struct { IP p; char *comp_name; } Element;
typedef struct { Element e; boolean deleted;  boolean empty; } Cell;
typedef Cell secLevelHashTable[MAX2];
typedef secLevelHashTable *FirstLevelHashTable[MAX1];
typedef FirstLevelHashTable hashTable;
void initFirstHTable(hashTable H)
//This function allocates memory for second level hash tables and initializes first level hash table cells as pointers pointing to the starting address of each second level hash table.
{
    int i,j;
    for(i=0;i<MAX1;i++)
   {
       H[i]= (secLevelHashTable*)malloc(sizeof(secLevelHashTable));
       for(j=0;j<MAX2;j++)
       {
           initSecHTables(H[i][j]);
       }
   }
}
void initSecHTables(Cell *ptr)
 //This function initializes the deleted and empty flags in all the second level hash tables.
 {
     ptr->deleted=FALSE;
     ptr->empty=TRUE;
 }
 int FirstLevelHashFunc(Element e)
 //This function takes the element to be processed (means inserted/searched/deleted) as input, applies hash function on the first level key (i.e. e.p[3])and returns the index of the first level hash table
  {

  }
  SecLevelHashFunc(Element e)
  //his function takes the element to be processed as input and applies hash function on the second level key (i.e e.p[2]) and returns the index of the second level hash table. (5)
int quadProbe(Element e,Cell *ptr)
//This function finds the position of the element in the second level hash table by using quadratic probing.
 void addAddress(Element e,hashTable H)
 //this function adds the element in the respective second level hash table cell and updates the empty flag of that cell.
  boolean findAddress(Element e, hashTable H)
  //This function finds the element in the respective second level hash table and returns TRUE if found else returns FALSE.
   void deleteAddress(Element e, hashTable H)
   // This function finds the element in the second level hash table and mark that cell as deleted. (9) driver function This function will first initialize the first and second level hash table. Then open the input file and read the elements from the file. Call addAddress(), findAddress() and deleteAddress() function to experiment the processing of hash tables.
int main()
{

    return 0;
}
