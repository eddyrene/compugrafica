#include <GL/glut.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include "matriz.cpp"

using namespace std;
/*
 * Nombre: Eddy Rene Caceres Huacarpuma
 *
 * Funciones:
 * Poligono circunscrito.
 * Linea - Algorito punto-pendiente
 * Linea - Algoritmo de Bresemham
 * Circulo - Algoritmo Punto Medio
 * Elipse - Algoritmo Punto Medio
 * Rellenado de poligno
 *
 * NOTA: Las funciones estan comentadas en en la funcion main, solo descomentar y probar;
 *  **Bibliografia: Apostilas.
 *                  Computer Graphics with opengl.
 * */
typedef vector<pair<int, int> > vpairs;
typedef pair<int, int > punto;
typedef vector<pair<int,int> > vpoints;
typedef vector<pair<float,float> > vfpoints;
int xmax, xmin, ymax, ymin=0;

vpoints * puntos = new vpoints();
GLsizei winWidth = 640, winHeight = 480;

vfpoints * vertices = new vfpoints();

matriz ma;

void reshape(int width, int height)
{
 glViewport(0, 0, winWidth, winHeight);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(-winWidth/2, winWidth/2, -winHeight/2, winHeight/2);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
/*
 glViewport(0, 0, width, height);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-1, 1, -1, 1, -1, 1);
 glMatrixMode(GL_MODELVIEW);*/
}

void init()
{
     glClearColor(0,0,0,0);
}

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
void linea_pediente(int x1, int y1, int x2, int y2 )
{
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


void pm_linea(int x1, int y1, int x2, int y2 )
{
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

void pm_linea_float(GLfloat x1, GLfloat y1,GLfloat x2, GLfloat y2 )
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

void mypoligono(int  lados, int radio)
{
    GLfloat angulo1=0.0;
    GLfloat angulo2=0.0;

    GLfloat grados = 360/(GLfloat)lados;
    for (GLfloat i=0; i<360; i+=grados)
    {
       angulo1 = (GLfloat)i* 3.14159f/180.0f;
       angulo2 = (GLfloat)(i+grados)*3.14159f/180.0f; // grados a radianes
       GLfloat x = radio*cos(angulo1);
       GLfloat y = radio*sin(angulo1);
       GLfloat x2 = radio*cos(angulo2);//multiplicaion el radio ya se soluciona este incoveniente.. XD
       GLfloat y2 = radio*sin(angulo2);
       pm_linea_float(x,y,x2,y2);
       vertices->push_back(make_pair(x,y));
       cout<<"cc: " << x <<" "<<y<<" "<<x2<<" "<<y2<<endl;
    }
}

void poligono(int lados, int radio)
{
     GLfloat angulo1=0.0;
     GLfloat angulo2=0.0;
     glBegin(GL_LINES);
     GLfloat grados = 360/(GLfloat)lados;
     for (GLfloat i=0; i<360; i+=grados)
     {
        angulo1 = (GLfloat)i*3.14159f/180.0f;
        angulo2 = (GLfloat)(i+grados)*3.14159f/180.0f; // grados a radianes
        GLfloat x = radio*cos(angulo1);
        GLfloat y = radio*sin(angulo1);
        GLfloat x2 = radio*cos(angulo2);//multiplicaion el radio ya se soluciona este incoveniente.. XD
        GLfloat y2 = radio*sin(angulo2);
        glVertex3f(x, y, 0.0f);
        glVertex3f(x2, y2, 0.0f);
     }
     glEnd();
     glBegin(GL_POINTS);
     GLfloat grados1= 0.0001;
     for ( GLfloat j=0; j<360; j+=grados1)
     {
        angulo1 = (GLfloat)j*3.14159f/180.0f;
        GLfloat x = radio*cos(angulo1);
        GLfloat y = radio*sin(angulo1);
        glVertex3f(x, y, 0.0f);
     }
     glEnd();
}

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

void dibuja_poligono()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);
    GLint l = 4;GLint r=200;
    cout<<"Ingrese lados  radio (de preferencia >150)"<<endl;
    cin>>l>>r;
    mypoligono(l,r);
    glFlush();
}

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

void dibuja_elipse()
{

    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);
    pm_elipse(200,100);
    glFlush();
}

typedef struct nodo{
    int  yalto;
    int  xbajo;
    float xinter, difx;
    nodo * siguiente;
}nodo;

void insert_nodo(nodo * lista, nodo * pnodo)
{
    nodo * p , * q = lista;
    p=q->siguiente;
    while(p!=NULL)
    {
        if(pnodo->xbajo<p->xbajo)
            p=NULL;
        else {
            q=p;
            p=p->siguiente;
        }
    }
    pnodo->siguiente = q->siguiente;
    q->siguiente=pnodo;
}
int siguiente_y(int k,int cnt , punto * pts)
{
    int j;
    if( (k+1)>(cnt-1))
        j=0;
    else
        j=k+1;
    while(pts[k].second == pts[j].second)
        if((j+1) > (cnt-1))
          j=0;
        else
            j++;
    return pts[j].second;
}

void makeEdgeRec(punto lower, punto upper, int yComp, nodo * pnodo, nodo * nodos[])
{
    pnodo->difx=(float)(upper.first-lower.first)/ (upper.second-lower.second);
    pnodo->xbajo=lower.first;
    if(upper.second<yComp)
        pnodo->yalto=upper.second;
    else
        pnodo->yalto=upper.second;
    insert_nodo(nodos[lower.second],pnodo);
}

void build_TB(int cnt, punto * pts, nodo * nodos[])
{
    nodo * pnodo;
    punto p1,p2;
    int i, yprev = pts[cnt-2].second;

    p1.first=pts[cnt-1].first;
    p1.second= pts[cnt-1].second;
    for(i=0;i<cnt;i++)
    {
        p2=pts[i];
        if(p1.second != p2.second)
        {
            pnodo = (nodo *) malloc (sizeof(nodo) );
            if(p1.second < p2.second)
                makeEdgeRec(p1,p2,siguiente_y(i,cnt,pts),pnodo,nodos);
            else
                makeEdgeRec(p2,p1,yprev,pnodo,nodos);
        }
        yprev=p1.second;
        p1=p2;
    }
}
void build_LBA (int scan, nodo *  active, nodo * nodos[])
{
    nodo * p, *q;
    p=nodos[scan]->siguiente;
    while(p)
    {
        q=p->siguiente;
        insert_nodo(active,p);
        p=q;
    }
}
void fillScan (int scan, nodo * active)
{
    nodo * p1, *p2;
    int i;
    p1=active->siguiente;
    while(p1){
        p2=p1->siguiente;
        for(i=p1->xbajo;i<p2->xbajo;i++)
        {
            glBegin(GL_POINTS);
               glVertex3f(i, scan, 0.0f);
            glEnd();
        }
        p1 = p2->siguiente;
    }
}
void deleteAfter(nodo * q)
{
    nodo *p=q->siguiente;
    q->siguiente = p->siguiente;
    free ( p );
}
void actualiza_LBA (int scan, nodo * active)
{
    nodo * q = active;
    nodo * p = active->siguiente;
    while(p)
    {
        if(scan >= p->yalto){
            p=p->siguiente;
            deleteAfter(q);
        }
        else{
            p->xbajo=p->xbajo+p->difx;
            q=p;
            p=p->siguiente;
        }
    }
}

void reordena_LBA(nodo * active)
{
    nodo * q, *p = active->siguiente;
    active->siguiente=NULL;
    while(p){
        q=p->siguiente;
        insert_nodo(active,p);
        p=q;
    }
}

void scanfill(int cnt,punto * pts)
{
    nodo * nodos[winHeight], *active;
    int i, scan;
    for(i=0;i<winHeight;i++){
        nodos[i]=(nodo *) malloc(sizeof(nodo));
        nodos[i]->siguiente=NULL;
    }
    build_TB(cnt,pts,nodos);
    active = (nodo *) malloc(sizeof(nodo));
    active->siguiente=NULL;
    for(scan=0;scan<winHeight;scan++)
    {
        build_LBA(scan,active,nodos);
        if(active->siguiente)
        {
            fillScan(scan,active);
            actualiza_LBA(scan,active);
            reordena_LBA(active);
        }
    }
}
void relleno_convexo()
{
    punto * puntos=new punto[4];
    puntos[0]=make_pair(0,0);
    puntos[1]=make_pair(0,200);
    puntos[2]=make_pair(200,200);
    puntos[3]=make_pair(200,0);
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 1.0, 1.0);
    scanfill(4,puntos);
    glFlush();
}
void relleno_concavo(){

       punto * puntos=new punto[5];
       puntos[0]=make_pair(160,120);
       puntos[1]=make_pair(180,5);
       puntos[2]=make_pair(100,70);
       puntos[3]=make_pair(10,20);
       puntos[4]=make_pair(20,120);
       glClear (GL_COLOR_BUFFER_BIT);
       glColor3f (0.0, 1.0, 1.0);
       scanfill(5,puntos);
       glFlush();
   }



matriz traslacion(int tx , int ty)
{
   /*
    * crea la matriz traslacio
    */

    crear_matriz(ma,3,3);
    matriz_identidad(ma,3,3);
    ma[2][0]=tx;
    ma[2][1]=ty;
   // mypoligono(4,100);
    imprimir(ma,3,3);
    cout<<endl<<endl;
    matriz p = vertices_matriz(*vertices);
    int filas= vertices->size();
    imprimir(p,filas,3);
    cout<<endl<<endl;
    matriz result=multiplicacion(p,filas,3,ma,3);
    imprimir(result,filas,3);
    return result;
}

matriz rotacion(double a)
{
   /*
    * crea la matriz traslacio
    */
    GLfloat ang=(GLfloat)(a)*3.14159f/180.0f;
    crear_matriz(ma,3,3);
    matriz_identidad(ma,3,3);
    ma[0][0]=cos(ang);
    ma[0][1]=sin(ang);
    ma[1][0]=-sin(ang);
    ma[1][1]=cos(ang);
   // mypoligono(4,100);
    imprimir(ma,3,3);
    cout<<endl<<endl;
    matriz p = vertices_matriz(*vertices);
    int filas= vertices->size();
    imprimir(p,filas,3);
    cout<<endl<<endl;
    matriz result=multiplicacion(p,filas,3,ma,3);
    imprimir(result,filas,3);
    return result;
}

matriz escalado(int tx , int ty)
{
   /*
    * crea la matriz traslacio
    */

    crear_matriz(ma,3,3);
    matriz_identidad(ma,3,3);
    ma[0][0]=tx;
    ma[1][1]=ty;
   // mypoligono(4,100);
    imprimir(ma,3,3);
    cout<<endl<<endl;
    matriz p = vertices_matriz(*vertices);
    int filas= vertices->size();
    imprimir(p,filas,3);
    cout<<endl<<endl;
    matriz result=multiplicacion(p,filas,3,ma,3);
    imprimir(result,filas,3);
    return result;
}

void dibujar_matr(matriz & m, int f)
{
    for( int i =0;i<f ;i++)
    {
        if(i==f-1)
        {
            pm_linea_float(m[i][0],m[i][1],m[0][0],m[0][1]);
        }
        else
        {
            int x=m[i][0];
            int  y=m[i][1];
            int xx=m[i+1][0];
            int  yy=m[i+1][1];
            pm_linea_float(x,y,xx,yy);
        }
    }
}


void dibujar_poligono_traslacion()
{

    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);
    int tt,pp;
    cout<<"indica coordenadas de traslacion"<<endl;
    cin>>tt>>pp;
    matriz t =traslacion(tt,pp);
    dibujar_matr(t ,vertices->size());
    glFlush();

}

void dibujar_poligono_rotacion()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);
    int tt;
    cout<<"indica angulo de rotacion en sexagesimales"<<endl;
    cin>>tt;
    matriz t =rotacion(tt);
    dibujar_matr(t ,vertices->size());
    glFlush();

}

void dibujar_poligono_escalado()
{

    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);

    int tt,pp;
    cout<<"indica coordenadas de escalado"<<endl;
    cin>>tt>>pp;
    matriz t =escalado(tt,pp);
    dibujar_matr(t ,vertices->size());
    glFlush();

}


int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowPosition(800, 50);
 glutInitWindowSize(winWidth, winHeight);
 glutCreateWindow("Dibujos con punto-medio");
 init();

 //glutDisplayFunc(dibuja_linea);
 glutDisplayFunc(dibuja_poligono);
 //glutDisplayFunc(dibuja_linea);
 //glutDisplayFunc(dibuja_circulo);
 glutReshapeFunc(reshape);

 init();
 glutCreateWindow("Dibujos con punto-medio");

 /*
  * Transformaciones en 2D
  */

 //glutDisplayFunc(dibujar_poligono_traslacion);
 glutDisplayFunc(dibujar_poligono_rotacion);
 //glutDisplayFunc(dibujar_poligono_escalado);


 //glutDisplayFunc(dibuja_elipse);
 //glutDisplayFunc(relleno_convexo);
 //glutDisplayFunc(relleno_concavo);
 glutReshapeFunc(reshape);
 glutMainLoop();
 return 0;
}
