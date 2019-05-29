# include "math.h"
# include "stdio.h"
//在本函数中 ，程序自动从所有节点中选取离插值点t最近的10个结点进行逐步线性插值 
double natk(double x[], double y[],int n, double t, double eps){
	
	int i,j,k,m,l;
	
	double z,xx[10],yy[10];
	
	z=0.0;
	
	if(n<1) return z;
	
	if(n==1){
		z=y[0];
		return z;
	}
	
	m=10 ;//最多取10个结点；
	if(m>n) m=n;
//  确定离插值点t最近的结点作为中心位置
    if(t <= x[0]) k=1; 
	else if(t >= x[n-1]) k=n;
	else{
		
		k=1; j=n;
		while((k-j!=1) && (k-j!=-1)){
			l=(k+j)/2;
			if(t<x[l-1])j=l;
			else k=l;
		}
		if(fabs(t-x[l-1])>fabs(t-x[j-1]))k=j;
	} 
	
	j=1;l=0;
// 分别从中心位置的前后取值参加插值的结点
    for (i=1;i<=m;i++){
    	
    	k=k+j*l;
    	if((k<1) || (k>n)){
    		l=l+1;j=-j;k=k+j*l;
		}
		xx[i-1]=x[k-1];
		yy[i-1]=y[k-1];
		l=l+1;
		j=-j;
	} 
	i=0;
// 进行艾特金逐步线性插值

  do {
  	i=i+1;
  	z=yy[i];
  	for(j=0;j<=i-1;j++) z=yy[j]+(t-xx[j])*(yy[j]-z)/(xx[j]-xx[i]);
  	yy[i]=z;
  } while((i!=m-1)&&((fabs(yy[i]-yy[i-1]))>eps));
  return z;
} 


int main(int arg, int argv[]){
	
	
	double t,z,eps;
	static double x[11]={-1.0,-0.8,-0.65,-0.4,-0.3,0.0,0.2,0.4,0.6,0.8,1.0};
	static double y[11]={0.0384615,0.0588236,0.0864865,0.2,0.307692,1.0,0.5,0.2,0.1,0.0588236,0.0384615};
	eps=1.0e-6;
	printf("\n");
	t=-0.75;z=natk(x,y,11,t,eps);
	printf("t=%6.3f,z=%e\n",t,z);
    t=0.05;z=natk(x,y,11,t,eps);
	printf("t=%6.3f,z=%e\n",t,z);
	t=0.6;z=natk(x,y,11,t,eps);
	printf("t=%6.3f,z=%e\n",t,z);	
	
	return 0;
}
