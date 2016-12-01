#include "poligono.h"


poligono::poligono()
{
    milinea=new linea();
    ivertices = new points_float();
    fvertices = new points_float();
    matri= new lamatriz();
}
void poligono::normal()
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
       milinea->setvalues(x,y,x2,y2);
       milinea->pm_float();
       ivertices->push_back(make_pair(x,y));
       //cout<<"cc: " << x <<" "<<y<<" "<<x2<<" "<<y2<<endl;
    }
}

void poligono::circunscrito()
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

void poligono::traslacion(int tx, int ty)
{
    int filas= ivertices->size();
    cout<<"filas:"<<filas<<endl;
    matri->matriz_traslacion(tx,ty);
    matri->vertices_matriz(ivertices); // de vector a matriz

    matri->rmultiplicacion(filas,3,3);

    ivertices =  matri->matriz_to_vertices();
    //ivertices=fvertices;}
}
void poligono::rotacion(double a)
{
    int filas= ivertices->size();
    matri->matriz_rotacion(a);
    matri->vertices_matriz(ivertices);

    matri->rmultiplicacion(filas,3,3);
    ivertices = matri->matriz_to_vertices();
    //ivertices=fvertices;
}

void poligono::rotacion_compuesta(double a)
{
    int xc,yc=0;
    int filas= ivertices->size();
    for(int i=0;i<filas;i++)
    {
        xc+=ivertices->at(i).first;
        yc+=ivertices->at(i).second;
    }
    xc=xc/filas;
    yc=yc/filas;
    traslacion(-xc,-yc);
    rotacion(a);
    traslacion(xc,yc);
}

void poligono::escalado(int tx, int ty)
{

    int filas= ivertices->size();
    matri->matriz_escalado(tx,ty);
    matri->vertices_matriz(ivertices);

    matri->rmultiplicacion(filas,3,3);
    ivertices = matri->matriz_to_vertices();
}

void poligono::escalado_compuesto(int tx, int ty)
{
    int xc,yc=0;
    int filas= ivertices->size();
    for(int i=0;i<filas;i++)
    {
        xc+=ivertices->at(i).first;
        yc+=ivertices->at(i).second;
    }
    xc=xc/filas;
    yc=yc/filas;
    traslacion(-xc,-yc);
    escalado(tx,ty);
    traslacion(xc,yc);
}


void poligono::redibujar()
{
    linea * l =new linea;
    for( int i =0;i<ivertices->size() ;i++)
    {
        if(i==ivertices->size()-1)
        {
            l->setvalues(ivertices->at(i).first,ivertices->at(i).second,ivertices->at(0).first,ivertices->at(0).second);
            l->pm_float();
        }
        else
        {
            int x=ivertices->at(i).first;
            int y=ivertices->at(i).second;
            int xx=ivertices->at(i+1).first;
            int  yy=ivertices->at(i+1).second;
            l->setvalues(x,y,xx,yy);
            l->pm_float();
        }
    }
    //rellenar();
}
void poligono:: redibujar_mouse()
{
    linea * l =new linea;
    for( int i =0;i<ivertices->size() ;i++)
    {
        if(i==ivertices->size()-1)
        {
            return;
            //l->setvalues(ivertices->at(i).first,ivertices->at(i).second,ivertices->at(0).first,ivertices->at(0).second);
            //l->pm_float();
        }
        else
        {
            int x=ivertices->at(i).first;
            int y=ivertices->at(i).second;
            int xx=ivertices->at(i+1).first;
            int  yy=ivertices->at(i+1).second;
            l->setvalues(x,y,xx,yy);
            l->pm_float();
        }
    }
    //rellenar();
}

void poligono::rellenar()
{

}

void poligono::insert_vertice( int x, int y)
{
    ivertices->push_back(make_pair(x,y));
}


