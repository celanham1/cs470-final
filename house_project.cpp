/*
Christopher Lanham
12/7/13
Term project

How to use program:

Right Mouse Button: Opens the menu
“j”: look to the left 
“l”: look to the right
“i”: look up
“k”: look down

Truck Controls:
“w”: up
“a”: left
“s”: down
“d”: right

Num Keys: Change values for gluLookAt()
"x","y","z": rotate along that axis
*/
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <GL/glut.h>

double rX=0; 
double rY=0;
double rZ=0;

//gluLookAt
double gl1=9;
double gl2=3;
double gl3=14.5;
double gl4=8.5;
double gl5=23.5;
double gl6=175;

//gluPerspective
double gp1 = 45;
double gp2 = GLUT_WINDOW_WIDTH/GLUT_INIT_WINDOW_HEIGHT;
double gp3 =0.1;
double gp4 = 100000;

double houseDoorAngle = 0;
double hdX = -2.5;
double hdY = 2;
double hdZ = 0;
double shedDoor1Angle = 0;
double shed1X = -.8;
double shed1Y = 2.5;
double shed1Z = 0;
double shedDoor2Angle = 0;
double shed2X = -1.5;
double shed2Y = 2.5;
double shed2Z = 0;

double truckX = 13;
double truckY = .65;
double truckZ = 8.5;
double truckDir = 0;

double tireRotation = 0;
int tireDir = 0;
double tireX = 6.5;
double tireY = .3;
double tireZ = -5;

static GLuint texName[12];
unsigned int imgwidth, imgheight;
unsigned int imgsize;

unsigned char * LoadBMPimage(const char * imagefile)
{
	//this function is based on http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/#Loading__BMP_images_yourself
	unsigned char data[54];
	unsigned int datastart;
	unsigned char * imgdata;
	FILE * file = fopen(imagefile, "rb");
	if (!file) {printf("Could not find or open file\n");}
	if (fread(data, 1, 54, file)!=54) {printf("Not a BMP file\n"); return false;}
	if (data[0] !='B' || data[1] != 'M' ){
		printf("Metadata not correct for BMP file\n");
		return 0;
		}
	datastart = *(int*)&(data[0x0A]);
	imgsize = *(int*)&(data[0x22]);
	imgwidth = *(int*)&(data[0x12]);
	imgheight = *(int*)&(data[0x16]);
	if (imgsize==0) imgsize= imgwidth*imgheight*3; 
	if (datastart==0) datastart=54; 
	imgdata = new unsigned char[imgsize];
	fread(imgdata, 1, imgsize, file);
	fclose(file);
	return imgdata;
}

void init(void)
{    
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   unsigned char * data;
   glGenTextures(12, texName);

   glBindTexture(GL_TEXTURE_2D, texName[0]);
   data = LoadBMPimage("C:/Users/Chris/textures/planks02.bmp");
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgwidth, imgheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   //glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

   glBindTexture(GL_TEXTURE_2D, texName[1]);
   data = LoadBMPimage("C:/Users/Chris/textures/brick01.bmp");
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgwidth, imgheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

   glBindTexture(GL_TEXTURE_2D, texName[2]);
   data = LoadBMPimage("C:/Users/Chris/textures/RooftilesWood1.bmp");
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgwidth, imgheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

   glBindTexture(GL_TEXTURE_2D, texName[4]);
   data = LoadBMPimage("C:/Users/Chris/textures/DoorsWoodL.bmp");
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgwidth, imgheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

   glBindTexture(GL_TEXTURE_2D, texName[5]);
   data = LoadBMPimage("C:/Users/Chris/textures/DoorsWoodR.bmp");
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgwidth, imgheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

   glBindTexture(GL_TEXTURE_2D, texName[6]);
   data = LoadBMPimage("C:/Users/Chris/textures/Grass.bmp");
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgwidth, imgheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

   glBindTexture(GL_TEXTURE_2D, texName[7]);
   data = LoadBMPimage("C:/Users/Chris/textures/redbeech.bmp");
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgwidth, imgheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 //  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

   glBindTexture(GL_TEXTURE_2D, texName[8]);
   data = LoadBMPimage("C:/Users/Chris/textures/floors5900.bmp");
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgwidth, imgheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

   glBindTexture(GL_TEXTURE_2D, texName[10]);
   data = LoadBMPimage("C:/Users/Chris/textures/concrete8076.bmp");
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgwidth, imgheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

   glBindTexture(GL_TEXTURE_2D, texName[11]);
   data = LoadBMPimage("C:/Users/Chris/textures/DoorsWood01.bmp");
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgwidth, imgheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    glBindTexture(GL_TEXTURE_2D, texName[12]);
   data = LoadBMPimage("C:/Users/Chris/textures/forest.bmp");
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imgwidth, imgheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

   glEnable(GL_TEXTURE_2D);
}

void drawCube()
{
        glPushMatrix();
          
		 glBegin(GL_POLYGON);
		 glTexCoord2d(0.0,0.0);
         glVertex3f(0, 0, 0);
		 glTexCoord2d(1.0,0.0);
         glVertex3f(0, 0, -1);
		 glTexCoord2d(1.0,1.0);
         glVertex3f(-1, 0, -1);
		 glTexCoord2d(0.0,1.0);
         glVertex3f(-1, 0, 0);
		 glEnd();
                
		 glBegin(GL_POLYGON);
		 glTexCoord2d(0.0,0.0);
         glVertex3f(0, 0, 0);
		 glTexCoord2d(1.0,0.0);
         glVertex3f(-1, 0, 0);
		 glTexCoord2d(1.0,1.0);
         glVertex3f(-1, -1, 0);
		 glTexCoord2d(0.0,1.0);
         glVertex3f(0, -1, 0);
		 glEnd();
               
		 glBegin(GL_POLYGON);
		 glTexCoord2d(0.0,0.0);
         glVertex3f(0, 0, 0);
		 glTexCoord2d(1.0,0.0);
         glVertex3f(0, -1, 0);
		 glTexCoord2d(1.0,1.0);
         glVertex3f(0, -1, -1);
		 glTexCoord2d(0.0,1.0);
         glVertex3f(0, 0, -1);
		 glEnd();
               
		 glBegin(GL_POLYGON);
		 glTexCoord2d(0.0,0.0);
         glVertex3f(-1, 0, 0);
		 glTexCoord2d(1.0,0.0);
         glVertex3f(-1, 0, -1);
		 glTexCoord2d(1.0,1.0);
         glVertex3f(-1, -1, -1);
		 glTexCoord2d(0.0,1.0);
         glVertex3f(-1, -1, 0);
		 glEnd();
                
		 glBegin(GL_POLYGON);
		 glTexCoord2d(0.0,0.0);
         glVertex3f(0, 0, 0);
		 glTexCoord2d(1.0,0.0);
         glVertex3f(0, -1, -1);
		 glTexCoord2d(1.0,1.0);
         glVertex3f(-1, -1, -1);
		 glTexCoord2d(0.0,1.0);
         glVertex3f(-1, -1, 0);
		 glEnd();
                
		 glBegin(GL_POLYGON);
		 glTexCoord2d(0.0,0.0);
         glVertex3f(0, 0, 0);
		 glTexCoord2d(1.0,0.0);
         glVertex3f(-1, 0, -1);
		 glTexCoord2d(1.0,1.0);
         glVertex3f(-1, -1, -1);
		 glTexCoord2d(0.0,1.0);
         glVertex3f(0, -1, -1);
		 glEnd();

         glPopMatrix();

}

void drawTriangle()
{
	glPushMatrix();
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0,0.0);
	glVertex3f(-1,0,0);
	glTexCoord2d(0.5,1.0);
	glVertex3f(0,1,0);
    glTexCoord2d(1.0,0.0);
	glVertex3f(1,0,0);
	glEnd();
	glPopMatrix();
}

void drawTree()
{
	glDisable(GL_TEXTURE_2D);
	GLUquadricObj *quadObj = gluNewQuadric();
	glPushMatrix();
			glColor3f(1,.5,0);
			glRotatef(90,1,0,0);
            glTranslatef(0, 0, 0);
			gluCylinder(quadObj, .3, .3, 4, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(0,1,0);
			glRotatef(-90,1,0,0);
            glTranslatef(0, 0, 0);
			gluCylinder(quadObj, 1.5, 0, 4, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(0,1,0);
			glRotatef(-90,1,0,0);
            glTranslatef(0, 0, 1.5);
			gluCylinder(quadObj, 1.5, 0, 4, 10, 10);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void drawTruck()
{
	glDisable(GL_TEXTURE_2D);
	GLUquadricObj *quadObj = gluNewQuadric();
	glMaterialf(GL_FRONT, GL_SHININESS, 0.55 * 128.0);

	//body
	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(0,0,.15);
		glScalef(1.5,.6,2.85);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,.8);
		glTranslatef(-.1,.1,.15);
		glScalef(1.3,.1,1.2);
		drawCube();
	glPopMatrix();

	//Wheels
	glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(90,0,1,0);
		glTranslatef(1,-1.1,0);
		glutSolidTorus(.2,.3,10,10);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(90,0,1,0);
		glTranslatef(1,-1.1,-1.5);
		glutSolidTorus(.2,.3,10,10);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(90,0,1,0);
		glTranslatef(4.5,-1.1,0);
		glutSolidTorus(.2,.3,10,10);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(90,0,1,0);
		glTranslatef(4.5,-1.1,-1.5);
		glutSolidTorus(.2,.3,10,10);
	glPopMatrix();

	glPushMatrix();
		glColor3f(.827,.827,.827);
		glTranslatef(0,-.75,.25);
		glScalef(1.5,.1,.1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(.827,.827,.827);
		glTranslatef(0,-.1,.25);
		glScalef(1.5,.1,.1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(.2,.2,.2);
		glTranslatef(-.1,-.2,.25);
		glScalef(1.3,.55,.05);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(.827,.827,.827);
		glTranslatef(0,-.1,.25);
		glScalef(.1,.7,.1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(.827,.827,.827);
		glTranslatef(-1.4,-.1,.25);
		glScalef(.1,.7,.1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(.827,.827,.827);
		glTranslatef(0,-.9,-5.8);
		glScalef(1.5,.3,.1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(.827,.827,.827);
		glTranslatef(0,-.9,.25);
		glScalef(1.5,.3,.1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(.827,.827,.827);
		glTranslatef(.1,-.9,.25);
		glScalef(.1,.3,.4);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(.827,.827,.827);
		glTranslatef(-1.5,-.9,.25);
		glScalef(.1,.3,.4);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,.5);
		glTranslatef(-.1,-.5,-2.7);
		glScalef(1.3,.1,2.9);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(0,0,-2.7);
		glScalef(.2,.6,3.1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(-1.3,0,-2.7);
		glScalef(.2,.6,3.1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(-.2,0,-5.6);
		glScalef(1.1,.6,.2);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(0,-.6,.15);
		glScalef(1.5,.6,.65);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(.827,.827,.827);
		glTranslatef(-.25,-.6,-.5);
		glScalef(1,.6,1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(0,-.6,-1.5);
		glScalef(1.5,.6,2.5);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(.827,.827,.827);
		glTranslatef(-.25,-.6,-4);
		glScalef(1,.6,1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(0,-.6,-5);
		glScalef(1.5,.6,.8);
		drawCube();
	glPopMatrix();

	//back windshield
	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(0,1,-2.5);
		glScalef(.1,1,.2);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(-1.4,1,-2.5);
		glScalef(.1,1,.2);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glRotatef(90,0,0,1);
		glTranslatef(.1,1.4,-2.5);
		glScalef(.1,1.3,.2);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor4f(1,1,1,.4);
		glRotatef(90,0,0,1);
		glTranslatef(.9,1.4,-2.5);
		glScalef(.8,1.3,.2);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glRotatef(90,0,0,1);
		glTranslatef(1,1.5,-2.5);
		glScalef(.1,1.5,.2);
		drawCube();
	glPopMatrix();

	//roof
	glPushMatrix();
		glColor3f(0,0,1);
		glRotatef(90,1,0,0);
		glTranslatef(0,-2,-.9);
		glScalef(1.5,.5,.1);
		drawCube();
	glPopMatrix();

	//front windshield
	glPushMatrix();
		glColor3f(0,0,1);
		glRotatef(315,1,0,0);
		glTranslatef(0,2.1,-.7);
		glScalef(.1,1.4,.1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glRotatef(315,1,0,0);
		glTranslatef(-1.4,2.1,-.7);
		glScalef(.1,1.4,.1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glRotatef(315,1,0,0);
		glRotatef(90,0,0,1);
		glTranslatef(2.1,1.5,-.7);
		glScalef(.1,1.5,.1);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor4f(1,1,1,.4);
		glRotatef(315,1,0,0);
		glRotatef(90,0,0,1);
		glTranslatef(2,1.4,-.7);
		glScalef(1.1,1.3,.1);
		drawCube();
	glPopMatrix();

	//side window panels
	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(0,.1,-1.1);
		glScalef(.1,.1,1.5);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(-1.4,.1,-1.1);
		glScalef(.1,.1,1.5);
		drawCube();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void drawTable()
{
	GLUquadricObj *quadObj = gluNewQuadric();
	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(-90,1,0,0);
            glTranslatef(.1, .1, -.1);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .1, .1, .8, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(-90,1,0,0);
            glTranslatef(.1, .9, -.1);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .1, .1, .8, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(-90,1,0,0);
            glTranslatef(.9, .1, -.1);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .1, .1, .8, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(-90,1,0,0);
            glTranslatef(.9, .9, -.1);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .1, .1, .8, 10, 10);
	glPopMatrix();

	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(1,.8,0);
		glScalef(1, .1, 1);
		glBindTexture(GL_TEXTURE_2D, texName[7]);
        drawCube();
	glPopMatrix();
}

void drawChair()
{
	GLUquadricObj *quadObj = gluNewQuadric();
	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(-90,1,0,0);
            glTranslatef(0, 0, 0);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .1, .1, .8, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(-90,1,0,0);
            glTranslatef(0, 1, 0);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .1, .1, .8, 10, 10);
	glPopMatrix();

	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(1,.8,0);
		glScalef(1, .1, 1);
		glBindTexture(GL_TEXTURE_2D, texName[7]);
        drawCube();
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(90,0,1,0);
            glTranslatef(0, .5, 0);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(90,0,1,0);
            glTranslatef(1, .5, 0);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(90,0,1,0);
            glTranslatef(0, .3, 0);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(90,0,1,0);
            glTranslatef(1, .3, 0);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
            glTranslatef(1, .4, -1);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
            glTranslatef(1, .9, -1);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
            glTranslatef(1, 1.7, -1);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
            glTranslatef(0, .4, -1);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, 1, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(90,1,0,0);
            glTranslatef(1, -.2, -1.7);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, .8, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(90,1,0,0);
            glTranslatef(1, -.4, -1.7);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, .8, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(90,1,0,0);
            glTranslatef(1, -.6, -1.7);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, .8, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(90,1,0,0);
            glTranslatef(1, -.8, -1.7);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .05, .05, .8, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(-90,1,0,0);
            glTranslatef(1, 0, 0);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .1, .1, 1.8, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,1,1);
			glRotatef(-90,1,0,0);
            glTranslatef(1, 1, 0);
			glBindTexture(GL_TEXTURE_2D, texName[7]);
			gluQuadricTexture(quadObj,GL_TRUE);
			gluCylinder(quadObj, .1, .1, 1.8, 10, 10);
	glPopMatrix();
}

void drawHouseDoor()
{
	glPushMatrix();//-----
		glColor3f(1,1,1);
	    glRotatef(houseDoorAngle,0,1,0);
		glTranslatef(hdX,hdY,hdZ);
        glScalef(1, 2, .1);
		glBindTexture(GL_TEXTURE_2D, texName[11]);
        drawCube();
	glPopMatrix();
}

void drawHouse(){
		//The floor
        glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(0, 0, 0);
                glScalef(6, .5, 6);
				glBindTexture(GL_TEXTURE_2D, texName[8]);
                drawCube();
		glPopMatrix();

		//The right wall
		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-5.5, 3, 0);
                glScalef(.5, 3, 2);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-5.5, 1, -2);
                glScalef(.5, 1, 2);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glPushMatrix();				//window
                glColor4f(1,1,1,.3);
                glTranslatef(-5.5, 2, -2);
                glScalef(.5, 1, 2);
                drawCube();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-5.5, 3, -2);
                glScalef(.5, 1, 2);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-5.5, 3, -4);
                glScalef(.5, 3, 2);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		//The left wall
		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(0, 3, 0);
                glScalef(.5, 3, 2);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(0, 1, -2);
                glScalef(.5, 1, 2);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glPushMatrix();//window
                glColor4f(1,1,1,.3);
                glTranslatef(0, 2, -2);
                glScalef(.5, 1, 2);
                drawCube();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(0, 3, -2);
                glScalef(.5, 1, 2);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(0, 3, -4);
                glScalef(.5, 3, 2);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		//The top left front triangle 
		glPushMatrix();
                glColor3f(1,1,1);
				glRotatef(90,0,1,0);
                glTranslatef(3, 3, 0);
                glScalef(3, 3, 3);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawTriangle();
		glPopMatrix();

		//The top left back triangle 
		glPushMatrix(); 
                glColor3f(1,1,1);
				glRotatef(90,0,1,0);
                glTranslatef(3, 3, -.5);
                glScalef(3, 3, 3);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawTriangle();
		glPopMatrix();

		//the front wall
		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-.5, 3, 0);
                glScalef(.5, 3, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-1, 1, 0);
                glScalef(1, 1, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glPushMatrix(); 
                glColor4f(1,1,1,.3);
                glTranslatef(-1, 2, 0);
                glScalef(1, 1, .5);
                drawCube();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-1, 3, 0);
                glScalef(1, 1, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-2, 3, 0);
                glScalef(.5, 3, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-2.5, 3, 0);
                glScalef(1, 1, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		//Steps
		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-2.5, 0, .5);
                glScalef(1, .5, .5);
				glBindTexture(GL_TEXTURE_2D, texName[10]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-2.5, -.25, .75);
                glScalef(1, .25, .25);
				glBindTexture(GL_TEXTURE_2D, texName[10]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-3.5, 3, 0);
                glScalef(.5, 3, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-4, 1, 0);
                glScalef(1, 1, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glPushMatrix();	
                glColor4f(1,1,1,.3);
                glTranslatef(-4, 2, 0);
                glScalef(1, 1, .5);
                drawCube();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-4, 3, 0);
                glScalef(1, 1, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-5, 3, 0);
                glScalef(.5, 3, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		//The back wall

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-.5, 3, -5.5);
                glScalef(1, 3, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-1.5, 1, -5.5);
                glScalef(1, 1, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glPushMatrix();	//window
                glColor4f(1,1,1,.3);
                glTranslatef(-1.5, 2, -5.5);
                glScalef(1, 1, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-1.5, 3, -5.5);
                glScalef(1, 1, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-2.5, 3, -5.5);
                glScalef(1, 3, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-3.5, 1, -5.5);
                glScalef(1, 1, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
                glColor4f(1,1,1,.3);
                glTranslatef(-3.5, 2, -5.5);
                glScalef(1, 1, .5);
                drawCube();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-3.5, 3, -5.5);
                glScalef(1, 1, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		glPushMatrix();
                glColor3f(1,1,1);
                glTranslatef(-4.5, 3, -5.5);
                glScalef(1, 3, .5);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawCube();
		glPopMatrix();

		//The top right front triangle 
		glPushMatrix();
                glColor3f(1,1,1);
				glRotatef(90,0,1,0);
                glTranslatef(3, 3, -5.5);
                glScalef(3, 3, 3);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawTriangle();
		glPopMatrix();

		//The top right back triangle 
		glPushMatrix();
                glColor3f(1,1,1);
				glRotatef(90,0,1,0);
                glTranslatef(3, 3, -6);
                glScalef(3, 3, 3);
				glBindTexture(GL_TEXTURE_2D, texName[1]);
                drawTriangle();
		glPopMatrix();
		
		
		//The left roof
        glPushMatrix();
                glColor3f(1,1,1);
				glRotatef(45,1,0,0);
                glTranslatef(0, 2.121, -2.121);
                glScalef(6, 0, 4.25);
				glBindTexture(GL_TEXTURE_2D, texName[2]);
                drawCube();
		glPopMatrix();

		//The right roof
        glPushMatrix();
                glColor3f(1,1,1);
				glRotatef(-45,1,0,0);
                glTranslatef(0, 6.363, 2.121);
                glScalef(6, 0, 4.25);
				glBindTexture(GL_TEXTURE_2D, texName[2]);
                drawCube();
		glPopMatrix();
}	

void drawShed()
{
	//floor
	glPushMatrix();
        glColor3f(1,1,1);
		glTranslatef(0, 0, 0);
        glScalef(3, .1, 4);
		glBindTexture(GL_TEXTURE_2D, texName[0]);
        drawCube();
	glPopMatrix();

	//Left wall
	glPushMatrix();
        glColor3f(1,1,1);
		glTranslatef(0, 3, 0);
        glScalef(.2, 3, 4);
		glBindTexture(GL_TEXTURE_2D, texName[0]);
        drawCube();
	glPopMatrix();

	//Right wall
	glPushMatrix();
        glColor3f(1,1,1);
		glTranslatef(-2.8, 3, 0);
        glScalef(.2, 3, 4);
		glBindTexture(GL_TEXTURE_2D, texName[0]);
        drawCube();
	glPopMatrix();

	//Back wall
	glPushMatrix();
        glColor3f(1,1,1);
		glTranslatef(-.2, 3, -3.8);
        glScalef(2.6, 3, .2);
		glBindTexture(GL_TEXTURE_2D, texName[0]);
        drawCube();
	glPopMatrix();

	//Front wall
	glPushMatrix();
        glColor3f(1,1,1);
		glTranslatef(-.2, 3, 0);
        glScalef(.6, 3, .2);
		glBindTexture(GL_TEXTURE_2D, texName[0]);
        drawCube();
	glPopMatrix();

	glPushMatrix();
        glColor3f(1,1,1);
		glTranslatef(-2.2, 3, 0);
        glScalef(.6, 3, .2);
		glBindTexture(GL_TEXTURE_2D, texName[0]);
        drawCube();
	glPopMatrix();

	glPushMatrix();
        glColor3f(1,1,1);
		glTranslatef(-.8, 3, 0);
        glScalef(1.6, .5, .2);
		glBindTexture(GL_TEXTURE_2D, texName[0]);
        drawCube();
	glPopMatrix();
	
	//Doors
	//Right door
	glPushMatrix();
        glColor3f(1,1,1);
		glRotatef(shedDoor1Angle,0,1,0);
		glTranslatef(shed1X,shed1Y,shed1Z);
        glScalef(.7, 2.5, .1);
		glBindTexture(GL_TEXTURE_2D, texName[5]);
        drawCube();
	glPopMatrix();
	
	//left door
	glPushMatrix();
        glColor3f(1,1,1);
		glRotatef(shedDoor2Angle,0,1,0);
		glTranslatef(shed2X,shed2Y,shed2Z);
        glScalef(.7, 2.5, .1);
		glBindTexture(GL_TEXTURE_2D, texName[4]);
        drawCube();
	glPopMatrix();

	//Roof

	glPushMatrix();
        glColor3f(1,1,1);
		glTranslatef(-1.5, 3, 0);
        glScalef(1.5, 1.5, .1);
		glBindTexture(GL_TEXTURE_2D, texName[0]);
        drawTriangle();
	glPopMatrix();

	glPushMatrix();
        glColor3f(1,1,1);
		glTranslatef(-1.5, 3, -4);
        glScalef(1.5, 1.5, .1);
		glBindTexture(GL_TEXTURE_2D, texName[0]);
        drawTriangle();
	glPopMatrix();
	
	glPushMatrix();
        glColor3f(1,1,1);
		glRotatef(45,0,0,1);
		glTranslatef(2.2, 4.25, 0);
        glScalef(.1, 2.4, 4);
		glBindTexture(GL_TEXTURE_2D, texName[2]);
        drawCube();
	glPopMatrix();

	glPushMatrix();
        glColor3f(1,1,1);
		glRotatef(-45,0,0,1);
		glTranslatef(-4.25,2.2, 0);
        glScalef(.1, 2.4, 4);
		glBindTexture(GL_TEXTURE_2D, texName[2]);
        drawCube();
	glPopMatrix();
}

void drawLampost()
{
	glDisable(GL_TEXTURE_2D);
	GLUquadricObj *quadObj = gluNewQuadric();
	glPushMatrix();
			glColor3f(.8,.8,.8);
			glRotatef(-90,1,0,0);
            glTranslatef(0, 0, 0);
			gluCylinder(quadObj, .2, .2, 4, 10, 10);
	glPopMatrix();

	glPushMatrix();
			glColor3f(1,.8,0);
			glRotatef(-90,1,0,0);
            glTranslatef(0, 0, 4);
			gluSphere(quadObj, .5, 10, 10);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void drawTireSwing(){
	glDisable(GL_TEXTURE_2D);
	GLUquadricObj *quadObj = gluNewQuadric();
	//Tire
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(0,0,0);
		glutSolidTorus(.5,1,10,20);
	glPopMatrix();
	
	//Rope
	glPushMatrix();
		glColor3f(1,.8,0);
		glRotatef(-90,1,0,0);
		glTranslatef(0,0,1.35);
		gluCylinder(quadObj, .15, .15, 4, 10, 10);
	glPopMatrix();
	//Branch its on
	glPushMatrix();
		glColor3f(1,.5,0);
		glRotatef(90,0,1,0);
		glTranslatef(0,5.35,-3);
		gluCylinder(quadObj, .15, .15, 4, 10, 10);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	double w = glutGet( GLUT_WINDOW_WIDTH )/200; 
    double h = glutGet( GLUT_WINDOW_HEIGHT )/200;

	//Set up the background image
	/*
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
	glOrtho(0,1,0,1,0,1);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, texName[12]);
	glColor3f(1,1,1);
	glBegin( GL_QUADS ); {
	  glTexCoord2f( 0, 0 );
	  glVertex2f( 0, 0 );
	  glTexCoord2f( 0, 1 );
	  glVertex2f( 0, 1 );
	  glTexCoord2f( 1, 1 );
	  glVertex2f( 1, 1 );
	  glTexCoord2f( 1, 0 );
	  glVertex2f( 1, 0 );
	} glEnd();

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	*/

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho( -1 * w, 1 * w, -1 * h, 1 * h, 20,-20);
	gluPerspective(gp1, gp2, gp3, gp4);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity(); 
	gluLookAt(gl1,gl2,gl3,gl4,gl5,gl6,0,1,0);
    glRotatef(rX,1,0,0);
    glRotatef(rY,0,1,0);
    glRotatef(rZ,0,0,1);

	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable(GL_TEXTURE_2D);

	//background
   /*
	glPushMatrix();
		glColor3f(1,1,1);
		glRotatef(180,1,0,0);
		glTranslatef(19,0,1);
		glScalef(20,20,0);
		glBindTexture(GL_TEXTURE_2D, texName[12]);
		drawCube();
	glPopMatrix();
	*/
	//Ground
	int groundSize = 20;
	for(int i=0; i<groundSize; i++){
		for(int j=0; j<groundSize; j++){
			glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(i,0,j);
			glScalef(1,0,1);
			glBindTexture(GL_TEXTURE_2D, texName[6]);
			drawCube();
			glPopMatrix();
		}
	}

	glPushMatrix();
		glTranslatef(10,.2,5);
		glScalef(.4,.4,.4);
		drawHouse();
		drawHouseDoor();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(truckX,truckY,truckZ);
		glRotatef(truckDir,0,1,0);
		glScalef(.4,.4,.4);
		drawTruck();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(13,.1,5);
		glScalef(.4,.4,.4);
		drawShed();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(7,.05,7);
		glScalef(.5,.5,.5);
		drawTable();
	glPopMatrix();

	glPushMatrix();
		glRotatef(180,0,1,0);
		glTranslatef(-7,.05,-6.8);
		glScalef(.35,.35,.35);
		drawChair();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90,0,1,0);
		glTranslatef(-7,.05,8);
		glScalef(.35,.35,.35);
		drawChair();
	glPopMatrix();

	glPushMatrix();
		glRotatef(180,0,1,0);
		glTranslatef(-5,1.5,-6);
		glScalef(.3,.5,.3);
		drawTree();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90,0,1,0);
		glRotatef(tireRotation,1,0,0);
		glTranslatef(tireX,tireY,tireZ);
		glScalef(.15,.15,.15);
		drawTireSwing();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(14,1.2,9);
		glScalef(.3,.5,.3);
		drawTree();
	glPopMatrix();

	/*
	glPushMatrix();
		glTranslatef(15,-.5,7);
		glScalef(.45,.45,.35);
		drawLampost();
	glPopMatrix();
  */
    glFlush();

	//Animate the Tire Swing
	
	if(tireRotation == 0) {
		if(tireDir == 0) {tireRotation = -30; tireX = 6.5; tireY = 2.5; tireZ = -3.8;}
		else if(tireDir == 1) {tireRotation = 30; tireX = 6.5; tireY = -2.5; tireZ = -4.8;}
	}
	else if(tireRotation == 30) {
		tireDir = 0;
		tireRotation = 0;
		tireX = 6.5;
		tireY = .3;
		tireZ = 5;
	}
	else if(tireRotation == -30){
		tireDir = 1;
		tireRotation = 0;
		tireX = 6.5;
		tireY = .3;
		tireZ = 5;
	}
	glutPostRedisplay();
	glutSwapBuffers();
	glDisable(GL_TEXTURE_2D);
}

void menu(int item)
{
        switch (item)
        {
		case 0: //front
			gl1=9;
			gl2=3;
			gl3=14.5;
			gl4=8.5;
			gl5=23.5;
			gl6=175;
			break;
		case 1://back
			gl1=9;
			gl2=3.5;
			gl3=3;
			gl4=15.5;
			gl5=35;
			gl6=-274;
		case 2://top
			gl1=8.5;
			gl2=8;
			gl3=13;
			gl4=8.5;
			gl5=296;
			gl6=175;
			break;
		case 3://left
			gl1=14;
			gl2=3;
			gl3=8.5;
			gl4=296;
			gl5=81;
			gl6=9.5;
			break;
		case 4://right
			gl1=-3.5;
			gl2=5.5;
			gl3=8;
			gl4=-122;
			gl5=23;
			gl6=9;
			break;
		case 5://top left
			gl1=10;
			gl2=3;
			gl3=13;
			gl4=-77.5;
			gl5=95;
			gl6=175;
			break;
		case 6://top right
			gl1=7.5;
			gl2=4;
			gl3=13;
			gl4=-113;
			gl5=155;
			gl6=175;
			break;
		case 7:
			if(houseDoorAngle == 0) {
				houseDoorAngle = 90;
				hdX = 1;
				hdY = 2;
				hdZ = -3.4;
			}
			else if(houseDoorAngle == 90){
				houseDoorAngle = 0;
				hdX = -2.5;
				hdY = 2;
				hdZ = 0;
			}
			break;
		case 8:
			if(shedDoor1Angle == 0) {shedDoor1Angle = 90; shed1X= 0, shed1Y = 2.5,shed1Z=-.7;}
			else if (shedDoor1Angle == 90) {shedDoor1Angle = 0; shed1X = -.8, shed1Y=2.5,shed1Z=0;}

			if(shedDoor2Angle == 0) {shedDoor2Angle = 90; shed2X = 0, shed2Y=2.5,shed2Z=-2.1;}
			else if (shedDoor2Angle == 90){shedDoor2Angle = 0; shed2X = -1.5, shed2Y=2.5,shed2Z=0;}
			break;
		case 9:
			std::exit(0);
        default:
                break;
        }

        glutPostRedisplay();

        return;
}

void input(unsigned char key, int a, int b)
{
	switch(key){
	case '1':
		gl1+=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case '2':
		gl1-=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case '3':
		gl2+=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case '4':
		gl2-=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case '5':
		gl3+=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case '6':
		gl3-=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case '7':
		gl4+=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case '8':
		gl4-=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case '9':
		gl5+=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case '0':
		gl5-=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case '-':
		gl6+=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case '=':
		gl6-=.5;
		printf("gluLookAt(%f,%f,%f,%f,%f,%f,0,1,0)\n",gl1,gl2,gl3,gl4,gl5,gl6);
		break;
	case 's':
		truckZ += 1;
		if(truckDir = 90) truckDir += -90;
		else if (truckDir = -90) truckDir += 90;
		break;
	case 'w':
		truckZ -= 1;
		if(truckDir = 90) truckDir += 90;
		else if (truckDir = -90) truckDir += -90;
		break;
	case 'd':
		truckX -= 1;
		truckDir = -90;
		break;
	case 'a':
		truckX += 1;
		truckDir = 90;
		break;
	case 'j': //rotate screen left
		gl4+=.5;
		break;
	case 'l': //move right
		gl4-=.5;
		break;
	case 'i':
		gl5+=.5; //move up
		break;
	case 'k':
		gl5-=.5; //move down
		break;
	case 'm':
	case 'M':
		break;
	case 'x':
	case 'X':
		rX += 5;
		break;
	case 'y':
	case 'Y':
		rY += 5;
		break;
	case 'z':
	case 'Z':
		rZ += 5;
		break;
	case 'q':
	case 'Q':
		std::exit(0);
	}

	 glutPostRedisplay();
}

int main(int argc, char* argv[]){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800,800);
  glutCreateWindow("Final Project");
  init();
 // glEnable(GL_LIGHTING);
 // glEnable(GL_LIGHT0);
  //GLfloat lightpos[] = {1,1,1,1};
  //glLightfv(GL_LIGHT0,GL_POSITION, lightpos); 

  glutCreateMenu(menu);
  glutAddMenuEntry("View Front", 0);
  glutAddMenuEntry("View Back", 1);
  glutAddMenuEntry("View Top", 2);
  glutAddMenuEntry("View Left", 3);
  glutAddMenuEntry("View Right", 4);
  glutAddMenuEntry("View Top Left",5);
  glutAddMenuEntry("View Top Right",6);
  glutAddMenuEntry("Use House Door",7);
  glutAddMenuEntry("use Shed Door",8);
  glutAddMenuEntry("Exit", 9);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutDisplayFunc(display);
  glutKeyboardFunc(input);

  glutMainLoop();
  return 0;
}
