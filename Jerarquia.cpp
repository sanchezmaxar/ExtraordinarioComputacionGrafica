
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

//variables para ver la camara
CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 92.0f;    // Look Position In The Z-Axis (NEW)

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
CTexture dice;
//variables de animacion
bool play=false;
bool cerrar=false;
bool abrir=false;
bool tiro=false;
typedef struct _frame {
	float angulo;
} FRAME ;
FRAME keyFrame [MAX_FRAMES];
float anguloActual=180;
//para el cubo
float rotacionAleatoriax=0;
float rotacionAleatoriaz=0;
float rotacionAleatoriax2=0;
float rotacionAleatoriaz2=0;
float rAx=0;
float rAz=0;
float rAxAux=0;
float rAzAux=0;
float rAx2=0;
float rAz2=0;
float rAxAux2=0;
float rAzAux2=0;


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

	dice.LoadTGA("texturas/dice.tga");
	dice.BuildGLTexture();
	dice.ReleaseImage();
	//END NEW//////////////////////////////

	keyFrame[0].angulo=0.0;
	keyFrame[1].angulo=180.0;

	//configuracion inicial del tablero


	// objCamera.Position_Camera(0,2.5f,3,
	// 	 0,2.5f,0,
	// 	  0, 1, 0);
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
      GLfloat mat_shininess[] = { 50.0 };
      GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
      glClearColor (0.0, 0.0, 0.0, 0.0);
      glShadeModel (GL_SMOOTH);

      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
      glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	objCamera.Position_Camera(4.229999, 31.900013, -11.579988,
	  4.229999, 31.900013, -14.579986,
	  0.000000, 1.000000, 0.000000);
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
			glPushMatrix();
				glTranslatef(27,2,0);
				cubo(dice.GLindex,rAx,rAz);
				glTranslatef(0,0,4);
				cubo(dice.GLindex,rAx2,rAz2);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers ( );


}

float interpolacion(float actual,float destino){
	float aumento=0.5;
	return ((actual-destino)/abs(actual-destino))*aumento;
}

float interpolacionCubo(float origen,float destino,float tiempo){
	return (destino-origen)/tiempo;
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
	if (tiro){
		if (rAx!=rotacionAleatoriax ||rAz!=rotacionAleatoriaz  ){
			rAx+=interpolacionCubo(rAxAux,rotacionAleatoriax,10);
			if (rAx>360)
				rAx-=360;
			rAz+=interpolacionCubo(rAzAux,rotacionAleatoriaz,10);
			if (rAz>360)
				rAz-=360;
		}
		if (rAx2!=rotacionAleatoriax2 || rAz2!=rotacionAleatoriaz2  ){
			rAx2+=interpolacionCubo(rAxAux2,rotacionAleatoriax2,10);
			if (rAx2>360)
				rAx2-=360;
			rAz2+=interpolacionCubo(rAzAux2,rotacionAleatoriaz2,10);
			if (rAz2>360)
				rAz2-=360;
		}
		if ((rAx==rotacionAleatoriax  &&rAx2==rotacionAleatoriax2 )||(rAz==rotacionAleatoriaz  &&rAz2==rotacionAleatoriaz2)){
			tiro=false;
			rAxAux=rAx;
			rAzAux=rAz;
			rAxAux2=rAx2;
			rAzAux2=rAz2;
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
			play=true;
			cerrar=false;
			abrir=true;
			break;
		case 't'://tirar
		case 'T':
			tiro=true;
			while (rAxAux==rotacionAleatoriax || rAzAux==rotacionAleatoriaz||rAxAux2==rotacionAleatoriax2 || rAzAux2==rotacionAleatoriaz2){
				rotacionAleatoriax=((rand()%3)+1)*90;
				rotacionAleatoriaz=((rand()%3)+1)*90;
				rotacionAleatoriax2=((rand()%3)+1)*90;
				rotacionAleatoriaz2=((rand()%3)+1)*90;
			}
			break;
		case 'p':
			printf("%f %f %f\n", objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z);
			printf("%f %f %f\n", 	objCamera.mView.x, objCamera.mView.y, objCamera.mView.z);
			printf("%f %f %f\n", objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
			printf("%f\n",g_lookupdown );
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
