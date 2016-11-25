#ifndef LINEA_H
#define LINEA_H

#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <algorithm>
#include <cstdio>


class linea{

private:
    float x1,y1, x2, y2;
   public:
    linea(){ x1 =1 ; x2=1; y2=1;y1=1;}

    void setvalues(int a,int b,int c,int d){x1= a; y1 =b; x2=c ; y2= d;}

    void punto_pendiente(){
        GLfloat m=(y2-y1)/(x2-x1);
        glBegin(GL_POINTS);
        GLint x,y;
        for (x=x1; x<x2; x++)
        {
           y=(y1+m*(x-x1));
           glVertex2i(x,y);
        }
        glEnd();
    }

    void punto_medio(){
        int dx, dy, incE, incNE, d, x, y, ax , ay;
        dx = x2 - x1;
        dy = y2 - y1;
        ax=ay=1;
        if( dy<0) // con estas lineas cambiamos la orientacion de avance para cuando la pendiente es negativa.
        {
             dy = -dy;
             ay= -1;
        }
         if(dx<0)
         {
             dx=-dx;
             ax=-1;
         }
        d = 2 * dy - dx; /* Valor inicial de d */
        incE = 2 * dy; /* Incremento de E */
        incNE = 2 * (dy - dx); /* Incremento de NE */
        x = x1;
        y = y1;
       glBegin(GL_POINTS);
       glVertex2i(x, y);
       if(x==x2 )
       {
            while ( y!=y2 )
            {
                 y+=ay;
                 glVertex2i(x, y);
            }
       }
       else{
             while ( x != x2 )
            {
                if (d < 0){
                    d = d + incE;
                    x+=ax;
                }else{
                    d = d + incNE;
                    x+=ax;
                    y+=ay;
                }
                glVertex2i(x, y);
            }
       }
        glEnd();
    }



    void pm_float()
    {

        GLfloat dx, dy, incE, incNE, d, x, y, ax , ay;
        dx = x2 - x1;
        dy = y2 - y1;
        ax=ay=1;
        if( dy<0) // con estas lineas cambiamos la orientacion de avance para cuando la pendiente es negativa.
        {
             dy=-dy;
             ay= -1;
        }
         if(dx<0)
         {
             dx=-dx;
             ax=-1;
         }
        if(dx > dy) // Para un pendiente  0< m <1
        {
           d = 2 * dy - dx; /* Valor inicial de d */
             incE = 2 * dy; /* Incremento de E */
             incNE = 2 * (dy - dx); /* Incremento de NE */
             x = x1;
             y = y1;
            glBegin(GL_POINTS);
            glVertex2f(x, y);
            while (abs(x-x2)>1)
           {
               if (d < 0){
                   d = d + incE;
                   x+=ax;
                   //cout<<"abs"<<endl;
               }else{
                   d = d + incNE;
                   x+=ax;
                   y+=ay;
               }
               glVertex2f(x, y);
           }
        }
        else{ // para un pendiente m<0  || m> 1

           d = 2 * dx - dy; /* Valor inicial de d */
             incE = 2 * dx; /* Incremento de E */
             incNE = 2 * (dx - dy); /* Incremento de NE */
             x = x1;
             y = y1;
            glBegin(GL_POINTS);
            while (abs(y-y2)>1)
           {
               if (d < 0){
                   d = d + incE;
                   y+=ay;
                   //cout<<"abs"<<endl;
               }else{
                   d = d + incNE;
                   x+=ax;
                   y+=ay;
               }
               glVertex2f(x, y);
           }
        }
        glEnd();

    }
};




#endif // LINEA_H
