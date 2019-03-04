/*********
CTIS164 - Template Source Program
----------
STUDENT :Berk ÖNDER

----------
PROBLEMS: When the program finish, it is not returning to the initial side.
----------
ADDITIONAL FEATURES:
*********/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  20 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532
#define SIZE 3
/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
float angle = 0;
bool ates = false;
int state = 0;
typedef struct
{
	float x, y, angle;
}top_t;
top_t top;

typedef struct
{
	float x, y, angle;

}silah_t;
silah_t silah;
typedef struct
{
	float y, x;
}cent_t;
typedef struct{
	int r, g, b;
}col_t;
typedef struct{
	col_t renk;
	float angle;
	cent_t cen;
	int hýz, yön, r;
	int gör = true;
}þek_t;

þek_t þekil[SIZE];

int  winWidth, winHeight; // current Window width and height

						  //
						  // to draw circle, center at (x,y)
						  // radius r
						  //
void tepenok(silah_t A, silah_t vur, double angle) {
	double xp = (A.x * cos(angle) - A.y * sin(angle)) + vur.x;
	double yp = (A.x * sin(angle) + A.y * cos(angle)) + vur.y;
	glVertex2d(xp, yp);
}

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
void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int i;
	int ilk = 170;
	silah.x = top.x = 0;
	silah.y = top.y = 0;
	for (i = 0; i<SIZE; i++)
	{

		þekil[i].r = rand() % 20 + 10;
		þekil[i].yön = rand() % 2;
		þekil[i].angle = rand() % 360;
		þekil[i].cen.x = ilk;
		þekil[i].cen.y = ilk;
		þekil[i].hýz = rand() % 2 + 1;
		þekil[i].gör = 1;
		þekil[i].renk.r = rand() % 256;
		þekil[i].renk.g = rand() % 256;
		þekil[i].renk.b = rand() % 256;
		ilk += 100;
	}
}
void silahçiz()
{
	glColor3f(255, 0, 0);
	glBegin(GL_LINES);
	tepenok({ 50,0 }, { 0,0 }, silah.angle*D2R);
	tepenok({ 0,20 }, { 0,0 }, silah.angle*D2R);
	tepenok({ 0,-20 }, { 0,0 }, silah.angle*D2R);
	tepenok({ 50,0 }, { 0,0 }, silah.angle*D2R);
	tepenok({ 0,40 }, { 0,0 }, silah.angle*D2R);
	tepenok({ 0,-40 }, { 0,0 }, silah.angle*D2R);
	glEnd();
}
void topçiz()
{
	glColor3f(165 ,42 ,42);
	if (ates)
		circle(top.x, top.y, 12);

	if (top.x >500 || top.x <-500 || top.y >500 || top.y < -500)
		ates = !ates;

}

//
// To display onto window using OpenGL commands
//


//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void Balls()
{

	if (state == 1)
	{
		int i;
		for (i = 0; i<SIZE; i++)
		{
			if (þekil[i].gör == 1)
			{
				glColor3ub(þekil[i].renk.r, þekil[i].renk.g, þekil[i].renk.b);
				circle(þekil[i].cen.x*cos(þekil[i].angle* D2R), þekil[i].cen.y*sin(þekil[i].angle*D2R), þekil[i].r);
			}
		}

	}
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
	if (state == 0)
	{
		if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN)
		{
			state = 1;
		}
	}

	else if (state == 1)
		if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN)
		{
			if (ates == false)
			{
				ates = !ates;
				top.angle = silah.angle;
				top.x = silah.x;
				top.y = silah.y;

			}
		}



	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void display() {
	//
	// clear window to black
	//
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	Balls();
	silahçiz();
	topçiz();
	vprint(-390, 350, GLUT_BITMAP_9_BY_15, "Berk ONDER");
	vprint(-390, 330, GLUT_BITMAP_9_BY_15, "21502378");
	//circles
	circle_wire(0, 0, 170);
	circle_wire(0, 0, 270);
	circle_wire(0, 0, 370);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	// line 1
	glVertex2f(0, 800);
	glVertex2f(0, -400);
	// line 2
	glColor3f(1, 1, 1);
	glVertex2f(-500, 0);
	glVertex2f(500, 0);
	glEnd();
	glColor3f(1, 1, 1);
	if (state == 0)
	{
		glColor3f(1, 1, 1);
		vprint(-60, -100, GLUT_BITMAP_9_BY_15, "Click to play");
	}





	glutSwapBuffers();
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
	silah.angle = atan2(winHeight / 2 - y, x - winWidth / 2) * 180 / PI;



	// to refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
	int i;
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.
	if (state == 1)// If the game state is and mouse clicked
	{
		for (i = 0; i < SIZE; i++)
		{
			if (þekil[i].yön == 1)
			{
				þekil[i].angle += þekil[i].hýz;
				if (þekil[i].angle > 360)
					þekil[i].angle -= 360;
			}
			else
			{
				þekil[i].angle -= þekil[i].hýz;
				if (þekil[i].angle < 0)
					þekil[i].angle += 360;
			}
		}

		if (ates)
		{
			top.x += 10 * cos(top.angle*D2R);
			top.y += 10 * sin(top.angle*D2R);

			for (i = 0; i<SIZE; i++)
			{
				if (þekil[i].gör == 1)
				{
					float collision = sqrt((top.x - þekil[i].cen.x*cos(þekil[i].angle* D2R)) * (top.x - þekil[i].cen.x*cos(þekil[i].angle* D2R)) + (top.y - þekil[i].cen.y*sin(þekil[i].angle*D2R)) * (top.y - þekil[i].cen.y*sin(þekil[i].angle*D2R)));

					if (collision <= þekil[i].r + 10)
					{
						þekil[i].gör = false;
						int count = 0;
						count++;
						if (count == 3)
							Init();
					}
				}
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
	//glutInitWindowPosition(100, 100);
	glutCreateWindow("BERK ÖNDER HOMEWORK3 ROTATING SHAPES");

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
