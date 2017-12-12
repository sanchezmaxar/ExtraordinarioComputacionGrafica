#include <math.h>
const double PI = 3.1415926535897;
void light (void) {
    GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0}; //set the material to white
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0}; //set the material to green
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set the light specular to white
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; //set the light ambient to black
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; //set the diffuse light to white
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
}

void  producto(float* v1,float* v2 ){
    float x,y,z;

    x=v1[1]*v2[2]-v2[1]*v1[2];
    y=v1[0]*v2[2]-v2[0]*v1[2];
    z=v1[0]*v2[1]-v2[0]*v1[1];
    glNormal3f(x,y,z);
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

void ficha(GLuint textura){
    int resolucion=20;
    float radio=2,alto=0.5,theta=2*PI/resolucion;
    float auxx1,auxy1,auxz1;
    float auxx2,auxy2,auxz2;
    // glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, textura);
    for (int i=0;i<resolucion;i++){
        auxx1=cos(i*theta);
        auxz1=sin(i*theta);
        auxx2=cos((i+1)*theta);
        auxz2=sin((i+1)*theta);
        glPushMatrix();
            glTranslatef(0,alto/2,0);
            glBegin(GL_TRIANGLES);
                producto(resta(0,0,0,radio*auxx1,0,radio*auxz1),resta(radio*auxx1,0,radio*auxz1,radio*auxx2,0,radio*auxz2));
                glTexCoord2f(0.5,0.5); glVertex3f(0,0,0);
                glTexCoord2f(auxx1/2+0.5,0.5+auxz1/2); glVertex3f(radio*auxx1,0,radio*auxz1);
                glTexCoord2f(auxx2/2+0.5,auxz2/2+0.5); glVertex3f(radio*auxx2,0,radio*auxz2);
            glEnd();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-alto/2,0);
            glBegin(GL_TRIANGLES);
                producto(resta(0,0,0,radio*auxx1,0,radio*auxz1),resta(radio*auxx1,0,radio*auxz1,radio*auxx2,0,radio*auxz2));
                glTexCoord2f(0.5,0.5); glVertex3f(0,0,0);
                glTexCoord2f(auxx1/2+0.5,0.5+auxz1/2); glVertex3f(radio*auxx1,0,radio*auxz1);
                glTexCoord2f(auxx2/2+0.5,auxz2/2+0.5); glVertex3f(radio*auxx2,0,radio*auxz2);
            glEnd();
        glPopMatrix();
        glBegin(GL_POLYGON);
            producto(resta(radio*auxx1,alto/2,radio*auxz1,radio*auxx1,-alto/2,radio*auxz1),resta(radio*auxx1,-alto/2,radio*auxz1,radio*auxx2,-alto/2,radio*auxz2));
            glTexCoord2f(auxx1,1); glVertex3f(radio*auxx1,alto/2,radio*auxz1);
            glTexCoord2f(auxx1,0); glVertex3f(radio*auxx1,-alto/2,radio*auxz1);
            glTexCoord2f(auxx2,0); glVertex3f(radio*auxx2,-alto/2,radio*auxz2);
            glTexCoord2f(auxx2,1); glVertex3f(radio*auxx2,alto/2,radio*auxz2);
        glEnd();

    }
    // glEnable(GL_LIGHTING);
}


void paredMadera(float x,float y,float z,float veces,GLuint textura){
    // esta funcion crea una pared con una textura en todas las caras
    float largo=x/2;
    float alto=y/2;
    float ancho=z/2;

    // glDisable(GL_LIGHTING);
	glPushMatrix();
		//pared interna
		glBindTexture(GL_TEXTURE_2D, textura);
		glBegin(GL_POLYGON);
            //pared frontal
            producto(resta(-largo , -alto , ancho,largo , -alto , ancho),resta(largo , -alto , ancho,largo , alto , ancho));
			glTexCoord2f(0, 0);	glVertex3f(-largo , -alto , ancho );
			glTexCoord2f(0, 1*largo*veces); glVertex3f(largo , -alto , ancho );
			glTexCoord2f(1 * alto * veces, 1 * largo * veces); glVertex3f(largo , alto , ancho );
			glTexCoord2f(1 * alto * veces, 0); glVertex3f(-largo , alto , ancho );
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textura);
		glBegin(GL_POLYGON);
            //pared trasera
            producto(resta(-largo ,-alto , -ancho,largo , -alto , -ancho),resta(largo , -alto , -ancho,largo , alto , -ancho));
			glTexCoord2f(0, 0);	glVertex3f(-largo ,-alto , -ancho );
			glTexCoord2f(0, 1 * largo * veces); glVertex3f(largo , -alto , -ancho );
			glTexCoord2f(1*alto*veces, 1 * largo * veces); glVertex3f(largo , alto , -ancho );
			glTexCoord2f(1 * alto * veces, 0); glVertex3f(-largo , alto , -ancho );
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textura);
		glBegin(GL_POLYGON);
    		// glNormal3f(-1, 0, 0);
            //pared izquierda
            producto(resta(-largo , -alto , -ancho,-largo , -alto , ancho),resta(-largo , -alto , ancho,-largo , alto , ancho));
    		glTexCoord2f(0, 0); glVertex3f(-largo , -alto , -ancho );
    		glTexCoord2f(0, 1 * largo * veces);	glVertex3f(-largo , -alto , ancho );
    		glTexCoord2f(1 * alto*veces, 1 * largo * veces);	glVertex3f(-largo , alto , ancho );
    		glTexCoord2f(1 * alto * veces, 0);	glVertex3f(-largo , alto , -ancho );
		glEnd();
		glBegin(GL_POLYGON);
		// glNormal3f(-1, 0, 0);
            //pared derecha
            producto(resta(largo , -alto , -ancho,largo , -alto , ancho),resta(largo , -alto , ancho,largo , alto , ancho));
			glTexCoord2f(0, 0); glVertex3f(largo , -alto , -ancho );
			glTexCoord2f(0, 1 * largo * veces); glVertex3f(largo , -alto , ancho );
			glTexCoord2f(1 * alto*veces, 1 * largo * veces); glVertex3f(largo , alto , ancho );
			glTexCoord2f(1 * alto * veces, 0); glVertex3f(largo , alto , -ancho );
		glEnd();
		glBegin(GL_POLYGON);
            // glNormal3f(0,1,0);
            //pared superior
            producto(resta(-largo , alto , ancho,largo , alto , ancho),resta(-largo , alto , ancho,largo , alto , ancho));
			glTexCoord2f(0,0); glVertex3f(-largo , alto , -ancho );
			glTexCoord2f(0, 1 * largo * veces); glVertex3f(-largo , alto , ancho );
			glTexCoord2f(1 * alto*veces, 1 * largo * veces); glVertex3f(largo , alto , ancho );
			glTexCoord2f(1 * alto * veces, 0); glVertex3f(largo , alto , -ancho );
		glEnd();
		glBegin(GL_POLYGON);
            // glNormal3f(0,1,0);
            producto(resta(-largo , -alto , -ancho,-largo , -alto , ancho),resta(-largo , -alto , ancho,largo , -alto , ancho));
			glTexCoord2f(0,0); glVertex3f(-largo , -alto , -ancho );
			glTexCoord2f(0, 1 * largo * veces); glVertex3f(-largo , -alto , ancho );
			glTexCoord2f(1 * alto*veces, 1 * largo * veces); glVertex3f(largo , -alto , ancho );
			glTexCoord2f(1 * alto * veces, 0); glVertex3f(largo , -alto , -ancho );
		glEnd();
	glPopMatrix();
	// glEnable(GL_LIGHTING);
}

void plano(float x,float z, GLuint textura){
    float largo=x/2;
    float ancho=z/2;
    // glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, textura);
    glBegin(GL_POLYGON);
        producto(resta(-largo , 0 , -ancho ,largo , 0 , -ancho),resta(largo , 0 , -ancho,largo , 0 , ancho));
        glTexCoord2f(0, 0);	glVertex3f(-largo , 0 , -ancho );
        glTexCoord2f(0, 1); glVertex3f(largo , 0 , -ancho );
        glTexCoord2f(1 ,1); glVertex3f(largo , 0 , ancho );
        glTexCoord2f(1 ,0); glVertex3f(-largo , 0, ancho );
    glEnd();
    // glEnable(GL_LIGHTING);
}

void bisagra1(float x,float z, GLuint textura){
    float largo=x/2;
    float ancho=z/2;
    // glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, textura);
    glBegin(GL_POLYGON);
        producto(resta(-largo , 0 , -ancho,largo , 0 , -ancho),resta(largo , 0 , -ancho,largo , 0 , ancho));
        glTexCoord2f(0, 1);	glVertex3f(-largo , 0 , -ancho );
        glTexCoord2f(0,0 ); glVertex3f(largo , 0 , -ancho );
        glTexCoord2f(0.4 ,0); glVertex3f(largo , 0 , ancho );
        glTexCoord2f(0.4 ,1); glVertex3f(-largo , 0, ancho );
    glEnd();
    // glEnable(GL_LIGHTING);
}


void triangulo(float base,float altura,GLuint textura,int tipo){
    //se esta en la base
    float aumento;
    // glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, textura);
    if (tipo==1)
        aumento=0;
    else
        aumento=0.5;
    glBegin(GL_TRIANGLES);
        producto(resta(0,0,0,0 , 0 , base),resta(0 , 0 , base,altura , 0 , base/2));
        glTexCoord2f(0+aumento, 0);	glVertex3f(0, 0 , 0 );
        glTexCoord2f(0.5+aumento, 0); glVertex3f(0 , 0 , base);
        glTexCoord2f(0.25+aumento ,1); glVertex3f(altura , 0 , base/2 );
    glEnd();
    // glEnable(GL_LIGHTING);
}

void tablero(GLuint madera,GLuint tapete,GLuint triangulos,int posiciones[24][5],int limite,GLuint textBlancas,GLuint textNegras){
    //en x--46 en z -- 26 en y -- 2
    glPushMatrix();
        paredMadera(46,1,26,0.1,madera);
        glPushMatrix();
            glTranslatef(-22.5,1,0);
            paredMadera(1,1,26,0.1,madera);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(22.5,1,0);
            paredMadera(1,1,26,0.1,madera);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,1,12.5);
            paredMadera(44,1,1,0.1,madera);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,1,-12.5);
            paredMadera(44,1,1,0.1,madera);
        glPopMatrix();
        //ponemos el tapete
        glTranslatef(0,1.01,0);
        plano(44,24,tapete);
        glPushMatrix();
            glTranslatef(-22,0.01,-12);
            for (int i =0, cond=-1; i<6;i++,cond*=-1){
                triangulo(4,20,triangulos,cond);
                glTranslatef(0,0,4);
            }
        glPopMatrix();
        glPushMatrix();
            glRotatef(180,0,1,0);
            glTranslatef(-22,0.01,-12);
            for (int i =0,cond=-1; i<6;i++,cond*=-1){
                triangulo(4,20,triangulos,cond);
                glTranslatef(0,0,4);
            }
        glPopMatrix();
    glPopMatrix();
    // aqui se incluyen las fichas de tablero
    glPushMatrix();
        glTranslatef(-22,1.27,-12);
        glTranslatef(2,0,2);
        for (int i=limite-12,signo=1;i<limite;i++){
            if (i==6 or i==18){
                glPopMatrix();
                glPushMatrix();
                glTranslatef(22,1.27,-12);
                glTranslatef(-2,0,2);
                signo=-1;
            }
            glPushMatrix();
            for (int j=0;j<5;j++){
                if (posiciones[i][j]==1)
                    ficha(textBlancas);
                else if (posiciones[i][j]==2)
                    ficha(textNegras);
                glTranslatef(4*signo,0,0);
            }
            glPopMatrix();
            glTranslatef(0,0,4);
        }
    glPopMatrix();
}

void cilindroBisagra(int resolucion,float radio,float alto,GLuint oro,GLuint bisagraT){
    float theta=2*PI/resolucion;
    // glDisable(GL_LIGHTING);
    for (int i=0;i<resolucion;i++){
        glPushMatrix();
            glTranslatef(0,alto/2,0);
            glBindTexture(GL_TEXTURE_2D, oro);
            glBegin(GL_TRIANGLES);
                producto(resta(0,0,0,radio*cos(i*theta),0,radio*sin(i*theta)),resta(radio*cos(i*theta),0,radio*sin(i*theta),radio*cos((i+1)*theta),0,radio*sin((i+1)*theta)));
                glTexCoord2f(0.5,0.5); glVertex3f(0,0,0);
                glTexCoord2f(cos(i*theta)/2+0.5,0.5+sin(i*theta)/2); glVertex3f(radio*cos(i*theta),0,radio*sin(i*theta));
                glTexCoord2f(cos((i+1)*theta)/2+0.5,sin((i+1)*theta)/2+0.5); glVertex3f(radio*cos((i+1)*theta),0,radio*sin((i+1)*theta));
            glEnd();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,-alto/2,0);
            glBindTexture(GL_TEXTURE_2D, oro);
            glBegin(GL_TRIANGLES);
                producto(resta(0,0,0,radio*cos(i*theta),0,radio*sin(i*theta)),resta(radio*cos(i*theta),0,radio*sin(i*theta),radio*cos((i+1)*theta),0,radio*sin((i+1)*theta)));
                glTexCoord2f(0.5,0.5); glVertex3f(0,0,0);
                glTexCoord2f(cos(i*theta)/2+0.5,0.5+sin(i*theta)/2); glVertex3f(radio*cos(i*theta),0,radio*sin(i*theta));
                glTexCoord2f(cos((i+1)*theta)/2+0.5,sin((i+1)*theta)/2+0.5); glVertex3f(radio*cos((i+1)*theta),0,radio*sin((i+1)*theta));
            glEnd();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, bisagraT);
        glBegin(GL_POLYGON);
            producto(resta(radio*cos(i*theta),alto/2,radio*sin(i*theta),radio*cos(i*theta),-alto/2,radio*sin(i*theta)),resta(radio*cos(i*theta),-alto/2,radio*sin(i*theta),radio*cos((i+1)*theta),-alto/2,radio*sin((i+1)*theta)));
            glTexCoord2f(0.155*cos(i*theta)+0.425,1); glVertex3f(radio*cos(i*theta),alto/2,radio*sin(i*theta));
            glTexCoord2f(0.155*cos(i*theta)+0.425,0); glVertex3f(radio*cos(i*theta),-alto/2,radio*sin(i*theta));
            glTexCoord2f(0.155*cos((i+1)*theta)+0.425,0); glVertex3f(radio*cos((i+1)*theta),-alto/2,radio*sin((i+1)*theta));
            glTexCoord2f(0.155*cos((i+1)*theta)+0.425,1); glVertex3f(radio*cos((i+1)*theta),alto/2,radio*sin((i+1)*theta));
        glEnd();

    }
    // glEnable(GL_LIGHTING);
}

void tableroCompleto(float anguloActual,GLuint bisagra,GLuint tapete,GLuint oro,GLuint triangulos,GLuint madera,int posiciones[24][5],GLuint textBlancas,GLuint textNegras){
    tablero(madera,tapete,triangulos,posiciones,24,textBlancas,textNegras);
    // aqui ponemos las bisagras
    glPushMatrix();
        glPushMatrix();
            glPushMatrix();
                glTranslatef(10.5,0.5,-13.01);
                glRotatef(-90,1,0,0);
                bisagra1(5,2,bisagra);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-10.5,0.5,-13.01);
                glRotatef(-90,1,0,0);
                bisagra1(5,2,bisagra);
            glPopMatrix();
        glPopMatrix();
        glTranslatef(0,1.5,-13.25);
        glRotatef(anguloActual,1,0,0);
        glTranslatef(0,-1.5,-13.25);
        tablero(madera,tapete,triangulos,posiciones,12,textBlancas,textNegras);
        glPushMatrix();
            glTranslatef(10.5,0.5,13.01);
            glPushMatrix();
                glRotatef(-90,1,0,0);
                bisagra1(5,2,bisagra);
            glPopMatrix();
            glTranslatef(0,1,0.25);
            glRotatef(90,0,0,1);
            cilindroBisagra(20,0.25,5,oro,bisagra);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-10.5,0.5,13.01);
            glPushMatrix();
                glRotatef(-90,1,0,0);
                bisagra1(5,2,bisagra);
            glPopMatrix();
            glTranslatef(0,1,0.25);
            glRotatef(90,0,0,1);
            cilindroBisagra(20,0.25,5,oro,bisagra);
        glPopMatrix();
    glPopMatrix();

}

void cubo(GLuint textura,float x, float z){
    float a=1; //arista
    //rotacion aleatoria en x y en z
    glPushMatrix();
        glRotatef(x,1,0,0);
        glRotatef(z,0,0,1);
        glBindTexture(GL_TEXTURE_2D, textura);
        glBegin(GL_POLYGON);
                //cara trasera con 2
                // glNormal3f(0,0,-1);
                producto(resta(-a,-a,-a,-a,a,-a),resta(-a,a,-a,a,a,-a));
                glTexCoord2f(0.33,0.5); glVertex3f(-a,-a,-a);
                glTexCoord2f(0.66,0.5); glVertex3f(-a,a,-a);
                glTexCoord2f(0.66,1); glVertex3f(a,a,-a);
                glTexCoord2f(0.33,1); glVertex3f(a,-a,-a);
        glEnd();
        glBegin(GL_POLYGON);
                //cara frontral con 5
                // glNormal3f(0,0,1);
                producto(resta(-a,-a,a,-a,a,a),resta(-a,a,a,a,a,a));
                glTexCoord2f(0.33,0); glVertex3f(-a,-a,a);
                glTexCoord2f(0.33,0.5); glVertex3f(-a,a,a);
                glTexCoord2f(0.66,0.5); glVertex3f(a,a,a);
                glTexCoord2f(0.66,0); glVertex3f(a,-a,a);
            glEnd();
            glBegin(GL_POLYGON);
                //cada inferior con 4
                // glNormal3f(0,-1,0);
                producto(resta(-a,-a,-a,a,-a,-a),resta(a,-a,-a,a,-a,a));
                glTexCoord2f(0,0); glVertex3f(-a,-a,-a);
                glTexCoord2f(0,0.5); glVertex3f(a,-a,-a);
                glTexCoord2f(0.33,0.5); glVertex3f(a,-a,a);
                glTexCoord2f(0.33,0); glVertex3f(-a,-a,a);
            glEnd();
            glBegin(GL_POLYGON);
                //cara superior con 3
                // glNormal3f(0,1,0);
                producto(resta(-a,a,-a,a,a,-a),resta(a,a,-a,a,a,a));
                glTexCoord2f(0.66,0.5); glVertex3f(-a,a,-a);
                glTexCoord2f(0.66,1); glVertex3f(a,a,-a);
                glTexCoord2f(1,1); glVertex3f(a,a,a);
                glTexCoord2f(1,0.5); glVertex3f(-a,a,a);
            glEnd();
            glBegin(GL_POLYGON);
                //cara izquierda con 1
                // glNormal3f(-1,0,0);
                producto(resta(-a,-a,-a,-a,-a,a),resta(-a,-a,a,-a,a,a));
                glTexCoord2f(0,0.5);  glVertex3f(-a,-a,-a);
                glTexCoord2f(0,1);    glVertex3f(-a,-a,a);
                glTexCoord2f(0.33,1);      glVertex3f(-a,a,a);
                glTexCoord2f(0.33,0.5);    glVertex3f(-a,a,-a);
            glEnd();
            glBegin(GL_POLYGON);
                //cara izquierda con 6
                // glNormal3f(1,0,0);
                producto(resta(a,-a,-a,a,-a,a),resta(a,-a,-a,a,a,a));
                glTexCoord2f(0.66,0);     glVertex3f(a,-a,-a);
                glTexCoord2f(0.66,0.5);       glVertex3f(a,-a,a);
                glTexCoord2f(1,0.5);      glVertex3f(a,a,a);
                glTexCoord2f(1,0);    glVertex3f(a,a,-a);
        glEnd();
    glPopMatrix();
    // glEnable(GL_LIGHTI   NG);
}
