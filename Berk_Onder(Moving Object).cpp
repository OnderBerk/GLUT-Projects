/*
Student  : Berk Onder
Id       : 21502378
*/

/* You can change the direction or the speed of any plane determined by a random number 
in the range of plane count. In order to specify a random plane, please press the space key 
and then you can change its attributes by using arrow keys (left,right,up). However
if specified plane's moveable status is not true, you cannot do this operation until 
you change its moveability by clicking the mouse right button. */

#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define TIMER_PERIOD   10 
#define TIMER_ON        1 
#define D2R     0.0174532
#define MAX			   10

typedef struct {
	int xx;
	int yy;
}random_t;
random_t random[MAX*MAX];

typedef struct {
	int CoordinateX;
	int CoordinateY;

	bool Stat = false;
	bool Moveable = false;
}plane_t;
plane_t plane[MAX];

int count = 0, j = 0, k, i;
bool up = false, down = false, right = false, left = false;
int globalX, globalY;
int winWidth, winHeight;
int randPlane = 0;

void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}

void print(int x, int y, char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);

	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, string[i]);
}

void vprint(int x, int y, void *font, char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);

	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, str[i]);
}

void vprint2(int x, int y, float size, char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);

	for (i = 0; i < len; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);

	glPopMatrix();
}

void shapePlane(int planeNo, int planeX, int planeY) {
	glColor3ub(47, 181, 239);
	glRectf(planeX + 50, planeY + 60, planeX + 70, planeY - 5);

	glColor3ub(285, 188, 40);
	glBegin(GL_TRIANGLES);
	glVertex2f(planeX + 50, planeY + 20);
	glVertex2f(planeX + 50, planeY + 35);
	glVertex2f(planeX + 20, planeY + 10);
	glEnd();

	glColor3ub(285, 188, 40);
	glBegin(GL_TRIANGLES);
	glVertex2f(planeX + 70, planeY + 20);
	glVertex2f(planeX + 70, planeY + 35);
	glVertex2f(planeX + 100, planeY + 10);
	glEnd();

	glColor3ub(285, 188, 40);
	glBegin(GL_TRIANGLES);
	glVertex2f(planeX + 70, planeY + -5);
	glVertex2f(planeX + 70, planeY);
	glVertex2f(planeX + 90, planeY + -5);
	glEnd();

	glColor3ub(285, 188, 40);
	glBegin(GL_TRIANGLES);
	glVertex2f(planeX + 50, planeY + -5);
	glVertex2f(planeX + 50, planeY);
	glVertex2f(planeX + 30, planeY + -5);
	glEnd();

	glColor3ub(47, 181, 239);
	glBegin(GL_TRIANGLES);
	glVertex2f(planeX + 70, planeY + 60);
	glVertex2f(planeX + 60, planeY + 76);
	glVertex2f(planeX + 50, planeY + 60);
	glEnd();

	glLineWidth(1);
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(planeX + 100, planeY + 10);
	glVertex2f(planeX + 100, planeY + 20);
	glEnd();

	glLineWidth(1);
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(planeX + 22, planeY + 21);
	glVertex2f(planeX + 22, planeY + 11);
	glEnd();

	glLineWidth(1);
	glColor3ub(47, 181, 239);
	glBegin(GL_LINES);
	glVertex2f(planeX + 60, planeY + 80);
	glVertex2f(planeX + 60, planeY + 60);
	glEnd();

	glLineWidth(1);
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(planeX + 60, planeY - 15);
	glVertex2f(planeX + 60, planeY);
	glEnd();

	glColor3ub(47, 181, 239);
	circle(planeX + 60, planeY, 10);

	glColor3f(0, 0, 0.5);
	if (planeNo+1 == MAX) {
		vprint(planeX + 50, planeY + 22, GLUT_BITMAP_HELVETICA_18, "%d", planeNo+1);
	}
	else {
		vprint(planeX + 55, planeY + 22, GLUT_BITMAP_HELVETICA_18, "%d", planeNo+1);
	}
}

void drawInfo() {
	glColor3ub(50, 70, 250);
	glRectf(-70, 360, 80, 310);
	glColor3ub(255, 211, 0);
	vprint(-40, 340, GLUT_BITMAP_HELVETICA_12, "Berk Onder");
	vprint(-20, 320, GLUT_BITMAP_HELVETICA_12, "21502378");
}

void display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawInfo();
	for (int y = 0; y < MAX*MAX; y += 1) {
		glColor3ub(255, 255, 255);
		circle(random[y].xx, random[y].yy, 1);
	}

	for (j = 0; j < MAX; j++) {
		if (plane[j].Stat) {
			shapePlane(j, plane[j].CoordinateX, plane[j].CoordinateY);
		}
	}
		
	glColor3ub(255, 211, 0);
	vprint(300, -380, GLUT_BITMAP_8_BY_13, "(%d, %d)", globalX, globalY);
	glutSwapBuffers();
}

void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	if (key == 32)
		randPlane = rand() % count;

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onSpecialKeyDown(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;
	}
	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onSpecialKeyUp(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onClick(int button, int stat, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
		plane[count].Stat = true;
		plane[count].CoordinateX = x - winWidth / 2 - 60;
		plane[count].CoordinateY = winHeight / 2 - y - 30;

		for (int k = 0; k < count; k++)
			if (plane[k].CoordinateX >= plane[count].CoordinateX - 60 && plane[k].CoordinateX <= plane[count].CoordinateX + 60 && plane[k].CoordinateY >= plane[count].CoordinateY - 30 && plane[k].CoordinateY <= plane[count].CoordinateY + 30)
				plane[count].Stat = false;

		if (plane[count].Stat)
			count++;
		if (count == MAX)
			plane[count].Stat = false;
	}

	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN) {
		plane[count].CoordinateX = x - winWidth / 2 - 60;
		plane[count].CoordinateY = winHeight / 2 - y - 30;

		for (i = 0; i < count; i++) {
			if (plane[i].CoordinateX >= plane[count].CoordinateX - 35 && plane[i].CoordinateX <= plane[count].CoordinateX + 35 && plane[i].CoordinateY >= plane[count].CoordinateY - 45 && plane[i].CoordinateY <= plane[count].CoordinateY + 45) {
				if (plane[i].Moveable)
					plane[i].Moveable = false;
				else
					plane[i].Moveable = true;
			}
		}
	}

	glutPostRedisplay();
}

void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}

void onMoveDown(int x, int y)
{
	// Write your codes here.
	// to refresh the window it calls display() function   

	glutPostRedisplay();
}

void onMove(int x, int y)
{
	globalX = x - winWidth / 2;
	globalY = winHeight / 2 - y;

	// Write your codes here.
	// to refresh the window it calls display() function

	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v)
{
	for (i = 0; i < count; i++) {
		if (plane[i].Moveable) {
			if (plane[i].CoordinateY <= 420) {
				plane[i].CoordinateY++;

				if (left)
					if(plane[randPlane].Moveable)
						plane[randPlane].CoordinateX--;
				if (right)
					if (plane[randPlane].Moveable)
						plane[randPlane].CoordinateX++;
				if (up)
					if (plane[randPlane].Moveable)
						plane[randPlane].CoordinateY+=2;
			}
			if (plane[i].CoordinateY >= 400) {
				plane[i].CoordinateY = -500;
			}
		}
	}

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);

	glutPostRedisplay();
}
#endif

void Init()
{
	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Homework-1 Animating a Plane by Berk Onder");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	// keyboard registration
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	// mouse registration
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

	for (int e = 0; e < MAX*MAX; e += 1) {
		random[e].xx = rand() % 800 + -400;
		random[e].yy = rand() % 800 + -400;
	}

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();

	glutMainLoop();
}
