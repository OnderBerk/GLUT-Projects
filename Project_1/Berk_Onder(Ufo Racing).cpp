/*********
CTIS164 - Template Source Program
----------
STUDENT :BERK ÖNDER
SECTION :02
HOMEWORK:Racing Objects
----------
*********/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800
#define SIZE 4

#define TIMER_PERIOD  40 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer
#define  DURATION 0

#define D2R 0.0174532

int son = 1;

bool activeTimer = false;
typedef struct {
	int x, y;
}ufo_t;
ufo_t ufo[SIZE];
int donme[SIZE] = { 1,1,1,1 };
/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int timeCounter = 0;
int  winWidth, winHeight; // current Window width and height

						  //
						  // to draw circle, center at (x,y)
						  // radius r
						  //
int win = 0;
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
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
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
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, char *string, ...) {
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
	for (i = 0; i<len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

//
// To display onto window using OpenGL commands
//
void display() {
	int i;

	//
	// clear window to black
	//
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(90, 100, 140);

	glColor3ub(167, 173, 186);
	glRectf(-500, 320, 500, 400);
	glColor3ub(190, 190, 190);
	glRectf(410, 330, 345, 370);
	glColor3f(0, 0, 0);
	vprint(-480, 380, GLUT_BITMAP_9_BY_15, "BERK ONDER");
	vprint(-470, 350, GLUT_BITMAP_9_BY_15, "21502378");
	vprint(-120, 380, GLUT_BITMAP_9_BY_15, " - WELCOME TO UFO RACING -");
	if (son == 1)
		vprint(-120, 350, GLUT_BITMAP_9_BY_15, "PRESS SPACEBAR TO START/STOP");
	else
		vprint(-80, 350, GLUT_BITMAP_9_BY_15, "PRESS F1 TO RESTART");
	vprint(350, 380, GLUT_BITMAP_9_BY_15, "WINNER");
	vprint(-300, 380, GLUT_BITMAP_9_BY_15, "TIMER");
	glLineWidth(3);
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(345, 372);
	glVertex2f(410, 372);
	glVertex2f(345, 332);
	glVertex2f(410, 332);
	glVertex2f(410, 372);
	glVertex2f(410, 332);
	glVertex2f(345, 372);
	glVertex2f(345, 332);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(500, 140);
	glVertex2f(-500, 140);
	glVertex2f(500, -40);
	glVertex2f(-500, -40);
	glVertex2f(500, -220);
	glVertex2f(-500, -220);
	glEnd();
	glColor3ub(0, 0, 0);
	vprint2(-320, 350, 0.18, "00:%d:%02d", timeCounter / 60, timeCounter % 60);
	vprint(365, 345, GLUT_BITMAP_TIMES_ROMAN_24, "0%d", win + 1);

	for (i = 0; i < SIZE; i++)
	{
		//UFO



		//Silah topu
		glColor3f(255, 0, 0);
		circle(77 * donme[i] + ufo[i].x, 5 + ufo[i].y, 5);

		//Silah
		glColor3ub(150, 150, 150);
		glRectf(75 * donme[i] + ufo[i].x, 0 + ufo[i].y, 34 * donme[i] + ufo[i].x, 10 + ufo[i].y);

		glColor3ub(191, 191, 191);
		glBegin(GL_LINES);
		glVertex2f(0 * donme[i] + ufo[i].x, 43 + ufo[i].y);
		glVertex2f(0 * donme[i] + ufo[i].x, 56 + ufo[i].y);
		glEnd();

		//circle0
		glColor3f(100, 200, 2);
		circle(0 * donme[i] + ufo[i].x, 56 + ufo[i].y, 5);
		glEnd();

		//circle1
		glColor3ub(24, 116, 205);
		circle(0 * donme[i] + ufo[i].x, 13 + ufo[i].y, 30);
		glEnd();

		//circle2
		glColor3ub(64, 64, 64);
		circle(-55 * donme[i] + ufo[i].x, -50 + ufo[i].y, 3);
		glEnd();

		//circle3
		glColor3ub(64, 64, 64);
		circle(55 * donme[i] + ufo[i].x, -50 + ufo[i].y, 3);
		glEnd();

		//AYAK
		glColor3ub(99, 99, 99);
		glBegin(GL_TRIANGLES);
		glVertex2f(-40 * donme[i] + ufo[i].x, -30 + ufo[i].y);
		glVertex2f(-30 * donme[i] + ufo[i].x, -30 + ufo[i].y);
		glVertex2f(-55 * donme[i] + ufo[i].x, -50 + ufo[i].y);
		glVertex2f(40 * donme[i] + ufo[i].x, -30 + ufo[i].y);
		glVertex2f(30 * donme[i] + ufo[i].x, -30 + ufo[i].y);
		glVertex2f(55 * donme[i] + ufo[i].x, -50 + ufo[i].y);
		glEnd();

		//GOVDE
		glColor3ub(148, 148, 148);
		glBegin(GL_QUADS);
		glVertex2f(-30 * donme[i] + ufo[i].x, 15 + ufo[i].y);
		glVertex2f(-60 * donme[i] + ufo[i].x, -30 + ufo[i].y);
		glVertex2f(30 * donme[i] + ufo[i].x, 15 + ufo[i].y);
		glVertex2f(60 * donme[i] + ufo[i].x, -30 + ufo[i].y);
		glEnd();
		glColor3ub(148, 148, 148);
		glBegin(GL_TRIANGLES);
		glVertex2f(-60 * donme[i] + ufo[i].x, -30 + ufo[i].y);
		glVertex2f(60 * donme[i] + ufo[i].x, -30 + ufo[i].y);
		glVertex2f(0 * donme[i] + ufo[i].x, 10 + ufo[i].y);
		glEnd();
		//circle4
		glColor3f(255, 0, 0);
		circle(-40 * donme[i] + ufo[i].x, -20 + ufo[i].y, 6);
		glEnd();
		//circle5
		glColor3ub(255, 165, 0);
		circle(-20 * donme[i] + ufo[i].x, -20 + ufo[i].y, 6);
		glEnd();
		//circle6
		glColor3ub(147, 112, 219);
		circle(0 * donme[i] + ufo[i].x, -20 + ufo[i].y, 6);
		glEnd();

		//circle7
		glColor3ub(50, 205, 50);
		circle(20 * donme[i] + ufo[i].x, -20 + ufo[i].y, 6);
		glEnd();

		//circle8
		glColor3f(0, 0, 0);
		circle(40 * donme[i] + ufo[i].x, -20 + ufo[i].y, 6);
		glEnd();
		glColor3f(1, 1, 1);
		vprint(-5 * donme[i] + ufo[i].x, -5 + ufo[i].y, GLUT_BITMAP_TIMES_ROMAN_24, "%d", i + 1);
		//UFO

	}

	glutSwapBuffers();

}
void bas() 
{
	int i, b = 226;
	timeCounter = 0;
	win = 0;
	for (i = 0; i < SIZE; i++)
		donme[i] = 1;
	for (i = 0; i < SIZE; i++)
	{
		ufo[i].x = -440;
		ufo[i].y = b;

		b -= 180;
	}

}
//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 32 && son == 1)
		activeTimer = !activeTimer;

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
	// Write your codes here.
	if (key == GLUT_KEY_F1 && son == 0)
	{
		bas();
		son = 1;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
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

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
	// Write your codes here.



	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
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

void onMoveDown(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function   
	glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function
	glutPostRedisplay();
}
int fwin()
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		if (donme[i] == 1)
		{
			if (donme[win] == 1)
				if (ufo[i].x > ufo[win].x)
					win = i;
		}
		else
		{
			if (donme[win] == 1)
				win = i;
			else if (ufo[i].x < ufo[win].x)
				win = i;
		}
	}
	return(win);
}
#if TIMER_ON == 1
void onTimer(int v) {
	int i;
	srand(time(0));
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	if (activeTimer && son == 1)
	{
		timeCounter += 3;
		for (i = 0; i < SIZE; i++)
		{
			if (donme[i] == 1)
			{
				if (ufo[i].x - 18 < 400)
				{
					ufo[i].x += rand() % 5 + 1;

				}
				else
					donme[i] = -1;
			}
			if (donme[i] == -1)
			{
				if (ufo[i].x + 18 > -400)
				{
					ufo[i].x -= rand() % 5 + 1;
				}
				else
				{
					activeTimer = false;
					son = 0;
				}
			}
			fwin();
		}
	}



	// to refresh the window it calls display() function
	glutPostRedisplay(); // display()

}
#endif



void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("UFO RACING");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	//
	// keyboard registration
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//
	// mouse registration
	//
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	bas();

	glutMainLoop();
}