/*********
CTIS164 - Template Source Program
----------
STUDENT :BERK ÖNDER
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
#define SIZE 5

#define TIMER_PERIOD  40 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer
#define  DURATION 0

#define D2R 0.0174532

int son = 1;
int total = 0;
int burst = 0;
int topx = -500, topy = 0;
int point = 0;
int twenty = 20;
int decreaser = 0;

bool activeTimer = false;
bool shoot = false;
typedef struct {
	int x, y;
	bool gor = true;
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
void drawGradient(int x1, int y1, int w, int h, float r, float g, float b) {
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex2f(x1, y1);
	glVertex2f(x1 + w, y1);
	glColor3f(r + 0.4, g + 0.4, b + 0.4);
	glVertex2f(x1 + w, y1 - h);
	glVertex2f(x1, y1 - h);
	glEnd();
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x1 + w, y1);
	glVertex2f(x1 + w, y1 - h);
	glVertex2f(x1, y1 - h);
	glEnd();
}

//
// To display onto window using OpenGL commands
//
void display() {
	int i;

	//
	// clear window to black
	//
	/*glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(90, 100, 140);*/
	drawGradient(-500, 400, 1000, 800, 0.5, 0.5, 0.9); //sky

	
	
	

		for (i = 0; i < SIZE; i++)
		{
			if (ufo[i].gor == true)
			{
				//UFO

				glColor3ub(191, 191, 191);
				glBegin(GL_LINES);
				glVertex2f(0 * donme[i] + ufo[i].x, 10 + ufo[i].y);
				glVertex2f(0 * donme[i] + ufo[i].x, 40 + ufo[i].y);
				glEnd();

				//circle0
				glColor3f(100, 200, 2);
				circle(0 * donme[i] + ufo[i].x, 40 + ufo[i].y, 4);
				glEnd();

				//circle1
				glColor3ub(24, 116, 205);
				circle(0 * donme[i] + ufo[i].x, 13 + ufo[i].y, 13);
				glEnd();

				//circle2
				glColor3ub(64, 64, 64);
				circle(-35 * donme[i] + ufo[i].x, -50 + ufo[i].y, 2);
				glEnd();

				//circle3
				glColor3ub(64, 64, 64);
				circle(35 * donme[i] + ufo[i].x, -50 + ufo[i].y, 2);
				glEnd();

				//AYAK
				glColor3ub(99, 99, 99);
				glBegin(GL_TRIANGLES);
				glVertex2f(-20 * donme[i] + ufo[i].x, -30 + ufo[i].y);
				glVertex2f(-10 * donme[i] + ufo[i].x, -30 + ufo[i].y);
				glVertex2f(-35 * donme[i] + ufo[i].x, -50 + ufo[i].y);
				glVertex2f(20 * donme[i] + ufo[i].x, -30 + ufo[i].y);
				glVertex2f(10 * donme[i] + ufo[i].x, -30 + ufo[i].y);
				glVertex2f(35 * donme[i] + ufo[i].x, -50 + ufo[i].y);
				glEnd();

				//GOVDE
				glColor3ub(148, 148, 148);
				glBegin(GL_QUADS);
				glVertex2f(-10 * donme[i] + ufo[i].x, 15 + ufo[i].y);
				glVertex2f(-40 * donme[i] + ufo[i].x, -30 + ufo[i].y);
				glVertex2f(10 * donme[i] + ufo[i].x, 15 + ufo[i].y);
				glVertex2f(40 * donme[i] + ufo[i].x, -30 + ufo[i].y);
				glEnd();
				glColor3ub(148, 148, 148);
				glBegin(GL_TRIANGLES);
				glVertex2f(-40 * donme[i] + ufo[i].x, -30 + ufo[i].y);
				glVertex2f(40 * donme[i] + ufo[i].x, -30 + ufo[i].y);
				glVertex2f(0 * donme[i] + ufo[i].x, 10 + ufo[i].y);
				glEnd();
				//circle5
				glColor3ub(255, 165, 0);
				circle(-20 * donme[i] + ufo[i].x, -20 + ufo[i].y, 3);
				glEnd();
				//circle6
				glColor3ub(147, 112, 219);
				circle(0 * donme[i] + ufo[i].x, -20 + ufo[i].y, 3);
				glEnd();

				//circle7
				glColor3ub(50, 205, 50);
				circle(20 * donme[i] + ufo[i].x, -20 + ufo[i].y, 3);
				glEnd();


				//UFO
			}
		}
		glColor3ub(167, 173, 186);
		glRectf(-500, 320, 500, 400);
		glColor3f(0, 0, 0);
		vprint(-480, 380, GLUT_BITMAP_9_BY_15, "BERK ONDER");
		vprint(-470, 350, GLUT_BITMAP_9_BY_15, "21502378");
		vprint(-120, 380, GLUT_BITMAP_9_BY_15, "PRESS SPACEBAR TO FIRE");
		vprint(-120, 350, GLUT_BITMAP_9_BY_15, "PRESS F1 TO START/RESTART");
		vprint(180, 380, GLUT_BITMAP_9_BY_15, "POINTS");
		vprint(270, 380, GLUT_BITMAP_9_BY_15, "BURST SHIP");
		vprint(370, 380, GLUT_BITMAP_9_BY_15, "TOTAL SHIP");
		vprint(-300, 380, GLUT_BITMAP_9_BY_15, "TIMER");
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2f(175, 372);
		glVertex2f(240, 372);
		glVertex2f(175, 332);
		glVertex2f(240, 332);
		glVertex2f(240, 372);
		glVertex2f(240, 332);
		glVertex2f(175, 372);
		glVertex2f(175, 332);
		glEnd();
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2f(275, 372);
		glVertex2f(340, 372);
		glVertex2f(275, 332);
		glVertex2f(340, 332);
		glVertex2f(340, 372);
		glVertex2f(340, 332);
		glVertex2f(275, 372);
		glVertex2f(275, 332);
		glEnd();
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2f(375, 372);
		glVertex2f(440, 372);
		glVertex2f(375, 332);
		glVertex2f(440, 332);
		glVertex2f(440, 372);
		glVertex2f(440, 332);
		glVertex2f(375, 372);
		glVertex2f(375, 332);
		glEnd();


		glColor3ub(0, 0, 0);
		vprint2(-320, 350, 0.18, "00:%02d:%02d", twenty, decreaser);
		vprint(195, 345, GLUT_BITMAP_TIMES_ROMAN_24, "%d", point);
		vprint(395, 345, GLUT_BITMAP_TIMES_ROMAN_24, "%d", total);
		vprint(300, 345, GLUT_BITMAP_TIMES_ROMAN_24, "%d", burst);

	if (activeTimer)
	{
		glColor3f(1, 0, 0);
		circle(topx, topy+20, 15);
		glColor3f(0, 0, 0);
		glRectf(-500, 0 + topy, -420, 40 + topy);
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex2f(-470, 0 + topy);
		glVertex2f(-470, -35 + topy);
		glVertex2f(-470, -35 + topy);
		glVertex2f(-440, -50 + topy);
		glVertex2f(-470, -35 + topy);
		glVertex2f(-500, -50 + topy);
		glEnd();


	}

	glutSwapBuffers();

}
void bas()
{
	int i, b = 300;
	for (i = 0; i < SIZE; i++)
		donme[i] = 1;
	for (i = 0; i < SIZE; i++)
	{
		ufo[i].x = 740;
		ufo[i].y = b;

	}
	total = 0;
	burst = 0;
	point = 0;
	twenty = 20;
	decreaser = 0;

}
void yeni1()
{
	ufo[0].y = -400;
	donme[0] = 1;
	ufo[0].x = 400;
	ufo[0].gor = true;
	total++;
}
void yeni2()
{
	ufo[1].y = -400;
	donme[1] = 1;
	ufo[1].x = 300;
	ufo[1].gor = true;

	total++;

}
void yeni3()
{
	ufo[2].y = -400;
	donme[2] = 1;
	ufo[2].x = 200;
	ufo[2].gor = true;

	total++;
}
void yeni4()
{
	ufo[3].y = -400;
	donme[3] = 1;
	ufo[3].x = 100;
	ufo[3].gor = true;

	total++;
}
void yeni5()
{
	ufo[4].y = -400;
	donme[4] = 1;
	ufo[4].x = 0;
	ufo[4].gor = true;

	total++;
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (activeTimer)
	{
		if (key == 32 && shoot == false)
		{
			shoot = !shoot;
		}
	}
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
	if (key == GLUT_KEY_F1 && son == 1)
	{
		activeTimer = !activeTimer;

	}
	if (key == GLUT_KEY_F1 && son == 0)
	{
		son = 1;
		bas();
	}
	if(!shoot)
	if (activeTimer)
		if (key == GLUT_KEY_UP)
			topy += 5;
		else if (key == GLUT_KEY_DOWN)
			topy -= 5;

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

#if TIMER_ON == 1
void onTimer(int v) {
	int i;
	srand(time(0));
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	if (activeTimer && son == 1)
	{
		if (twenty > 0 || decreaser != 0)
		{
			if (timeCounter % 20 == 0)
			{
				twenty--;
				decreaser = 100;
			}
			timeCounter++;
			decreaser -= 5;
			if (shoot)
			{
				if (topx < 490)
				{
					topx += 20;
					for (i = 0; i < SIZE; i++)
						if (topx == ufo[i].x && topy <= ufo[i].y + 44 && topy >= ufo[i].y - 50)
						{
							point += 5;
							burst++;
							ufo[i].gor = false;
						}
				}
				else
				{
					topx = -500;
					shoot = !shoot;
				}
			}
			for (i = 0; i < SIZE; i++)
			{
				if (donme[0] == 1)
				{
					if (ufo[0].y - 18 < 530)
					{
						ufo[0].y += rand() % 3 + 1;
						ufo[1].y += rand() % 3 + 1;
						ufo[2].y += rand() % 3 + 1;
						ufo[3].y += rand() % 3 + 1;
						ufo[4].y += rand() % 3 + 1;

					}
					else
						donme[0] = -1;
				}
				if (donme[0] == -1)
				{
					if (ufo[0].y + 18 > -270)
					{
						yeni1();
					}
				}
			}
			for (i = 0; i < SIZE; i++)
			{
				if (donme[1] == 1)
				{
					if (ufo[1].y - 18 < 530)
					{
						ufo[0].y;
						ufo[1].y;
						ufo[2].y;
						ufo[3].y;
						ufo[4].y;
					}
					else
						donme[1] = -1;
				}
				if (donme[1] == -1)
				{
					if (ufo[1].y + 18 > -270)
					{
						yeni2();
					}
				}
				for (i = 0; i < SIZE; i++)
				{
					if (donme[2] == 1)
					{
						if (ufo[2].y - 18 < 530)
						{
							ufo[0].y;
							ufo[1].y;
							ufo[2].y;
							ufo[3].y;
							ufo[4].y;
						}
						else
							donme[2] = -1;
					}
					if (donme[2] == -1)
					{
						if (ufo[2].y + 18 > -270)
						{
							yeni3();
						}
					}
				}
			}
			for (i = 0; i < SIZE; i++)
			{
				if (donme[3] == 1)
				{
					if (ufo[3].y - 18 < 530)
					{
						ufo[0].y;
						ufo[1].y;
						ufo[2].y;
						ufo[3].y;
						ufo[4].y;
					}
					else
						donme[3] = -1;
				}
				if (donme[3] == -1)
				{
					if (ufo[3].y + 18 > -270)
					{
						yeni4();
					}
				}
			}
			for (i = 0; i < SIZE; i++)
			{
				if (donme[4] == 1)
				{
					if (ufo[4].y - 18 < 530)
					{
						ufo[0].y;
						ufo[1].y;
						ufo[2].y;
						ufo[3].y;
						ufo[4].y;
					}
					else
						donme[4] = -1;
				}
				if (donme[4] == -1)
				{
					if (ufo[4].y + 18 > -270)
					{
						yeni5();
					}
				}
			}
			for (i = 0; i < SIZE; i++)
			{
				if (donme[4] == 1)
				{
					if (ufo[4].y - 18 < 530)
					{
						ufo[0].y;
						ufo[1].y;
						ufo[2].y;
						ufo[3].y;
						ufo[4].y;
					}
					else
						donme[4] = -1;
				}
				if (donme[4] == -1)
				{
					if (ufo[4].y + 18 > -270)
					{
						yeni5();
					}
					else
					{

					}
				}
			}

		}
		else
		{
			son = 0;
			activeTimer = !activeTimer;
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
	glutCreateWindow("UFO SHOOTING BY BERK ONDER");

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
