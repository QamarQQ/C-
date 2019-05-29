# include "math.h"
# include "stdio.h"

double elgr(double x0, double h, int n, double y[], double t){
	
	
	
	int i,j,k,m;
	double z,s,xi,xj;
	
	float p,q;
	
	z=0.0;
	
	if(n<1) return(z);
	
	if(n==1){
		z=y[0];
		return (z);
	}
	if(n==2){
		z=(y[1]*(t-x0)-y[0]*(t-x0-h))/h;
		return (z);
	}
	if(t>x0)/*确定插值点的位置*/
	{
   	   p= (t-x0)/h;
       i= (int)p;
       q=(float)i;
       if(p>q)i=i+1;
    } 
    else i=0;
    
    k=i-4; /*确定第一个结点的位置*/
    if(k<0) k=0;
	m=i+3;// 确定最后一个结点的位置
	if(m>n-1) m=n-1;
	
	// 进行插值计算
	for(i=k;i<=m;i++){
		
		s=1.0;
		xi=x0+i*h;
		for(j=k;j<=m;j++){
			if(j!=i){
				xj=x0+j*h;
				s=s*(t-xj)/(xi-xj);
			}
		}
	z=z+s*y[i];
	} 
	return (z);
} 


int main(int arg, int argv[]){
	
	double x0, h,t,z;
	static double y[10]={0.904837,0.818731,0.740818,0.670320,0.606531,
	                      0.548812,0.496585,0.449329,0.406570,0.367879};
	x0=0.1;h=0.1; 
	t=0.25; z=elgr(x0,h,10,y,t);
	printf("t=%6.3f,z=%e\n",t,z);
	t=0.63; z=elgr(x0,h,10,y,t);
	printf("t=%6.3f,z=%e\n",t,z);
	t=0.95; z=elgr(x0,h,10,y,t);
	printf("t=%6.3f,z=%e\n",t,z);	
	return 0;
}
