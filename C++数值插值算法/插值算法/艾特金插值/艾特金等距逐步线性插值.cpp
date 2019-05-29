# include "math.h"
# include "stdio.h"
double eatk(double x0, double h, int n, double y[], double t, double eps){
	
	int i,j,k,m,l;
	double z, xx[10],yy[10];
	
	if(n<1) return(z);
	
	if(n==1){
		z=y[0];
		return (z);
	}
	m=10;
	
	if(m>n) m=n;
// 确定离插值点t最近的结点作为中心位置 
	if(t<=x0)k=1;
	else if (t >= x0+(n-1)*h)k=n;
	else{
		k=1;j=n;
		while((k-j!=1)&&(k-j!=-1)){
			
			l=(k+j)/2;
			if(t<x0+(l-1)*h)j=l;
			else k=l;
		}
		if(fabs(t-(x0+(l-1)*h))>fabs(t-(x0+(j-1)*h)))k=j;
	} 
	j=1;l=0;
	
// 分别从中心位置的前后取参加插值的结点
   for(i=1;i<=m;i++){
   	k=k+j*l;
   	if((k<1)||(k>n))
   	{
   		l=l+1;
   		j=-j;
   		k=k+j*l;
	   }
	xx[i-1]=x0+(k-1)*h;
	yy[i-1]=y[k-1];
	l=l+1;
	j=-j;	
   } 
   i=0;
// 进行艾特金逐步线性插值；
  do{
  	
  	i=i+1;
  	z=yy[i];
  	for(j=0;j<=i-1;j++){
  		z=yy[j]+(t-xx[j])*(yy[j]-z)/(xx[j]-xx[i]);
	  }
	yy[i]=z;
  } while((i!=m-1) && (fabs(yy[i]-yy[i-1])>eps));
  return z;
	
}


int main(int arg, int argv[]){
	
	double z,s,t,x0,h,eps;
	static double y[10]={0.904837,0.818731,0.740818,0.670320,0.606531,
	                    0.548812,0.496585,0.449329,0.406570,0.367879};
	eps=1.0e-6;x0=0.1;h=0.1;
	printf("\n");
	t=0.15;
	z=eatk(x0,h,10,y,t,eps);
	printf("t=%6.3f,z=%e\n",t,z);
	t=0.55;
	z=eatk(x0,h,10,y,t,eps);
	printf("t=%6.3f,z=%e\n",t,z);		
	
	return 0;
} 
