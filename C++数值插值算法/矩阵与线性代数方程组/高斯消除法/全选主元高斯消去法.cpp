# include "stdlib.h"
# include "math.h"
# include "stdio.h"
//  本函数返回整型标志值，若返回标志值为0，那么方程组的系数矩阵奇异，输出信息“Fail”,返回的标志值不为0，那么表示正常返回
 
int rgauss( double a[],int nn,double b[],int n){
	
	int *js,l,k,i,j,is,p,q;
	double d,t;
	
	js= (int*) malloc(n*sizeof(int));// 开辟用于记忆交换信息的动态空间
	l=1;                             //置非奇异标志
	
	 
	for(k=0;k<=n-2;k++){
		
		d=0.0;
		for(i=k;i<=n-1;i++){
		
		    for(j=k;j<=n-1;j++)         //全选主元 
		{ 
		   t=fabs(a[i*n+j]);
		   if(t>d){
		   	d=t;
		   	js[k]=j;                 //记忆行、列交换信息 
		   	is=i;
		   } 
		  
		
		}
	}
		
	  if(d+1.0 == 1.0) l=0; //置奇异标志；
	  
	  else{
	  	    if(js[k]!=k)
	  	      for(i=0;i<=n-1;i++){  //列交换 
	  	      	p=i*n+k; q=i*n+js[k];
				t=a[p];a[p]=a[q];a[q]=t; 
				}
				
			if(is!=k){
				for(j=k;j<=n-1;j++)  //行交换 
				{
				
				p=k*n+j;q=is*n+j;
				t=a[p];a[p]=a[q];a[q]=t; 
				
				} 
			t=b[k];b[k]=b[is];b[is]=t;
			}
	  } 
	  
	  if(l==0)  //         奇异返回 
	  {
	    free(js);
		printf("Fail\n");
		return 0; 
	  } 
	  
	 d=a[k*n+k];
	 for(j=k+1;j<=n-1;j++)   //归一化 
	  {
	  	p=k*n+j; a[p]=a[p]/d; 
	  } 
	  b[k]=b[k]/d;
	  for (i=k+1;i<=n-1;i++)// 消元
	  {
	   for(j=k+1;j<=n-1;j++)
	      {
	         p=i*n+j;
			 a[p]=a[p]-a[i*n+k]*a[k*n+j]; 
	   	
	      } 
		 b[i]=b[i]-a[i*n+k]*b[k];  	
	  } 
	}
	d=a[(n-1)*n+n-1];
	if(fabs(d)+1.0 == 1.0) //奇异返回
	{
		free(js);
		printf("Fail\n");
		return 0; 
	} 
	b[n-1]=b[n-1]/d;
	for(i=n-2;i>=0;i--)  //回代
	{
      t=0.0;
	  for(j=i+1;j<=n-1;j++)
	     t=t+a[i*n+j]*b[j];
	  b[i]=b[i]-t;	
	} 
	
	js[n-1]=n-1;
	for(k=n-1;k>=0;k--){  //恢复解向量 
		if(js[k]!=k){
			t=b[k];
			b[k]=b[js[k]];
			b[js[k]]=t;
		}
		
	}
	
	free(js);
	return 1; 	
} 


int main(int arg, int argv[]){
	
	int i;
	
	static double a[16]={
	0.2368,0.2471,0.2568,1.2671,
	0.1968,0.2071,1.2168,0.2271,
	0.1581,1.1675,0.1768,0.1871,
	1.1161,0.1254,0.1397,0.1490
	
	};
	
	static double b[4]={1.8471,1.7471,1.6471,1.5471};
	
	
	if(rgauss(a,16,b,4)!=0)
	   for(i=0;i<=3;i++){
	   	printf("x(%d)=%e\n",i,b[i]);
	   }
	
	
	return 0;
} 
