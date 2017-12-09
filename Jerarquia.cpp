
 // g++ Jerarquia.cpp Camera.cpp texture.cpp figuras.cpp -lGL -lglut -lGLU -w
#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "figuras_max.cpp"

#define MAX_FRAMES 20

CFiguras mifigura;

int w = 500, h = 500;
int frame=0,time,timebase=0;
int deltaTime = 0;


CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW)

GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

//texturas
CTexture madera;
CTexture cielo;
CTexture tapete;
CTexture triangulos;
CTexture bisagra;
CTexture oro;
CTexture azul;
CTexture naranja;
//variables de animacion
bool play=false;
bool cerrar=false;
bool abrir=false;
typedef struct _frame {
	float angulo;
} FRAME ;
FRAME keyFrame [MAX_FRAMES];
float anguloActual=180;
//variales para las FICHAS
int posiciones[24][5]={
{1,1,1,1,1}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{2,2,2,0,0}
,{0,0,0,0,0}
//el otro lado tablero 1
,{2,2,2,2,2}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{1,1,1,0,0}
,{0,0,0,0,0}
//tablero 2
,{2,2,2,2,2}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{1,1,0,0,0}
//lado 2 tablero 2
,{1,1,1,1,1}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{2,2,0,0,0}};

//figuras
CFiguras sky;
//variables de animacion
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable ( GL_COLOR_MATERIAL );

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

    cielo.LoadBMP("texturas/cielo.bmp");
	cielo.BuildGLTexture();
	cielo.ReleaseImage();

	madera.LoadTGA("texturas/madera.tga");
	madera.BuildGLTexture();
	madera.ReleaseImage();

	tapete.LoadTGA("texturas/tapete.tga");
	tapete.BuildGLTexture();
	tapete.ReleaseImage();

	triangulos.LoadTGA("texturas/triangulos.tga");
	triangulos.BuildGLTexture();
	triangulos.ReleaseImage();

	bisagra.LoadTGA("texturas/bisagra.tga");
	bisagra.BuildGLTexture();
	bisagra.ReleaseImage();

	oro.LoadTGA("texturas/oro.tga");
	oro.BuildGLTexture();
	oro.ReleaseImage();

	azul.LoadTGA("texturas/fichaAzul.tga");
	azul.BuildGLTexture();
	azul.ReleaseImage();

	naranja.LoadTGA("texturas/fichaNaranja.tga");
	naranja.BuildGLTexture();
	naranja.ReleaseImage();
	//END NEW//////////////////////////////

	keyFrame[0].angulo=0.0;
	keyFrame[1].angulo=180.0;

	//configuracion inicial del tablero


	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

}


void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	glPushMatrix();
		glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);


		glPushMatrix();
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				sky.skybox(130.0, 130.0, 130.0,cielo.GLindex);
				glEnable(GL_LIGHTING);
				glColor3f(1.0,1.0,1.0);
			glPopMatrix();

			tableroCompleto(anguloActual,bisagra.GLindex,tapete.GLindex,oro.GLindex,triangulos.GLindex,madera.GLindex,posiciones,azul.GLindex,naranja.GLindex);
			// glTranslatef(0,5,0);
			// ficha(azul.GLindex,naranja.GLindex,1);
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers ( );


}

float interpolacion(float actual,float destino){
	float aumento=0.5;
	return ((actual-destino)/abs(actual-destino))*aumento;
}

void animacion()
{
	if (play){
		if (cerrar){
			anguloActual-=interpolacion(keyFrame[0].angulo,keyFrame[1].angulo);
			if (anguloActual>180)
				play=false;
		}
		else if (abrir){
			anguloActual-=interpolacion(keyFrame[1].angulo,keyFrame[0].angulo);
			if (anguloActual<0)
				play=false;
		}
	}
	glutPostRedisplay();
}



void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {

		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;
		case 'c':
			play=true;
			cerrar=true;
			abrir=false;
			break;
		case 'o':
			play=1;
			cerrar=false;
			abrir=true;
			break;
		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

int main ( int argc, char** argv )   // Main Function
{

  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (2000, 2000);	// Tama�o de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Jerarquia"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut funci�n de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut funci�n en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut funci�n de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );


  glutMainLoop        ( );          //

  return 0;
}
