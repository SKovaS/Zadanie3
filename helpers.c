/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

 

bool search(int value, int values[], int n)
{
   int first=0;
   int last=n-1;
   while(first<=last){
       int middle=(first+last)/2;
       if(values[middle]==value)
       {
           return true;
       }
       if(values[middle]<value)
       {
           first=middle+1;
       }
       if(values[middle]>value)
       {
           last=middle-1;
       }
      
       
   }
   return false;
}
void sort(int values[], int n)
{
   for(int i=n;i>0;i--)
   {
       for(int j=0;j<i;j++)
       {
           if(values[j]>values[j+1])
           {
               int tmp=0;
               tmp=values[j+1];
               values[j+1]=values[j];
           }
       }
   }
    
    return;
}
