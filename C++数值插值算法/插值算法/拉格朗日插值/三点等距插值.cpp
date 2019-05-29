//  本函数采用抛物线插值，程序自动从所有结点中选取离插值点t最近的三个结点进行插值

# include "math.h"
# include "stdio.h"


double elg3(double x0,double h, int n, double y[], double t){
	
	int i,j,k,m;
	double z,s,xi,xj;
	z=0.0;
	if(n<1) return(z); /* 结点个数不对，返回*/
	if(n==1){
		z=y[0];
		return (z);
	} 
	if(n==2){
		z=(y[1]*(t-x0)-y[0]*(t-x0-h))/h;
		return (z);
	}
	if(t <= x0+h){
		k=0; m=2; /* 取最前的三个结点*/
	}
	else if(t>x0+(n-3)*h){
		k=n-3;m=n-1; /*取最后的三个结点*/ 
	} 
	else { /*取中间的三个结点*/
	
	i= (int)((t-x0)/h)+1;
	if(fabs(t-x0-i*h)>= fabs(t-x0-(i-1)*h)){
		k=i-2;
		m=i;
	}
	else{
		k=i-1;
		m=m+1;
	}
   }
// 进行二次插值 
    z=0.0;
	for(i=k;i<=m;i++){
		
		s=1.0;
		xi=x0+i*h;
		for(j=k;j<=m;j++){
			if(j!=i){
				xj=x0+j*h;
				s=s*(t-xj)/(xi-xj);
			}
		}
	z= z+s*y[i];
	}		
		
	 
	return (z);
} 

int main(int arg,int argv[]){
	double t,z,x0,h;
	
	static double y[10]={0.904837,0.818731,0.740818,0.670320,0.606531,
	0.548812,0.496585,0.449329,0.406570,0.367879};
	
	x0=0.1;
	h=0.1;
	printf("\n");
	t=0.23;
	z=elg3(x0,h,10,y,t);
	printf("t=%6.3f, z=%e\n",t,z);
	t=0.63;
	z=elg3(x0,h,10,y,t);
	printf("t=%6.3f, z=%e\n",t,z);
	t=0.95;
	z=elg3(x0,h,10,y,t);
	printf("t=%6.3f, z=%e\n",t,z);
	
	
	
	return 0;
}
