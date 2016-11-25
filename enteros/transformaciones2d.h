#ifndef TRANSFORMACIONES2D_H
#define TRANSFORMACIONES2D_H
#include "lamatriz.h"

typedef vector<pair<float,float> > points_float;

class transformaciones2d
{
    points_float * vertices_ini;
    points_float * vertices_fin;
    lamatriz * matri;
public:
    transformaciones2d();
    void set_ver_ini( points_float * a){vertices_ini=a;}
    void set_ver_fin( points_float * a){vertices_fin=a;}
    points_float * get_ver_ini(){return vertices_ini;}
    points_float * get_ver_fin(){return vertices_fin;}

    void matriz_traslacion();
    void matriz_rotacion();
    void matriz_escalado();


    void graficar();


};

#endif // TRANSFORMACIONES2D_H
