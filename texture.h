//#include <windows.h>  //Solo para Windows
//#include <gl/gl.h>     // The GL Header File
//#include <stdio.h>
//#include <string.h>
// #include "Main.h"
//#include "gl.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
class CTexture
{
public:
	char* name;
	unsigned char*  imageData;
	int		bpp;			// Image Color Depth In Bits Per Pixel
	int		width;			// Image Width
	int		height;		    // Image Height
	unsigned int    GLindex;

	bool LoadTGA(char* filename);		// Loads A TGA File Into Memory
	bool LoadBMP(char* filename);
	void BuildGLTexture();
	void ReleaseImage();
};
