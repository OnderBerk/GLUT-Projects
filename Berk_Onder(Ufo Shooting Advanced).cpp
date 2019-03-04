/*********
 CTIS164 - Template Source Program
 ----------
 STUDENT : Berk Onder
 ----------
 
- If you press the spacebar there is a fire effect of gun
- While bullet is on the screen "Reloading" is on show
 *********/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define MAX 5

#define TIMER_PERIOD  1000 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */

bool activeTimer=false;
bool fire= false; // checks whether the weapon is fired or not
int  winWidth, winHeight; // current Window width and height
int wX=-400, wY=0; //Weapon's init coordinate
int state=1; // Game state
int counter;
int timer;//init time
int minus;//timer decreaser
int check; // fire
int bX=-333, bY=0; // coordinates of the bullet
int randomNum[MAX]; // random +x value for balloons
int forfire;//for gun fire
int totalPts; // total Point
int lastPt; //last point
int blowedBallons; // number of blowed out ballons
int totalOfBalloons; // number of the balloons sended to sky
int checkNum[MAX]={0,0,0,0,0}; //checks whether the balloon has random value
int isVisible[MAX]={1,1,1,1,1}; // checks whether the balloons are shooted or reached to top of the screen

typedef struct {
    int baX, baY;
}balloons_t;

balloons_t balloons[MAX];

//
// to draw circle, center at (x,y)
// radius r
//
void circle( int x, int y, int r )
{
#define PI 3.1415
    float angle ;
    glBegin( GL_POLYGON ) ;
    for ( int i = 0 ; i < 100 ; i++ )
    {
        angle = 2*PI*i/100;
        glVertex2f( x+r*cos(angle), y+r*sin(angle)) ;
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

void print(int x, int y, char *string, void *font )
{
    int len, i ;
    
    glRasterPos2f( x, y );
    len = (int) strlen( string );
    for ( i =0; i<len; i++ )
    {
        glutBitmapCharacter( font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, char *string , ...)
{
    va_list ap;
    va_start ( ap, string );
    char str[1024] ;
    vsprintf_s( str, string, ap ) ;
    va_end(ap) ;
    
    int len, i ;
    glRasterPos2f( x, y );
    len = (int) strlen( str );
    for ( i =0; i<len; i++ )
    {
        glutBitmapCharacter( font, str[i]);
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

void Init() {
    //time initial values
    timer=20;
    counter = 0;
    minus = 0;
    state = 1;
    fire=false;
    activeTimer=false;
    
    //weapon's init coordinate
    wY=0;
    wX=-400;
    
    //Game infos
    totalPts=0;
    lastPt=0;
    blowedBallons=0;
    totalOfBalloons=0;
    
    //ballons initial values
    int i;
    int a=-320;
    for(i=0; i<MAX; i++)
    {
        balloons[i].baX=-105;
        balloons[i].baY=a;
        a-=135;
        checkNum[i]=0;
        isVisible[i]=1;
    }
}
void drawBalloons()
{
    int i;
    
    for(i=0; i<MAX; i++)
    {
        if(isVisible[i]==1)
        {
            glColor3f(0.8, 0.8, 0);
            circle(balloons[i].baX+70, balloons[i].baY+15, 35);
            glColor3f(0.8, 0.8, 0);
            glBegin(GL_TRIANGLES);
            glVertex2f(balloons[i].baX+47, balloons[i].baY-12);
            glVertex2f(balloons[i].baX+93, balloons[i].baY-12);
            glVertex2f(balloons[i].baX+70, balloons[i].baY-30);
            glEnd();
            
            //Skirt of the ballob
            glColor3f(0.7, 0.7, 0);
            glRectf(balloons[i].baX+56, balloons[i].baY-20, balloons[i].baX+84, balloons[i].baY-40);
            
            //Cords of the balloon
            glColor3f(0, 0, 0);
            glBegin(GL_LINES);
            glVertex2f(balloons[i].baX+57, balloons[i].baY-40);
            glVertex2f(balloons[i].baX+67, balloons[i].baY-55);
            glVertex2f(balloons[i].baX+83, balloons[i].baY-40);
            glVertex2f(balloons[i].baX+73, balloons[i].baY-55);
            glEnd();
            
            //Wicker Basket
            glColor3f(0, 0, 0);
            glBegin(GL_LINES);
            glVertex2f(balloons[i].baX+62, balloons[i].baY-52);
            glVertex2f(balloons[i].baX+62, balloons[i].baY-65);
            glVertex2f(balloons[i].baX+78, balloons[i].baY-52);
            glVertex2f(balloons[i].baX+78, balloons[i].baY-65);
            glVertex2f(balloons[i].baX+62, balloons[i].baY-52);
            glVertex2f(balloons[i].baX+66, balloons[i].baY-52);
            glVertex2f(balloons[i].baX+74, balloons[i].baY-52);
            glVertex2f(balloons[i].baX+78, balloons[i].baY-52);
            glEnd();
            glColor3f(0,0.2,0.9);
            glRectf(balloons[i].baX+60, balloons[i].baY-65, balloons[i].baX+80, balloons[i].baY-80);
            
            //burners
            if(counter % 3== 0)
            {
                glColor3f(1, 0, 0);
                glRectf(balloons[i].baX+66,balloons[i].baY-48,balloons[i].baX+74, balloons[i].baY-58);
                glColor3f(1, 0.6, 0);
                glRectf(balloons[i].baX+68, balloons[i].baY-58, balloons[i].baX+72, balloons[i].baY-53);
                glColor3f(1, 0, 0);
                glBegin(GL_TRIANGLES);
                glVertex2f(balloons[i].baX+66, balloons[i].baY-48);
                glVertex2f(balloons[i].baX+74, balloons[i].baY-48);
                glVertex2f(balloons[i].baX+70, balloons[i].baY-44);
                glColor3f(1, 0.6, 0);
                glVertex2f(balloons[i].baX+68, balloons[i].baY-53);
                glVertex2f(balloons[i].baX+72, balloons[i].baY-53);
                glVertex2f(balloons[i].baX+70, balloons[i].baY-48);
                glEnd();
            }
            glColor3f(0, 0, 0);
            glRectf(balloons[i].baX+65, balloons[i].baY-58, balloons[i].baX+75, balloons[i].baY-54);
        }
    }
    
}
void drawGradient(int x1, int y1, int w, int h,  float r, float g, float b) {
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex2f(x1, y1);
    glVertex2f(x1+w, y1);
    glColor3f(r+0.4, g+0.4, b+0.4);
    glVertex2f(x1+w, y1-h);
    glVertex2f(x1, y1-h);
    glEnd();
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x1+w, y1);
    glVertex2f(x1+w, y1-h);
    glVertex2f(x1, y1-h);
    glEnd();
}
void drawBackground() {
    drawGradient(-400, 300, 800, 600, 0.3, 0.3, 1 );
}
void drawBullets()
{
    if(fire) // If spacebard draw the bullet
    {
        glColor3f(0.8, 0.6, 0);
        glRectf(bX, bY+2, bX+25, bY-2);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2f(bX+25, bY+2);
        glVertex2f(bX+25, bY-2);
        glVertex2f(bX+30, bY);
        glEnd();
        
        //Gun fire when shot
        if(forfire+3>=counter)
        {
            glColor3f(1, 0, 0);
            glRectf(wX+80, wY+2, wX+90 ,wY-2);
            glRectf(wX+80, wY+10, wX+84, wY+2);
            glRectf(wX+80, wY-2, wX+84, wY-10);
            glColor3f(1, 0.6, 0);
            glRectf(wX+80, wY+1, wX+88, wY-1);
            glRectf(wX+81, wY+8, wX+83, wY+1);
            glRectf(wX+81, wY-1, wX+83, wY-9);
        }
    }
}

void drawWeapon()
{
    glColor3f(0, 0.1, 0.3);
    //Stock of the Weapon
    glBegin(GL_TRIANGLES);
    glVertex2f(wX, wY+4);
    glVertex2f(wX, wY-12);
    glVertex2f(wX+18, wY+4);
    glEnd();
    glRectf(wX+10, wY+3, wX+25, wY-3);
    
   
    //Receiver of the Weapon
    glColor3f(0, 0.1, 0.3);
    glRectf(wX+25, wY+4, wX+70, wY-4);
    
    //Suppressor of the Weapon
    glRectf(wX+70, wY+2, wX+80, wY-2);
    
    //Grip of the Weapon
    glBegin(GL_QUADS);
    glVertex2f(wX+27, wY-15);
    glVertex2f(wX+32, wY-4);
    glVertex2f(wX+37, wY-4);
    glVertex2f(wX+34, wY-17);
    
    //Magazine of the Weapon
    
    glBegin(GL_QUADS);
    glVertex2f(wX+43, wY-21);
    glVertex2f(wX+42, wY-4);
    glVertex2f(wX+50, wY-4);
    glVertex2f(wX+51, wY-18);
    glEnd();
    
    //Trigger and Trigger Guard
    glBegin(GL_LINES);
    glVertex2f(wX+32, wY-8);
    glVertex2f(wX+42, wY-8);
    glVertex2f(wX+39, wY-4);
    glVertex2f(wX+39, wY-6);
    glEnd();
    
    //Rear Sight Drum
    glBegin(GL_QUADS);
    glVertex2f(wX+30, wY+4);
    glVertex2f(wX+32, wY+8);
    glVertex2f(wX+35, wY+8);
    glVertex2f(wX+37, wY+4);
    glEnd();
    
    //Triangle of the Weapon
    glBegin(GL_LINES);
    glVertex2f(wX+68, wY+10);
    glVertex2f(wX+68, wY+4);
    glVertex2f(wX+63, wY+4);
    glVertex2f(wX+68, wY+10);
    glEnd();
}
void display() {
    
    //
    // clear window to black
    //
    glClearColor( 0.8, 0.8 , 0.8, 0 );
    glClear( GL_COLOR_BUFFER_BIT );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
  

    drawBackground();
    drawBalloons();
    drawBullets();
    
    //Menu
    glColor4f(0, 0, 0, 1);
    glRectf(304, 300, 400, -300);
    glRectf(-400, -268, 400, -300);
    glColor3f(1, 1, 1);
    vprint(317, 275, GLUT_BITMAP_HELVETICA_12, "REMAINING");
    vprint(338, 263, GLUT_BITMAP_HELVETICA_12, "TIME");
    glColor3f(0 ,1, 0);
    
    if(minus==100)
        vprint(327, 241, GLUT_BITMAP_8_BY_13, "%02d:%02d",timer, 99);
    else
        vprint(327, 241, GLUT_BITMAP_8_BY_13, "%02d:%02d",timer, minus);
    
    glColor3f(1, 1, 1);
    vprint(338, 185, GLUT_BITMAP_HELVETICA_12, "NUM-Of");
    vprint(326, 173, GLUT_BITMAP_HELVETICA_12, "BALLOONS");
    glColor3f(1, 1, 0);
    vprint(348, 155, GLUT_BITMAP_8_BY_13, "%02d",totalOfBalloons);
    
    glColor3f(1, 1, 1);
    vprint(338, 60, GLUT_BITMAP_HELVETICA_12, "BLOWED");
    vprint(326, 47, GLUT_BITMAP_HELVETICA_12, "BALLOONS");
    glColor3f(1, 1, 0);
    vprint(348, 25, GLUT_BITMAP_8_BY_13, "%02d", blowedBallons);
    
    glColor3f(1, 1, 1);
    vprint(338, -60, GLUT_BITMAP_HELVETICA_12, "LAST");
    vprint(332, -72, GLUT_BITMAP_HELVETICA_12, "POINTS");
    glColor3f(1, 1, 0);
    vprint(347, -94, GLUT_BITMAP_8_BY_13, "%02d",lastPt);
    
    glColor3f(1, 1, 1);
    vprint(338, -200, GLUT_BITMAP_HELVETICA_12, "TOTAL");
    vprint(334, -212, GLUT_BITMAP_HELVETICA_12, "POINTS");
    glColor3f(1, 0, 0);
    vprint(349, -234, GLUT_BITMAP_8_BY_13, "%02d",totalPts);
    
    glColor3f(1, 1, 0);
    vprint(-180, -284, GLUT_BITMAP_8_BY_13, "<Spacebar> Fire, <F1> Pause/Restart");

    drawWeapon();
    
    
    if(fire) // If spacebar write to screen
    {
        glColor3f(0.7, 0.2, 0.1);
        vprint(wX+5, wY+14, GLUT_BITMAP_HELVETICA_12, "Reloading...");
    }
    glutSwapBuffers();
    
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y )
{
    if(state==1 && activeTimer)
        if(key == ' ' && fire == false)
            if(bX<300)
            {
                forfire=counter;
                fire = !fire;
                bX=wX+50;
                bY=wY;
            }
    
    // to refresh the window it calls display() function
    glutPostRedisplay() ;
}

void onKeyUp(unsigned char key, int x, int y )
{
    // exit when ESC is pressed.
    if ( key == 27 )
        exit(0);
    
    // to refresh the window it calls display() function
    glutPostRedisplay() ;
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown( int key, int x, int y )
{
    // Write your codes here.
    if(state == 1 && key == GLUT_KEY_F1)
        activeTimer = !activeTimer;
        
    if (activeTimer)
    {
        
    switch (key) {
        case GLUT_KEY_UP:
            if(wY+10 <=225)
                wY+=15;
            break;
                
        case GLUT_KEY_DOWN:
            if(wY-12 >= -225)
                wY-=15;
            break;
    }
    }
    if (state == 0 && key == GLUT_KEY_F1)
    {
        state = 1;
        Init();
    }

    
    // to refresh the window it calls display() function
    glutPostRedisplay() ;
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp( int key, int x, int y )
{
    // Write your codes here.
    
    
    // to refresh the window it calls display() function
    glutPostRedisplay() ;
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick( int button, int stat, int x, int y )
{
    // Write your codes here.
    
    
    
    // to refresh the window it calls display() function
    glutPostRedisplay() ;
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize( int w, int h )
{
    winWidth = w;
    winHeight = h;
    glViewport( 0, 0, w, h ) ;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( -w/2, w/2, -h/2, h/2, -1, 1);
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown( int x, int y ) {
    // Write your codes here.
    
    
    
    // to refresh the window it calls display() function
    glutPostRedisplay() ;
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove( int x, int y ) {
    // Write your codes here.
    
    
    
    // to refresh the window it calls display() function
    glutPostRedisplay() ;
}

#if TIMER_ON == 1
void onTimer( int v ) {
    
    int i;
    glutTimerFunc( TIMER_PERIOD/20, onTimer, 0 ) ;
    
    if(state==1 && activeTimer) // If the game state is and F1 pressed
    {
        if(timer>0 || minus !=0) // If timer > 0
        {
     
            //Timer infos
            if(counter%20==0)
            {
                timer--;
                minus=100;
            }
            counter++;
            minus-=5;
            
            //Increase 1 the total num of balloons when y axis=-320
            for(i=0; i<MAX; i++)
                if(balloons[i].baY==-320)
                    totalOfBalloons++;
        
            //If random x didnt assign to balloons before
            for(i=0; i<MAX; i++)
                if(checkNum[i] == 0)
                {
                    randomNum[i] = rand()%280;
                    balloons[i].baX+=randomNum[i];
                    checkNum[i]= 1;
                }
            
            
            //Check the following axis and do the followings
            for(i=0; i<MAX; i++)
            {
                if(balloons[i].baY-48 <=300)
                {
                    balloons[i].baY+=5;
                }
                else
                {
                    // If it reached to the top of the screen
                    checkNum[i]=0;
                    balloons[i].baY=-320;
                    balloons[i].baX= -105;
                    isVisible[i]=1; // make it visible again
                }
            }
            
            //When spacebar is pressed
            if(fire)
            {
                //If the x axis of the bullet below it
                if(bX<=280)
                {
                    bX+=19; // Increase the x axis
                    for(i=0; i<MAX;i++)
                        if(isVisible[i]==1) //Check whether the balloons are on show
                            if(bX > balloons[i].baX+60 &&bX < balloons[i].baX+80 && bY < balloons[i].baY+50 &&bY > balloons[i].baY-80) // If the coordinates of the bullets and balloons crashed
                            {
                                blowedBallons++; // Increase the number of blowed balloons
                                
                                if(bY < balloons[i].baY+50 &&bY > balloons[i].baY+35) //Top of the balloon
                                    lastPt=5;
                                else if(bY <= balloons[i].baY+35 &&bY > balloons[i].baY-20) //Center of the balloon
                                    lastPt=6;
                                else if(bY <= balloons[i].baY-20 &&bY >=balloons[i].baY-40) //Skirt of the balloon
                                    lastPt=3;
                                else if(bY <= balloons[i].baY-40 &&bY > balloons[i].baY-55) //Cords of the balloon
                                    lastPt=4;
                                else if(bY <= balloons[i].baY-55 &&bY >= balloons[i].baY-65) //Irons of the wicker basket
                                    lastPt=1;
                                else //Wicker basket
                                    lastPt=2;
                                
                                totalPts+=lastPt;
                                isVisible[i] = 0; // Make it invisible
                            }
                            
                    
                }
                //If the x axis of the bullet below it
                else if(bX > 280)
                {
                    //make the coordinates of the bullet equals to weapon
                    bX=wX+50;
                    bY=wY;
                    fire = !fire; // stop the fire
                }
            }
            
        }
        else // If the timer reached to 0
        {
            
            activeTimer = !activeTimer; // stop the onTimer func
            state=0; // make the game state 0
        }
    }

    
    
    // to refresh the window it calls display() function
    glutPostRedisplay() ; // display()
    
}
#endif



void main( int argc, char *argv[] ) {
    glutInit(&argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow( "HW-2:\"Blowing out the Balloons\" by Berk Onder" ) ;
    
    
     srand(time(0));
    glutDisplayFunc( display ) ;
    glutReshapeFunc( onResize );
    
    //
    // keyboard registration
    //
    glutKeyboardFunc( onKeyDown ) ;
    glutSpecialFunc( onSpecialKeyDown ) ;
    
    glutKeyboardUpFunc( onKeyUp ) ;
    glutSpecialUpFunc( onSpecialKeyUp ) ;
    
    //
    // mouse registration
    //
    glutMouseFunc( onClick) ;
    glutMotionFunc( onMoveDown ) ;
    glutPassiveMotionFunc( onMove ) ;
    
#if  TIMER_ON == 1
    // timer event
    glutTimerFunc( TIMER_PERIOD, onTimer, 0 ) ;
#endif
    
    Init();
    
    glutMainLoop();
}

