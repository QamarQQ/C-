#include<stdio.h> 
int main() 
{ 
    float x[20],fx[20][20],xvalue,h,p,temp,ans; 
    int n,i,j,fact; 
    printf("\n Enter the value of x to find f(x)..."); 
    scanf("%f",&xvalue); 
    printf("\n Enter the number of observation you want to insert..."); 
    scanf("%d",&n); 

//Input observation table 
    for(i=0;i<n;i++) 
    { 
      printf("\n Enter the value of x..."); 
      scanf("%f",&x[i]); 
      printf("\n Enter the value of f(x)..."); 
      scanf("%f",&fx[i][0]); 
} 

//Calculate the value of p 
      h=x[1]-x[0]; 
      p=(xvalue-x[0])/h; 

//Calculate the value of ?xi , ?2xi , ?3xi , . . . (where i = 1, 2, 3, . . . ) 
    for(i=1;i<n;i++) 
    { 
      for(j=0;j<n-i;j++) 
      { 
         fx[j][i]=fx[j+1][i-1]-fx[j][i-1]; 
      } 
    } 

//Print the value of ?xi , ?2xi , ?3xi , . . . table 
     for(i=0;i<n;i++) 
     { 
      printf("\n"); 
      for(j=0;j<n-i;j++) 
      { 
         printf("%f ",fx[i][j]); 
     } 
     }    

//Find f(x) using Newton's Forward Interpolation Method 
     ans=fx[0][0]; 
     for(i=1;i<n;i++) 
   { 

//Calculate p , p(p - 1) , p(p - 1)(p - 2) , . . . 
    temp=p; 
    for(j=1;j<i;j++) 
    { 
      temp=temp*(p-j); 
    }   

//Factorial calculation 
    fact=1; 
    for(j=1;j<=i;j++) 
    { 
       fact=fact*j; 
    } 
      ans=ans+((temp/fact)*fx[0][i]); 
    } 
     printf("\n f(x) = %f",ans); 
    return 0;
    }
