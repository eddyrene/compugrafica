

#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <algorithm>
#include <cstdio>
GLsizei winWidth = 640, winHeight = 480;



void ElipsePoints(GLfloat x, GLfloat y)
{
    glBegin(GL_POINTS);
    glVertex2i( x, y);
    glVertex2i( x, -y);
    glVertex2i(-x, y);
    glVertex2i(-x, -y);
    glEnd();
}

void pm_elipse(int a, int b)
{
    int x, y;
    GLfloat d1, d2;
    x = 0;
    y = b;
    d1 = b * b - a * a * b + a * a / 4.0;
    ElipsePoints(x, y);
    while(a * a * (y - 0.5) > b * b * (x + 1))
    {
        if (d1 < 0)
        {
            d1 = d1 + b * b * (2 * x + 3);
            x++;
        }
        else
        {
            d1 = d1 + b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            x++;
            y--;
        }
        ElipsePoints(x, y);
    }
    d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
    while(y > 0)
    {
        if (d2 < 0)
        {
            d2 = d2 + b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
            y--;
        }
        else
        {
            d2 = d2 + a * a * (-2 * y + 3);
            y-=1;
        }
        ElipsePoints(x, y);
    }
}

void dibuja_elipse()
{

    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);
    pm_elipse(200,100);
    glFlush();
}
