/*
********************************************************************************************************************************************************
Programmer Details:

Name              :  Ebrahim Bharmal
Student ID        :  1001553077
Class             :  CSE 2320-003
Class Teacher     :  Dr. Bob P Weems


************************************************************************************************************************************************************

Assignment Description:

Assignment Name         : Lab Assignment 5
Objective of Assignment : 1. Understanding of hashing.
                          2. Understanding of graphs.
                          3. Understanding of strongly-connected components (Notes 14)

ASSUMPTION:              THE INPUT STRING IS NO LONGER THAN 25 CHARACTERS
						  
Requirements            :  write a  C program to determine strongly connected components for a directed graph. Where the input will be strings 

Compilation Command     : $gcc lab5_1001553077.c
Used on OMEGA

*****************************************************************************************************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
/*
FUNCTION GUIDE:

tailThenHead at line    :  69

read_input_file at line :  84

hashFunction at line    :  149

DFSvisit at line        :  224

reverseEdges at line    :  240

DFSvisit2 at line       :  275

getNextPrime at line    :  299

main at line            :  333
*/
int n;  // number of nodes
int e;  // number of edges
int hashTableSize; //Global Variable for hashTableSize
int totalCells;
struct edge {
  int tail,head,type; 
};
typedef struct edge edgeType;
edgeType *edgeTab;
int *firstEdge;  // Table indicating first in range of edges with a common tail

int *vertexStatus,*secondDFSrestarts;

int tailThenHead(const void* xin, const void* yin)
// Used in calls to qsort() and bsearch() for read_input_file()
{
int result;
edgeType *x,*y;

x=(edgeType*) xin;
y=(edgeType*) yin;
result=x->tail - y->tail;
if (result!=0)
  return result;
else
  return x->head - y->head;
}

void read_input_file(int *hashArray,char *ptrToStrings)
{
int a,b,i,j;
edgeType work;
edgeType *ptr;
char array1[26]; //char array to store the 1st string read
char array2[26]; //char array to store the 2nd string read

edgeTab=(edgeType*) malloc(e*sizeof(edgeType));
if (!edgeTab)
{
  printf("edgeTab malloc failed %d\n",__LINE__);
  exit(0);
}

// read edges
for (i=0; i<e; i++)
{
  scanf("%s %s",&array1,&array2);
  //Here hashFunction returns an Int value indicating the index at which the string is stored in array ptrToStrings
  edgeTab[i].tail= hashFunction(array1,hashArray,ptrToStrings);
  edgeTab[i].head= hashFunction(array2,hashArray,ptrToStrings);
}
// sort edges
qsort(edgeTab,e,sizeof(edgeType),tailThenHead);
// Coalesce duplicates into a single edge
j=0;
for (i=1; i<e; i++)
  if (edgeTab[j].tail==edgeTab[i].tail
     && edgeTab[j].head==edgeTab[i].head)
    ; 
  else
  {
    j++;
    edgeTab[j].tail=edgeTab[i].tail;
    edgeTab[j].head=edgeTab[i].head;
  }
e=j+1;
// For each vertex as a tail, determine first in range of edgeTab entries
firstEdge=(int*) malloc((n+1)*sizeof(int));
if (!firstEdge)
{
  printf("malloc failed %d\n",__LINE__);
  exit(0);
}
j=0;
for (i=0; i<n; i++)
{
  firstEdge[i]=j;
  for ( ;
       j<e && edgeTab[j].tail==i;
       j++)
    ;
}
firstEdge[n]=e;
}
/*
*********************************************************************************************************************************************************************
Function Name: hashFunction
Return Type: Int
Input: (char pointer to char array to be hashed, pointer to int hashArray, char pointer to the strings)
        WHERE ptrToStrings IS A 2D ARRAY HOLDING THE STRINGS READ
		
*********************************************************************************************************************************************************************
*/
int hashFunction(char *array,int *hashArray,char *ptrToStrings)
{
int i,n,l,h1,h2,j,k,m;
i=0;
k=0;
n = 0;
l =0;
h1 = 0;
h2 = 0;
unsigned int h =0; //Unsigned int h so that it can hold big values
unsigned int inValue=0;  //Unsigned int inValue so that it can hold big values
int subscript; //Variable for the index value of the string
int strlength; //Variable to store the length of the string
strlength = strlen(array);
for(j=0; *(array+j) != '\0';j++)
{
	h = h*10 + array[j]; //Compute the ASCII values of each character and then add it up.
}
inValue = h;
m = hashTableSize;
if(inValue >=0 )
{
	 //WHERE ptrToStrings IS A 2D ARRAY HOLDING THE STRINGS READ
	i=h1=inValue%m; //Where m is the sizae of the HashTable
    h2=inValue%(m-1)+1;
	 while ( *(hashArray +i) != -1 && *(hashArray +i) != inValue)
	 {
    i=(i+h2)%m; //If the space is occupied 
	 }
  if ((*(hashArray +i))==inValue) //indicating that a duplicate has been inserted
  {
	for(k=0;k<e;k++)
	{
		if(!strcmp(ptrToStrings + k*26,array))
		{
			//Since a duplicate is found it would have already existed in array ptrToStrings
			//Hence return its index
			subscript =k;
			return subscript;
		}
		
	}
	
	
  }
  else {
    *(hashArray +i) =inValue;
	  for (k = 0; k < e; k++) 
	  { 
          //ARRAY ptrToStrings IS INITIALIZED WITH THE FIRST COLUMN OF EACH ROW CONTAINS '\0' INDICATING IT IS EMPTY
          if((*(ptrToStrings + k*26)) == '\0') 
		  {
			  //THIS IF CONDITION FINDS THE FIRST EMPTY ROW AND THEN STARTS FILLING IT
			  subscript = k;
			for(j=0;j<=strlength;j++)
            { 
			 *((ptrToStrings+k*26) + j) = *(array+j);
				
			}
			*((ptrToStrings+k*26) + strlength+1) = '\0'; //ADDING NULL TERMINATOR IN THE END 
            break;	 //	WHEN THE FIRST EMPTY CELL IS FOUND THEN BREAK;	
		  }
		  else
		  {
			  continue;





			  }
      }
    }
}
	
return subscript;
}

int finishIndex;

void DFSvisit(int u)
{
int i,v;

vertexStatus[u]=GRAY;

for (i=firstEdge[u];i<firstEdge[u+1];i++)
{
  v=edgeTab[i].head;
  if (vertexStatus[v]==WHITE)
    DFSvisit(v);
}
vertexStatus[u]=BLACK;
secondDFSrestarts[--finishIndex]=u;
}

void reverseEdges()
{
int a,b,i,j;
edgeType work;
edgeType *ptr;

for (i=0; i<e; i++)
{
  a=edgeTab[i].tail;
  b=edgeTab[i].head;
  edgeTab[i].tail=b;
  edgeTab[i].head=a;
}

// sort edges
qsort(edgeTab,e,sizeof(edgeType),tailThenHead);

// For each vertex as a tail, determine first in range of edgeTab entries
if (!firstEdge)
{
  printf("malloc failed %d\n",__LINE__);
  exit(0);
}
j=0;
for (i=0; i<n; i++)
{
  firstEdge[i]=j;
  for ( ;
       j<e && edgeTab[j].tail==i;
       j++)
    ;
}
firstEdge[n]=e;
}

void DFSvisit2(int u,char *ptrToStrings) //CHANGED DFSvisit2 so that it can print the strings instead of integers 
{
int i,v;

printf("%s\n",ptrToStrings+u*26); //Printing the strings instead of integers
vertexStatus[u]=GRAY;

for (i=firstEdge[u];i<firstEdge[u+1];i++)
{
  v=edgeTab[i].head;
  if (vertexStatus[v]==WHITE)
    DFSvisit2(v,(char *)ptrToStrings);
}
vertexStatus[u]=BLACK;
}

/*
********************************************************************************************************************************************************************
Function Name: getNextPrime
Input: int a
output: int ans
Processing: This function takes in an integer whose next prime is to be found WITH A LOAD FACTOR FOR LESS THAN 90% and returns the next prime
********************************************************************************************************************************************************************
*/
int getNextPrime(int a)
{
int i,j,flag=0;
double k; //Double k to hold 0.90
k=a;
int ans;
for(i=n+1;i<=n+100;i++)
   {
      flag=0;
      for(j=2;j<i;j++)
      {
         if(i%j==0) 
         {
            flag=1;
            break;
         }
      }
      if(flag==0) //Indicating prime is found
      {
         if((k/i) <  0.90) //Load factor
         {  
	     ans = i;
         break;
         }
         else
           {
            continue;
           }
      }
   }
	
	return ans;
}

int main()
{
system("clear");
int u,i,j,k,nextDFS;
int SCCcount=0;
scanf("%d %d",&n,&e); //Input n and e
hashTableSize = getNextPrime(n); //Get the next prime with loadfactor less than 0.90
printf("The size of hash Table is %d\n\n",hashTableSize);
int hashArray[hashTableSize];
char ptrToStrings[n][26]; //A 2D array to store the strings

//Initializing hashArray indicating it is empty
for (i=0;i<hashTableSize;i++)
   {
    hashArray [i] = -1;
   }
   
 totalCells = n*26;
 j=0;

 //INITIALIZING ARRAY ptrToStrings SO THAT EEVRY ROW'S FIRST COLUMN CONTAINS '\0' (TERMINATOR) INDICATING THAT THE ARRAY IS EMPTY
 for (i = 0; i < n; i++) {
      ptrToStrings[i][0]  = '\0';
  }
read_input_file(hashArray,(char *)ptrToStrings);
vertexStatus=(int*) malloc(n*sizeof(int));
secondDFSrestarts=(int*) malloc(n*sizeof(int));
if (!vertexStatus || !secondDFSrestarts)
{
  printf("malloc failed\n");
  exit(0);
}
// DFS code
for (u=0;u<n;u++)
  vertexStatus[u]=WHITE;
finishIndex=n;
for (u=0;u<n;u++)
  if (vertexStatus[u]==WHITE)
    DFSvisit(u);
reverseEdges();
// DFS code
for (u=0;u<n;u++)
  vertexStatus[u]=WHITE;
for (i=0;i<n;i++)
  if (vertexStatus[secondDFSrestarts[i]]==WHITE)
  {
    SCCcount++;
    printf("SCC %d\n",SCCcount);
    DFSvisit2(secondDFSrestarts[i],(char *)ptrToStrings);
  }
free(edgeTab);
free(firstEdge);
free(vertexStatus);
free(secondDFSrestarts);
return 0;
}



