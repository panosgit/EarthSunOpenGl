#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> 
#include <fstream>
#include "gl/glut.h"   // - An interface and windows 
//   management library
#include "visuals.h"   // Header file for our OpenGL functions

GLfloat viewangle = 0, tippangle = 0; //gwnies peristrofwn gyrw apo aksones x,y (velakia)

GLfloat year = 0.0;   //degrees
static float rotx = 0.0;
GLfloat alphaDynamic = 0;
bool alphaDynamicIncreaseBoolean = true;
GLfloat SpeedMultiplicator = 1.0;
GLfloat DaysPerYear = 10.0;
GLfloat day = 0.0;
GLfloat moonAroundEarth = 0.0;
GLfloat earthItsSelf = 0.0;

GLfloat EarthOrbitRadius = 1.25;
GLfloat MoonOrbitRadius = 0.20;
GLfloat daySpeed = 5.0 * SpeedMultiplicator;
GLfloat yearSpeed = DaysPerYear / 360.0 * daySpeed * SpeedMultiplicator * 4;
GLfloat moonAroundEarthSpeed = 1.25 * SpeedMultiplicator;
GLfloat earthItsSelfSpeed = 2 * SpeedMultiplicator;



static float tx = 0.0, sx = 0.0, ax = 0.0, vx = 0.0, rx = 0.0;

static float ty = 0.0, sy = 0.0, ay = 0.0, vy = 0.0, ry = 0.0;

static float tz = 0.0, sz = 0.0, az = 301.0, vz = 0.0, rz = 0.0;

static float scalex, scaley, scalez; //scale for planet

GLfloat  xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;


int pause = 0; //if pause is pressed
int donewithStarts = 0;
const int starsnumber = 500;
model md; //object
float thesis[starsnumber][3]; //star positions

using namespace std;


void Setup() {
	ReadFile(&md);

	scalex = (rand() % 1 + 0.05) / 3.2 / 8;
	printf("scalex2 = %6f \n", scalex);
	scaley = (rand() % 1 + 0.05) / 3.6 / 8;
	printf("scaley2 = %6f \n", scaley);
	scalez = (rand() % 1 + 0.05) / 4 / 8; //tyxaio sxhma
	printf("scalez2 = %6f \n", scalez);

	//Parameter handling
	glShadeModel(GL_SMOOTH);

	//(02)
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);

	// (06) // polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);



	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	glEnable(GL_CULL_FACE);

	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	// incoming //  // stored //
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glAlphaFunc(GL_GREATER, 0.5);
	//glEnable(GL_ALPHA_TEST);


	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);



}



void sun() { //method to create sun
	glTranslatef(tx - 15, ty, tz);
	glPushMatrix();
	glColor3f(255, 255, 0);
	glutSolidSphere(3, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glColor4f(255, 255, 0, alphaDynamic);
	glutSolidSphere(4, 50, 50);
	glPopMatrix();




}

void stars(int starsNumber) {//method to create stars
	int i = 0;

	if (donewithStarts == 0) { //do it just one time
		donewithStarts = 1;
		srand(time(NULL));
		for (i = 0; i < starsNumber; i++) { //starsNumber stars in the scene
			sx = rand() % 1000 + -starsNumber;
			sy = rand() % 1000 + -starsNumber;
			sz = rand() % 1000 + -starsNumber; //random star positions
			glPushMatrix();
			glTranslatef(sx, sy, sz);
			glColor4f(1, 1, 1, 0.5);
			glScalef(0.5, 0.5, 0.5);
			glutSolidSphere(1, 25, 25);
			glPopMatrix();

			thesis[i][0] = sx;
			thesis[i][1] = sy;
			thesis[i][2] = sz; 
		}
	}
	else {
		for (i = 0; i < starsnumber; i++) {
			sx = thesis[i][0];
			sy = thesis[i][1];
			sz = thesis[i][2]; //saved position of stars
			glPushMatrix();
			glTranslatef(sx, sy, sz);
			glColor4f(1, 1, 1, 0.5);
			glScalef(0.5, 0.5, 0.5);
			glutSolidSphere(1, 25, 25);
			glPopMatrix();

		}//for
	}//else
}

void earthMoonWithObject() {// method to create earth moon and their rotation
	glRotatef(year, 0, 1.0, 0.0);   // Rotation of earth aroung sun
	glTranslatef(tx + 15, ty, tz);
	glPushMatrix();
	glRotatef(earthItsSelf, 0, 0, 255);   // selfrotation of earth
	glColor3f(0, 0.4, 1);
	glScalef(scalex, scalex, scalex);//how big ?
	DisplayModel(md); //show object
	glPopMatrix();

	glPushMatrix();
	glRotatef(day, 0, 1.0, 0.0);   // Rotation of moon aroung earth
	glTranslatef(tx + 5, ty, tz);//go a little away 
	glColor3f(192, 192, 192);
	glScalef(scalex / 2, scalex / 2, scalex / 2);//how big ?
	DisplayModel(md); //show object
	glPopMatrix();
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
													   // and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (pause == 1)
	{
		glPushMatrix();
		glTranslatef(-10.5, 5, -20);
		glScalef(0.007, 0.007, 0.007);
		glColor3f(0, 1, 0.3);
		const char str[] = "Game paused. Press Space bar to continue...";
		//sxetiko mhnyma pros ton xrhsth
		for (int i = 0; i < strlen(str); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
		glPopMatrix();
	}


	glTranslatef(0, 0, -30);
	glRotatef(tippangle, 1, 0, 0);  // Up and down arrow keys 'tip' view.
	glRotatef(viewangle, 0, 1, 0);  // Right/left arrow keys 'turn' view.
	glRotatef(zAngle, 0, 0, 1);
	glRotatef(yAngle, 0, 1, 0);
	glRotatef(xAngle, 1, 0, 0);

	stars(starsnumber);
	earthMoonWithObject();
	sun();
	glutSwapBuffers();
}



void Resize(int w, int h)
{
	// define the visible area of the window ( in pixels )
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

	// Setup viewing volume

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
}


void Idle()
{


	if (pause == 0) //if normal flow
	{

		if (alphaDynamicIncreaseBoolean == true) {
			alphaDynamic = alphaDynamic + 0.05;
			if (alphaDynamic >= 1) {
				alphaDynamicIncreaseBoolean = false;
			}
		}
		else {
			alphaDynamic = alphaDynamic - 0.05;
			if (alphaDynamic <= 0) {
				alphaDynamicIncreaseBoolean = true;
			}
		}

		day += daySpeed;
		year += yearSpeed;
		earthItsSelf += earthItsSelfSpeed;
		moonAroundEarth += moonAroundEarthSpeed;

		glutPostRedisplay();

	}
	else{
		glutPostRedisplay();
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	if (pause == 0) //if not in pause
	{
		switch (key)
		{
		case 'q': exit(0); break;
		case 'x': xAngle += 5;  break; // peristrofh ston x aksona tou
		case 'y': yAngle += 5;  break; // peristrofh ston y aksona tou
		case 'z': zAngle += 5;  break; // peristrofh ston z aksona tou
		case ' ': pause = 1; break; //pause

		default: break;
		}
	}

	//allow only resume and exit
	else if (pause == 1)
	{
		switch (key)
		{
		case ' ': pause = 0; break;
		case 'q': exit(0); break;
		default: break;
		}
	}
	glutPostRedisplay();
}

void Special_Keys(int key, int x, int y)
{
	if (pause == 0) //normal row (no pause)
	{
		switch (key) {

		case GLUT_KEY_LEFT:  viewangle -= 5;  break;
		case GLUT_KEY_RIGHT:  viewangle += 5;  break;
		case GLUT_KEY_UP:  tippangle -= 5;  break;
		case GLUT_KEY_DOWN:  tippangle += 5;  break; //peristrofh ston geniko x 'h y aksona
		}
	}
	glutPostRedisplay();
}


void ReadFile(model *md)
{
	ifstream obj_file("planet.obj");                   // Open the file for reading planet

	if (obj_file.fail()) {
		printf("failed to read");
		exit(1);
	}
	printf("planet reading success!\n");


	char a = ' ';
	int i = 0;
	while (i < 3)
	{
		obj_file >> a;
		if (a == '#')
			i++;
	}

	obj_file >> md->vertices;                      // Get the number of vertices

	i = 0;
	while (i < 15)
	{
		obj_file >> a;
		i++;
	}


	for (int i = 0; i < md->vertices; i++) {                        // Get the vertex coordinates
		obj_file >> a;
		obj_file >> md->obj_points[i].x;
		obj_file >> md->obj_points[i].y;
		obj_file >> md->obj_points[i].z;
	}
	//diavasma points

	i = 0;
	while (i < 3)
	{
		obj_file >> a;
		if (a == '#')
			i++;
	}

	i = 0;
	while (i < 17)
	{
		obj_file >> a;
		i++;
	}

	obj_file >> md->faces;     // Get the number of faces

	i = 0;
	while (i < 23)
	{
		obj_file >> a;
		i++;
	}

	int v;

	for (int i = 0; i < md->faces; i++) {                        // Get the face structure
		obj_file >> a;
		obj_file >> md->obj_faces[i].vtx[0];
		obj_file >> a;
		obj_file >> a;
		obj_file >> v;
		obj_file >> md->obj_faces[i].vtx[1];
		obj_file >> a;
		obj_file >> a;
		obj_file >> v;
		obj_file >> md->obj_faces[i].vtx[2];
		obj_file >> a;
		obj_file >> a;
		obj_file >> v;
	}

	obj_file.close();
}


void DisplayModel(model md)
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < md.faces; i++)
	{
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[0] - 1].x, md.obj_points[md.obj_faces[i].vtx[0] - 1].y, md.obj_points[md.obj_faces[i].vtx[0] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[1] - 1].x, md.obj_points[md.obj_faces[i].vtx[1] - 1].y, md.obj_points[md.obj_faces[i].vtx[1] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[2] - 1].x, md.obj_points[md.obj_faces[i].vtx[2] - 1].y, md.obj_points[md.obj_faces[i].vtx[2] - 1].z);
	}
	glEnd();
}