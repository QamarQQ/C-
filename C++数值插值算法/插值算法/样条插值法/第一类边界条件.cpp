//��һ�ֱ߽��������������������˵㴦��һ�׵���ֵ
#include "stdio.h"
#include "stdlib.h"


double spl1(double x[], double y[],int n,double dy[],double ddy[],double t[],int m,
            double z[],double dz[],double ddz[]){
       int i,j;
       double h0,h1,alpha,beta,g; 
       double *s;
       s= (double*) malloc(n*sizeof(double));
//       �����㴦��һ�׵���ֵ
      s[0]=dy[0];
	  dy[0]=0.0;
	  h0=x[1]-x[0];
	  for(j=1;j<=n-2;j++){
	  	h1=x[j+1]-x[j];
	  	alpha=h0/(h0+h1);
	  	beta=(1.0-alpha)*(y[j]-y[j-1])/h0;
	  	beta=3.0*(beta+alpha*(y[j+1]-y[j])/h1);
	  	dy[j]=-alpha/(2.0+(1.0-alpha)*dy[j-1]);
	  	s[j]=(beta-(1.0-alpha)*s[j-1]);
	  	s[j]=s[j]/(2.0+(1.0-alpha)*dy[j-1]);
	  	h0=h1;
	  } 
	  
	  for(j=n-2;j>=0;j--){
	  	
	  	dy[j]=dy[j]*dy[j+1]+s[j];
   
	  }
// �����㴦�Ķ��׵���ֵ
    for(j=0;j<=n-2;j++) s[j]=x[j+1]-x[j];
    for(j=0;j<=n-2;j++){
    	h1=s[j]*s[j];
		ddy[j]=6.0*(y[j+1]-y[j])/h1-2.0*(2.0*dy[j]+dy[j+1])/s[j];
	}
    h1=s[n-2]*s[n-2];
    ddy[n-1]=6.0*(y[n-2]-y[n-1])/h1+2.0*(2.0*dy[n-1]+dy[n-2])/s[n-2];
//  �������ֵ

    g=0.0;
	
	for(i=0;i<=n-2;i++){
		h1=0.5*s[i]*(y[i]+y[i+1]);
		h1=h1-s[i]*s[i]*s[i]*(ddy[i]+ddy[i+1])/24.0;
		g=g+h1;
	} 
	
	for(j=0;j<=m-1;j++){
		if(t[j]>=x[n-1]) i=n-2;  //ȷ����ֵ���λ��
		else{
			i=0;
			while(t[j]>x[i+1])i=i+1;
		} 
		
// �����ֵ�㴦�ĺ���ֵ����ֵ��һ�ף����׵�������ֵ

   h1=(x[i+1]-t[j])/s[i];
   h0=h1*h1;
   z[j]=(3.0*h0-2.0*h0*h1)*y[i];
   z[j]=z[j]+s[i]*(h0-h0*h1)*dy[i];
   dz[j]=6.0*(h0-h1)*y[i]/s[i];
   dz[j]=dz[j]+(3.0*h0-2.0*h1)*dy[i];
   ddz[j]=(6.0-12.0*h1)*y[i]/(s[i]*s[i]);
   ddz[j]=ddz[j]+(2.0-6.0*h1)*dy[i]/s[i];
   h1=(t[j]-x[i])/s[i];
   h0=h1*h1;
   z[j]=z[j]+(3.0*h0-2.0*h0*h1)*y[i+1];
   z[j]=z[j]-s[i]*(h0-h0*h1)*dy[i+1];
   dz[j]=dz[j]-6.0*(h0-h1)*y[i+1]/s[i];
   dz[j]=dz[j]+(3.0*h0-2.0*h1)*dy[i+1];
   ddz[j]=ddz[j]+(6.0-12.0*h1)*y[i+1]/(s[i]*s[i]);
   ddz[j]=ddz[j]-(2.0-6.0*h1)*dy[i+1]/s[i];
		
	}
   free(s);
   return g;
} 

int main(int arg, int argv[]){
	int n,m,i;
	double s;
	static double dy[12],ddy[12],z[8],dz[8],ddz[8];
	static double x[12]={0.52,8.0,17.95,28.65,50.65,104.6,
	                    156.6,260.7,364.4,468.0,507.0,520.0};
	static double y[12]={5.28794,13.84,20.2,24.9,31.1,36.5,
	                     36.6,31.0,20.9,7.8,1.5,0.2};
    static double t[8]={4.0,14.0,30.0,60.0,130.0,230.0,
	                    450.0,515.0};
    dy[0]=1.86548;
    dy[11]=-0.046115;
    n=12;
    m=8;
    printf("\n");
    s=spl1(x,y,n,dy,ddy,t,m,z,dz,ddz);
    printf(
"	   x(i)                 y(i)              dy(i)                  ddy(i)\n");
	for(i=0;i<=11;i++) printf("%20.6e%20.6e%20.6e%20.6e\n",x[i],y[i],dy[i],ddy[i]);
    printf("\n");
    
    printf("        s=%e\n",s);
    printf("\n");
    printf(
"	   t(i)                 z(i)              dz(i)                  ddz(i)\n");
 	for(i=0;i<=7;i++) printf("%20.6e%20.6e%20.6e%20.6e\n",t[i],z[i],dz[i],ddz[i]);
 	printf("\n");
	  
	 
	
	
	
	
	
	return 0;
}

