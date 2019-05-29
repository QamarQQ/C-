# include "stdio.h"

double ehmt(double x0,double h,int n, double y[],double dy[],double t){
	
	int i,j;
	double z,s,p,q;
	z=0.0;
	for(i=1;i<=n;i++){
		s=1.0;
		q=x0+(i-1)*h;
		for(j=1;j<=n;j++){
			p=x0+(j-1)*h;
			if(j!=i)s=s*(t-p)/(q-p); 
		}
	s=s*s;
	p=0.0;
	for(j=1;j<=n;j++){
		if(j!=i)p=p+1.0/(q-(x0+(j-1)*h));
	}
	q=y[i-1]+(t-q)*(dy[i-1]-2.0*y[i-1]*p);
	z=z+q*s;
	}
	return z;
}

int main(int arg, int argv[]){
	
	int i;
	double x0,h,t,z,dy[10];
	static double y[10]={0.904837,0.818731,0.740818,0.670320,0.606531,
	                     0.548812,0.496585,0.449329,0.406570,0.367879};
    for(i=0;i<=9;i++)dy[i]=-y[i];
    x0=0.1;
    h=0.1;
    t=0.752;
    z=ehmt(x0,h,10,y,dy,t);
    printf("t=%6.3f,z=%e\n",t,z);
	
	
	return 0;
}
