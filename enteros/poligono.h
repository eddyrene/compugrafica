#ifndef POLIGNO_H
#define POLIGNO_H
#include "lamatriz.h"
#include "linea.h"
#include "relleno_poligono.cpp"
#include <vector>

using namespace std;



typedef vector<pair<float,float> > points_float;


class poligono
{
private:
    int lados;
    int radio;
    //points_float * ivertices, *fvertices;
    linea * milinea;
    lamatriz * matri;
public:

    points_float * ivertices, *fvertices;

    poligono();
    void setlado( int l){lados=l;}
    void setradio (int r){radio=r;}
    int getlado(){return lados;}
    int getradio(){return radio;}

    void normal();
    void circunscrito();
    void traslacion(float tx, float ty);
    void rotacion(double a);
    void rotacion_compuesta(double a);
    void escalado(float tx, float ty);
    void escalado_compuesto(float tx, float ty);
    void redibujar();
    void redibujar_mouse();
    void rellenar();
    void insert_vertice(int x, int y);

    /*void dibujar_normal();
    void dibujar_circu();*/
};

#endif // POLIGNO_H
