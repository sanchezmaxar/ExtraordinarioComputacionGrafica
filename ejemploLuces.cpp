#include <GL/gl.h>
#include <GL/glut.h>
// #include "figuras_max.cpp"
#include <math.h>
#define def 10
GLfloat angle = 0.0;
float ax=0;
float ay=0;
float az=0;


GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0}; //set the material to red
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0}; //set the material to white
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0}; //set the material to green
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set the light specular to white
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; //set the light ambient to black
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; //set the diffuse light to white
GLfloat blankMaterial[] = {0.0, 0.0, 0.0}; //set the diffuse light to white
GLfloat mShininess[] = {128}; //set the shininess of the material

GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
float a0=1;
float a1=1;
float a2=1;
float a3=0;


bool diffuse = false;
bool emissive = false;
bool specular = false;

void init (void) {
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

void cubo(float arista){
	//trasero
	float a=arista/2;
	glBegin(GL_QUADS);
    	//trasera
    	glNormal3f(0,0,-1);
    	glVertex3f(-a,-a,-a);
    	glVertex3f(-a,a,-a);
    	glVertex3f(a,a,-a);
    	glVertex3f(a,-a,-a);
    	//frontal
    	glNormal3f(0,0,1);
    	glVertex3f(-a,-a,a);
    	glVertex3f(-a,a,a);
    	glVertex3f(a,a,a);
    	glVertex3f(a,-a,a);
    	//superior
    	glNormal3f(0,1,0);
    	glVertex3f(-a,a,-a);
    	glVertex3f(a,a,-a);
    	glVertex3f(a,a,a);
    	glVertex3f(-a,a,a);
    	//Inferior
    	glNormal3f(0,-1,0);
    	glVertex3f(-a,-a,-a);
    	glVertex3f(a,-a,-a);
    	glVertex3f(a,-a,a);
    	glVertex3f(-a,-a,a);
    	//izquierdo
    	glNormal3f(-1,0,0);
    	glVertex3f(-a,-a,-a);
    	glVertex3f(-a,-a,a);
    	glVertex3f(-a,a,a);
    	glVertex3f(-a,a,-a);
    	//DERECHO
    	glNormal3f(1,0,0);
    	glVertex3f(a,-a,-a);
    	glVertex3f(a,-a,a);
    	glVertex3f(a,a,a);
    	glVertex3f(a,a,-a);
    glEnd();
}
void light (void) {
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
}

void display (void) {
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    light();
    glTranslatef(0,0,-5);
    light_position[0]= a0;
    light_position[1]= a1;
    light_position[2]= a2;
    light_position[3]= a3;
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    // glRotatef(angle,1,1,1);
    glPushMatrix();
    	glTranslatef(a0,a1,a2);
    	cubo(1);
    glPopMatrix();
    glPushMatrix();
	    glRotatef(ax,1,0,0);
	    glRotatef(ay,0,1,0);
	    glRotatef(az,0,0,1);
	    // glutSolidTeapot(2);
	    // cubo(0,0,0);
	    cubo(1);
    glPopMatrix();
    glutSwapBuffers();
    // angle ++;
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y) {
//     if (key=='z')
//     {
//         if (specular==false)
//         {
//             specular = true;
//             glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,
// whiteSpecularMaterial);
//             glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
//         }
//         else if (specular==true)
//         {
//             specular = false;
//             glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blankMaterial);
//             glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,
// blankMaterial);
//         }
//     }

//     if (key=='q')
//     {
//         if (diffuse==false)
//         {
//             diffuse = true;
//             glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
// redDiffuseMaterial);
//         }
//         else if (diffuse==true)
//         {
//             diffuse = false;
//             glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
//         }
//     }

//     if (key=='e')
//     {
//         if (emissive==false)
//         {
//             emissive = true;
//             glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,
// greenEmissiveMaterial);
//         }
//         else if (emissive==true)
//         {
//             emissive = false;
//             glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blankMaterial);
//         }
//     }
    if (key=='a')
    	ax+=def;
    if (key=='s')
    	ay+=def;
    if (key=='d')
    	az+=def;
    if (key=='A')
    	ax-=def;
    if (key=='S')
    	ay-=def;
    if (key=='D')
    	az-=def;
    if (key=='m')
    	a3+=0.2;
    if (key=='M')
    	a3-=0.2;
    if (key=='n')
    	a2+=0.2;
    if (key=='N')
    	a2-=0.2;
    if (key=='b')
    	a1+=0.2;
    if (key=='B')
    	a1-=0.2;
    if (key=='v')
    	a0+=0.2;
    if (key=='V')
    	a0-=0.2;
    if (key==27)
    	exit(0);
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init ();
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutKeyboardFunc (keyboard);
    glutReshapeFunc (reshape);
    glutMainLoop ();
    return 0;
}
