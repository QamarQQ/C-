#include "stdio.h"

//��������֪��x��ֵ 
// ��������,�����Զ������нڵ���ѡȡ�����ֵ��t�����8�������в�ֵ 

double nlgr(double x[],double y[],int n, double t) {


      int i,j,k,m;
	  double z,s;
	  z=0.0;
	  if(n<1) return(z);
	  if(n==1){
	  	z=y[0];
	  	return (z);
	  } 
	  if(n==2){
	  	
	  	z=(y[0]*(t-x[1])-y[1]*(t-x[0]))/(x[0]-x[1]);
	  	return(z);
	  }
      i=0;
      while((x[i]<t) && (i<n)) i=i+1; /*ȷ����ֵ���λ��*/
      k=i-4 ;    /*ȷ����һ������λ��*/
      if(k<0) k=0;
	  m=i+3;   /*ȷ�����һ������λ��*/
	  if(m>n-1) m=n-1;
	  
	  for(i=k;i<=m;i++){   /*���в�ֵ����*/
	     
	     s=1.0;
		 for(j=k;j<=m;j++)
		 	if(j!=i)s=s*(t-x[j])/(x[i]-x[j]);
		z=z+s*y[i];
		  
	  
	  } 
	   
	return (z);

} 

int main(){
	double t,z;
	static double x[10]={0.10,0.15,0.25,0.40,0.50,
	                    0.57,0.70,0.85,0.93,1.0};
	static double y[10]={0.904837,0.860708,0.778801,0.670320,0.606531,
	                     0.565525,0.496585,0.427415,0.394554,0.367879};	                    
    t=0.63;z=nlgr(x,y,10,t);
	printf("\n");
	printf("t=%6.3f,  z=%e\n",t,z);	
	printf("\n");
	return 0;
} 
