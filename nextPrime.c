#include<stdio.h>


int main(void)

{
int i,j,flag=0;
double k;
n =k;
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
      if(flag==0)
      {
         if((k/i) <  0.90)
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

return 0;
}


