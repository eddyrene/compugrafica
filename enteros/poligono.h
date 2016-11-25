#ifndef POLIGNO_H
#define POLIGNO_H
#include "lamatriz.h"
#include "linea.h"
#include <vector>

using namespace std;

typedef vector<pair<float,float> > points_float;


class poligono
{
private:
    int lados;
    int radio;
    points_float * ivertices, *fvertices;
    linea * milinea;
    lamatriz * matri;
public:
    poligono();
    void setlado( int l){lados=l;}
    void setradio (int r){radio=r;}
    int getlado(){return lados;}
    int getradio(){return radio;}

    void normal();
    void circunscrito();
    void traslacion(int tx, int ty);
    void rotacion(double a);
    void escalado(int tx, int ty);
    void redibujar();

    /*void dibujar_normal();
    void dibujar_circu();*/
};

#endif // POLIGNO_H
