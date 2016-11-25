
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <algorithm>
#include <cstdio>
GLsizei winWidth = 640, winHeight = 480;


void CirclePoints(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i( x, y);
    glVertex2i( x, -y);
    glVertex2i(-x, y);
    glVertex2i(-x, -y);
    glVertex2i( y, x);
    glVertex2i( y, -x);
    glVertex2i(-y, x);
    glVertex2i(-y, -x);
    glEnd ();
}
void circulo_pm(GLint &x, GLint &y, GLint &radio)
{
    GLint r=radio;
    GLint d;
    x = 0;
    y = r;
    d = 5/4 - r;
    CirclePoints(x,y);
    while (y > x)
    {
        if (d < 0){
            d = d + 2 * x + 3;
            x+=1;
        }
        else
        {
            d = d + 2 * (x - y) + 5;
            x+=1;
            y-=1;
        }
       CirclePoints(x,y);
    }
}

void dibuja_circulo()
{
    GLint x=winWidth / 2;
    GLint y=winHeight / 2;
    GLint r= 200;
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);
    circulo_pm(x,y,r);
    glFlush();
}
