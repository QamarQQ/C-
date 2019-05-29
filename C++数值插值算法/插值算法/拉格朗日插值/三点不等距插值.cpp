#include "math.h"
#include"stdio.h"
double nlg3(double x[],double y[],int n,double t){

    int i,j,k,m;
    
    double z,s;
    z=0.0;
    if(n<1) return(z);/*  节点个数不对，返回*/
    
    
    if(n==1) {
    	z=y[0];
    	return(z);/*只有一个节点，取值返回*/	
	} 
	
	if(n==2){
		z=(y[0]*(t-x[1])-y[1]*(t-x[0]))/(x[0]-x[1]);
		return(z);
	} 
	
	if(t<=x[1]){
		k=0;
		m=2;/*取最前的三个节点*/
	}
	else if(t>=x[n-2]){
		k=n-3;
		m=n-1;/*取最后三个节点*/
	} 
	
   else{
   	
   	k=1;
   	m=n;
   	
   	while(m-k!=1){
   		i=(k+m)/2;
   		if(t<x[i-1])m=i;
   		else k=i;
   		
	   }
	   k=k-1;
	   m=m-1;
	   if(fabs(t-x[k])<fabs(t-x[m]))k=k-1;
	   else m=m+1;   
   } 
   
   z=0.0;
   for(i=k;i<=m;i++) /*进行三点二次插值*/
   {
       s=1.0;
	   for(j=k;j<=m;j++)
	   	if(j!=i)s=s*(t-x[j])/(x[i]-x[j]);
	   	z=z+s*y[i];
	    
   } 
   return(z);
      
}

int main(){
	double t,z;
	static double x[5]={1.615,1.634,1.702,1.828,1.921};
	static double y[5]={2.41450,2.46459,2.65271,3.03035,3.34066};
    printf("\n");
	t=1.682;
	z=nlg3(x,y,5,t);
	printf("x=%6.3f,f(x)=%e\n",t,z);
	t=1.813;
	z=nlg3(x,y,5,t);
	printf("x=%6.3f,f(x)=%e\n",t,z);
	printf("\n");		
}
