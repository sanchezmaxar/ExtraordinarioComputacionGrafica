//prueba
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

void  producto(float* v1,float* v2 ){
    float x,y,z;

    x=v1[1]*v2[2]-v2[1]*v1[2];
    y=v1[0]*v2[2]-v2[0]*v1[2];
    z=v1[0]*v2[1]-v2[0]*v1[1];
	printf("(%.3f,%.3f,%.3f)\n",x,y,z );    
    // glNormal3f(x,y,z);
}

float* resta(float v10,float v11,float v12,float v20,float v21,float v22){
    float * sal;
    float n;
    sal=(float *)malloc(3*sizeof(float));
    n=((v20-v10)*(v20-v10))+((v21-v11)*(v21-v11))+((v22-v12)*(v22-v12));
    n=sqrt(n);
    sal[0]=(v20-v10)/n;
    sal[1]=(v21-v11)/n;
    sal[2]=(v22-v12)/n;
    return sal;
}


int main(){
	producto(resta(-1,1,0,-1,-1,0),resta(-1,-1,0,1,-1,0));
	producto(resta(0,1,1,0,-1,1),resta(0,-1,1,1,-1,0));
	return 0;
}