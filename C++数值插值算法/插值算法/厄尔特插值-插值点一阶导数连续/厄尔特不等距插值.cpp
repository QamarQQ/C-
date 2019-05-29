# include "stdio.h"

double nhmt(double x[],double y[], double dy[], int n, double t){
	
	int i,j;
	double z,p,q,s;
	z=0.0;
	for(i=1;i<=n;i++){
		s=1.0;
		for(j=1;j<=n;j++){
			if(j!=i) s=s*(t-x[j-1])/(x[i-1]-x[j-1]); 
		}
		s=s*s;
		p=0.0;
		for(j=1;j<=n;j++){
			if(j!=i)p=p+1.0/(x[i-1]-x[j-1]);
		}
		q=y[i-1]+(t-x[i-1])*(dy[i-1]-2.0*y[i-1]*p);
		z=z+q*s;
	}
	return z;
}


int main(int arg, int argv[]){
	int i;
	double t,z,dy[10];
	
	static double x[10]={0.1,0.15,0.3,0.45,0.55,0.6,0.7,0.85,0.9,1.0};
	static double y[10]={0.904837,0.860708,0.740818,0.637628,0.576950,
	                     0.548812,0.496585,0.427415,0.406570,0.367879};
    for(i=0;i<=9;i++) dy[i]=-y[i];
	t=0.356;
	z=nhmt(x,y,dy,10,t);
	printf("t=%6.3f,z=%e\n",t,z);	
	
	return 0;
}
