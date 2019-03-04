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
#include "vec.h"

#define WINDOW_WIDTH  700
#define WINDOW_HEIGHT 700

#define TIMER_PERIOD  16 // Period for the timer.
#define TIMER_ON       1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532


/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
bool activetimer = true;
typedef struct {
	float r, g, b;
} renk_t;
int state = 0;

typedef struct {
	vec_t pos;
	renk_t color;
	vec_t vel;
	bool disp;
} light_t;

typedef struct {
	vec_t pos;
	vec_t N;
} vertex_t;

typedef struct {
	renk_t color;
	float angle;
	float hýz;
	bool direction;
	float radius;
} toplar;

toplar top[4];

#define NUM 4

light_t light[4] =
{
	{ { 0, 0 },{ 1, 0, 0 },{ 3,  2 } ,true},
	{ { 200, 0 },{ 0, 1, 0 },{ -2, -1 } ,true},
	{ { -200, 0 },{ 0, 0, 1 },{ 3, -2 } ,true},
	{ { 0, 0 },{ 1, 1, 0 },{ 0 , 0 }, true }
};

renk_t mulColor(float k, renk_t c) {
	renk_t tmp = { k * c.r, k * c.g, k * c.b };
	return tmp;
}

renk_t addColor(renk_t c1, renk_t c2) {
	renk_t tmp = { c1.r + c2.r, c1.g + c2.g, c1.b + c2.b };
	return tmp;
}

// To add distance into calculation
// when distance is 0  => its impact is 1.0
// when distance is 350 => impact is 0.0
// Linear impact of distance on light calculation.
double distanceImpact(double d) {
	return (-1.0 / 350.0) * d + 1.0;
}

renk_t calculateColor(light_t source, vertex_t v) {
	vec_t L = subV(source.pos, v.pos);
	vec_t uL = unitV(L);
	float factor = dotP(uL, v.N) * distanceImpact(magV(L));
	return mulColor(factor, source.color);
}

void Init() {

	// Smoothing shapes
	for (int i = 0; i < 4; i++) {
		top[i].color = { 100 , 100 , 100 };
		top[i].direction = rand() & 1;
		top[i].angle = rand() % 360;
		top[i].hýz = rand() % 2 + 1;
		top[i].radius = rand() % 5 + 18;
	}
	light_t light[4] =
	{
		{ { 0, 0 },{ 1, 0, 0 },{ 3,  2 } ,true },
		{ { 200, 0 },{ 0, 1, 0 },{ -2, -1 } ,true },
		{ { -200, 0 },{ 0, 0, 1 },{ 3, -2 } ,true },
		{ { 0, 0 },{ 1, 1, 0 },{ 0 , 0 }, true }
	};

}
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

void topçiz(toplar planet, float radius) {
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5, 0.5, 0.5);
	float x = radius * cos(planet.angle * D2R), y = radius * sin(planet.angle * D2R);
	glVertex2f(x, y);

	for (int j = 0; j <= 100; j++) {
		planet.angle = 2 * PI*j / 100;

		vec_t v = { x + planet.radius*cos(planet.angle), y + planet.radius*sin(planet.angle) };
		vertex_t P = { { v.x, v.y } };

		P.N = unitV(subV({ v.x, v.y }, { x, y }));

		renk_t res = { 0, 0, 0 };
		for (int k = 0; k < NUM; k++) {
			if (light[k].disp == true)
				res = addColor(res, calculateColor(light[k], P));
		}

		glColor3f(res.r, res.g, res.b);
		glVertex2f(v.x, v.y);
	}
	glEnd();

}
//
// To display onto window using OpenGL commands
//
void display() {

	//
	// clear window to black
	//
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// light source 
	for (int i = 0; i < 3; i++) {
		if (light[i].disp == true)
		{
			glColor3f(light[i].color.r, light[i].color.g, light[i].color.b);
			circle(light[i].pos.x, light[i].pos.y, 10);
		}
		if(light[3].disp==true)
		{
			glColor3f(light[3].color.r, light[3].color.g, light[3].color.b);
			circle(light[3].pos.x, light[3].pos.y, 30);
		}

	}

	for (int x = -400; x <= 400; x++) {
		vertex_t P = { { x, -100 },{ 0, 1 } };

		renk_t res = { 0, 0, 0 };
		for (int i = 0; i < NUM; i++) {
			res = addColor(res, calculateColor(light[i], P));
		}
		
	}

	for (int x = -400; x <= 400; x++) {
		vertex_t P = { { x, -100 },{ 0, 1 } };
		renk_t res = { 0, 0, 0 };
	}
	float radius = 200;
	for (int i = 0; i < 3; i++) {
		topçiz(top[i], radius);
		radius += 40;
	}
	glColor3ub(167, 173, 186);
	glRectf(-500, 320, 500, 400);
	glColor3f(1, 1, 1);
	if (light[0].disp)
		vprint(-340, 330, GLUT_BITMAP_9_BY_15, "F1(RED):ON");
	else
		vprint(-340, 330, GLUT_BITMAP_9_BY_15, "F1(RED):OFF");
	if (light[1].disp)
		vprint(-240, 330, GLUT_BITMAP_9_BY_15, "F2(GREEN):ON");
	else
		vprint(-240, 330, GLUT_BITMAP_9_BY_15, "F2(GREEN):OFF");
	if (light[2].disp)
		vprint(-120, 330, GLUT_BITMAP_9_BY_15, "F3(BLUE):ON");
	else
		vprint(-120, 330, GLUT_BITMAP_9_BY_15, "F3(BLUE):OFF");
	if (light[3].disp)
		vprint(-10, 330, GLUT_BITMAP_9_BY_15, "F4(SUN):ON");
	else
		vprint(-10, 330, GLUT_BITMAP_9_BY_15, "F4(SUN):OFF");
	if (activetimer)
		vprint(100, 330, GLUT_BITMAP_9_BY_15, "F5:START:ON");
	else
		vprint(100, 330, GLUT_BITMAP_9_BY_15, "F5:START:OFF");
	vprint(210, 330, GLUT_BITMAP_9_BY_15, "F6:RESTART");

	glutSwapBuffers();

}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
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
	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;
	}

	
	if (key == GLUT_KEY_F3)
		light[2].disp = !light[2].disp;
	if (key == GLUT_KEY_F2)
		light[1].disp = !light[1].disp;
	if (key == GLUT_KEY_F1)
		light[0].disp = !light[0].disp;
	if (key == GLUT_KEY_F4)
		light[3].disp = !light[3].disp;
	if (key == GLUT_KEY_F5)
		activetimer = !activetimer;
	if (key == GLUT_KEY_F6)
		Init();

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

void onMove(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.
	if (activetimer)
	{
		for (int i = 0; i < 4; i++)
			top[i].angle += 1;

		for (int i = 0; i < NUM; i++) {
			light[i].pos = addV(light[i].pos, light[i].vel);

			// Reflection from Walls.
			if (light[i].pos.x > 340 || light[i].pos.x < -340) {
				light[i].vel.x *= -1;
			}

			if (light[i].pos.y > 340 || light[i].pos.y < -340) {
				light[i].vel.y *= -1;

			}
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
	glutCreateWindow("Berk ÖNDER - Homework #4");

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

	Init();

	glutMainLoop();
}
