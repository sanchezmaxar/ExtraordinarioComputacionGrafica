
 // g++ Jerarquia.cpp Camera.cpp texture.cpp figuras.cpp -lGL -lglut -lGLU -w
#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "texture.h"
#include "Camera.h"
#include "figuras_max.cpp"

#define MAX_FRAMES 20

int w = 500, h = 500;
int frame=0,time,timebase=0;
int deltaTime = 0;

//variables para ver la camara
CCamera objCamera;	//Create objet Camera
bool changeCamera=false;

//variables de ficha1 dummy
float fichaDummyx=2.83,
	fichaDummyy=4.2,
	fichaDummyz=0.57,
	fichaDviewx=2.82, 	
	fichaDviewy=6,
	fichaDviewz=-2.43,
	fichaDryAnterior=0,
	fichaDry=0;
GLfloat matFichaAzul[]={0.184,0.384,0.850,1.0};//ficha azul

GLfloat g_lookupdown = 92.0f;    // Look Position In The Z-Axis (NEW)

//variables para las luces
//para todo el tablero se usara una luz direccional
GLfloat posLiDir[]={0.0,32.0,0.0,0.0}; //se posiciona en 0,32,0 como fuente direccional
GLfloat ambLiDir[]={0.5,0,0,1}; //un color amarillesco
GLfloat espLiDir[]={0.5,0.2,0,1}; //un color medio morado
GLfloat difLiDir[]={0.5,0.2,0,1};
//luz posicional 
GLfloat light1_ambient[] = { 0, 0, 0.2, 1.0 };
GLfloat light1_diffuse[] = { 0.0, 1, 1.0, 1.0 };
GLfloat light1_specular[] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat light1_position[] = { -22.0, 30.0, 1.0, 1.0 };
GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
//luz dos
GLfloat light_specular2[] = {0.0, 0.5, 1.0}; //set the light specular to white
GLfloat light_ambient2[] = {0.0, 0.6, 0.0}; //set the light ambient to black
GLfloat light_diffuse2[] = {0.4, 0.4, 0.4}; //set the diffuse light to white
GLfloat light_position2[] = { 1.0, 1.0, 1.0, 1.0 };
// GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
// GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat light_position[] = {0,12,-13,0 };
// GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

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
int totalK;
int indiceK;
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
// int posiciones[24][5]={
// {1,1,1,1,1}
// ,{0,0,0,0,0}
// ,{0,0,0,0,0}
// ,{0,0,0,0,0}
// ,{2,2,2,0,0}
// ,{0,0,0,0,0}
// //el otro lado tablero 1
// ,{2,2,2,2,2}
// ,{0,0,0,0,0}
// ,{0,0,0,0,0}
// ,{0,0,0,0,0}
// ,{1,1,1,0,0}
// ,{0,0,0,0,0}
// //tablero 2
// ,{2,2,2,2,2}
// ,{0,0,0,0,0}
// ,{0,0,0,0,0}
// ,{0,0,0,0,0}
// ,{0,0,0,0,0}
// ,{1,1,0,0,0}
// //lado 2 tablero 2
// ,{1,1,1,1,1}
// ,{0,0,0,0,0}
// ,{0,0,0,0,0}
// ,{0,0,0,0,0}
// ,{0,0,0,0,0}
// ,{2,2,0,0,0}};

//punto 2
int posiciones[24][5]={

//tablero 2 	
{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
//lado 2 tablero 2
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{1,1,1,1,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{2,2,2,2,0}
//el otro lado tablero 1
,{2,2,2,2,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{0,0,0,0,0}
,{1,1,1,1,0}};


//variables auxiliares

float ax=0;
float ay= 8.9;
float az=0;


void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

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
	totalK=2;
	//configuracion inicial del tablero

   
}


void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	glPushMatrix();
		glRotatef(g_lookupdown,1.0f,0,0);
		light_position2[0] = ax;
		light_position2[1] = ay;
		light_position2[2] = az;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0,GL_AMBIENT,ambLiDir);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,difLiDir);
		glLightfv(GL_LIGHT0,GL_SPECULAR,espLiDir);

		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 22.0);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	
		glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
		glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 10.0);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);



		if (!changeCamera)
			objCamera.Position_Camera(4.229999, 31.900013, -11.579988,
			  4.229999, 31.900013, -14.579986,
			  0.000000, 1.000000, 0.000000);			
		else{
			
			if (fichaDryAnterior<fichaDry)
				objCamera.Position_Camera(fichaDummyx,fichaDummyy,fichaDummyz,
					fichaDviewx,fichaDummyy,fichaDviewz,0,1,0,-CAMERASPEED);
			else if (fichaDryAnterior>fichaDry)
				objCamera.Position_Camera(fichaDummyx,fichaDummyy,fichaDummyz,
					fichaDviewx,fichaDummyy,fichaDviewz,0,1,0,CAMERASPEED);
			else
				objCamera.Position_Camera(fichaDummyx,fichaDummyy,fichaDummyz,
					fichaDviewx,fichaDummyy,fichaDviewz,0,1,0,0);		
			fichaDryAnterior=fichaDry;
		}
				
		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,
				objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
				objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);

		glPushMatrix();
			glPushMatrix();
				glTranslatef(ax,ay,az);
				cubo(1);
			glPopMatrix();
			// glPushMatrix(); //Creamos cielo
			// 	glDisable(GL_LIGHT0);
			// 	glTranslatef(0,60,0);
			// 	sky.skybox(130.0, 130.0, 130.0,cielo.GLindex);
			// 	glEnable(GL_LIGHT0);
			// 	// glColor3f(1.0,1.0,1.0);
			// glPopMatrix();
			glPushMatrix();
				tableroCompleto(anguloActual,bisagra.GLindex,tapete.GLindex,oro.GLindex,triangulos.GLindex,madera.GLindex,posiciones,azul.GLindex,naranja.GLindex);
				glTranslatef(27,2,0);
				cubo(dice.GLindex,rAx,rAz);
				glTranslatef(0,0,4);
				cubo(dice.GLindex,rAx2,rAz2);
			glPopMatrix();
			glPushMatrix();
				// glRotatef(fichaDry,0,1,0);
				glTranslatef(fichaDummyx,fichaDummyy-2.2,fichaDummyz);
				// glRotatef(fichaDrx,1,0,0);
				// glRotatef(fichaDrz,0,0,1);
				ficha(matFichaAzul);
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
		if (abrir){
			if (anguloActual<keyFrame[0].angulo)
				indiceK--;
				if (indiceK==0){
					abrir=false;
					play=false;
				}
			else
				anguloActual-=interpolacion(keyFrame[indiceK].angulo,keyFrame[indiceK-1].angulo);
		}
		else if (cerrar){
			if (anguloActual>=keyFrame[1].angulo)
				indiceK++;
				if (indiceK==totalK-1){
					play=false;
					cerrar=false;
				}
			else
				anguloActual-=interpolacion(keyFrame[indiceK].angulo,keyFrame[indiceK+1].angulo);
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
			if (changeCamera){
				objCamera.Move_Camera( CAMERASPEED+0.2 );
				fichaDummyz-=0.8073046875;
				fichaDviewz-=0.8073046875;
			}
			break;

		case 's':
		case 'S':
			if (changeCamera){
				objCamera.Move_Camera(-(CAMERASPEED+0.2));
				fichaDummyz+=0.8073046875;
				fichaDviewz+=0.8073046875;	
			}
			break;

		case 'a':
		case 'A':
			if (changeCamera){
				objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
				fichaDummyx-=0.8073046875;
				fichaDviewx-=0.8073046875;
			}
			break;

		case 'd':
		case 'D':
			if (changeCamera){
				objCamera.Strafe_Camera( CAMERASPEED+0.4 );
				fichaDummyx+=0.8073046875;
				fichaDviewx+=0.8073046875;
			}
			break;
		case 'c':
		case 'C':
			play=true;
			cerrar=true;
			abrir=false;
			indiceK=0;
			break;
		case 'o':
		case 'O':
			play=true;
			cerrar=false;
			abrir=true;
			indiceK=totalK-1;
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
		case 'l':
		case 'L':
			changeCamera=!changeCamera;
			if (changeCamera){
				//poner la camara en movimiento usando la ficha dummy
				g_lookupdown=12;
				objCamera.Position_Camera(fichaDummyx,fichaDummyy,fichaDummyz,
				fichaDviewx,fichaDummyy,fichaDviewz,0,1,0);
			}
			else{
				fichaDviewx=objCamera.mView.x;
				fichaDviewy=objCamera.mView.y;
				fichaDviewz=objCamera.mView.z;
				fichaDviewx=objCamera.mView.x;
				fichaDviewy=objCamera.mView.y;
				fichaDviewz=objCamera.mView.z;
				g_lookupdown=92;
			}
			break;
		case 'g':
		case 'G':
			ax-=1;
			break;
		case 'j':
		case 'J':
			ax+=1;
			break;
		case 'n':
		case 'N':
			ay-=1;
			break;
		case 'm':
		case 'M':
			ay+=1;
			break;
		case 'y':
		case 'Y':
			az-=1;
			break;
		case 'h':
		case 'H':
			az+=1;
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
		if (changeCamera){
			objCamera.UpDown_Camera(CAMERASPEED);
			fichaDummyy+=10;}
		break;

	case GLUT_KEY_PAGE_DOWN:
		if (changeCamera){
			objCamera.UpDown_Camera(-CAMERASPEED);
			fichaDummyy-=10;}
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
    	if (changeCamera)
    		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		if (changeCamera)
			g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		// if (changeCamera){
			// objCamera.Rotate_View(-CAMERASPEED);
			fichaDry+=4;
		// }
		break;

	case GLUT_KEY_RIGHT:
		// if (changeCamera){
			// objCamera.Rotate_View( CAMERASPEED);
			fichaDry-=4;
		// }
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
  glutCreateWindow    ("Proyecto Extraordinario"); // Nombre de la Ventana
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
