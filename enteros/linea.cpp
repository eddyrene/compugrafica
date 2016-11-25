#include "linea.h"

void linea::punto_pediente()
{


}


void linea::punto_medio( )
{

}
/*
void linea::pm_float()
{

}*/

void dibuja_linea()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);

    //glBegin(GL_POINTS);

   pm_linea_float(200 ,0,61.8036 ,190.211);
   //glColor3f (1.0, 0.0, 1.0);
  // glLoadIdentity();
  // //glBegin(GL_LINES);
    //glVertex2f(61.8036 ,190.211);
    //glVertex2f(200, 0);

   //pm_linea_float( -161.803, 117.557,61.8036 ,190.211);
   //pm_linea_float( -161.803, 117.557,-161.804 ,-117.557);
   //pm_linea_float( -161.804, -117.557, 61.8026, -190.212);
  // pm_linea_float( 61.8026 ,-190.212, 200 ,-0.00101407);
   //pm_linea_float( 200, -0.00101407, 61.8045, 190.211);

    glEnd();
    glFlush();
    /*glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glLoadIdentity();
    glBegin(GL_TRIANGLES);
    glVertex2f(-1,-1);
    glVertex2f(1,-1);
    glVertex2f(0,1);
    glEnd();
    glFlush();*/
}
