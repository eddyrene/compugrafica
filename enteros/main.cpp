#include <iostream>
#include "poligono.h"



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
//typedef pair<int, int > punto;
typedef vector<pair<int,int> > vpoints;
//typedef vector<pair<float,float> > vfpoints;
int xmax, xmin, ymax, ymin=0;

vpoints * puntos = new vpoints();


//vfpoints * vertices = new vfpoints();

GLsizei winWidth = 640, winHeight = 480;

//punto * v_finales;

void reshape(int width, int height)
{
 glViewport(0, 0, winWidth, winHeight);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(-winWidth/2, winWidth/2, -winHeight/2, winHeight/2);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();

}

void init()
{
     glClearColor(0,0,0,0);
}

/*
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
void dibujar_matr(matriz & m, int f )
{

    cout<<"si esta entrando aqui"<<endl;
    v_finales = new punto[f];
    for( int i =0;i<f ;i++)
    {
        if(i==f-1)
        {
            pm_linea_float(m[i][0],m[i][1],m[0][0],m[0][1]);
            v_finales[i]=make_pair(m[i][0],m[i][1]);
        }
        else
        {
            int x=m[i][0];
            int  y=m[i][1];
            int xx=m[i+1][0];
            int  yy=m[i+1][1];
            pm_linea_float(x,y,xx,yy);
            v_finales[i]=make_pair(x,y);
        }
    }

     punto * puntoss=new punto[4];
    for(int i =0;i<f;i++)
    {
        cout<<"par : "<<v_finales[i].first<<" "<<v_finales[i].second<<endl;
        //puntoss[i]=make_pair(v_finales[i].first,v_finales[i].second);
    }

   puntoss[0]=make_pair(104,4);
    puntoss[1]=make_pair(4,104);
    puntoss[2]=make_pair(-96,4);
    puntoss[3]=make_pair(3,-96);
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 1.0, 1.0);
    scanfill(4,puntoss);
    glFlush();

}

*/

void display()
{

    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);

    int salir=0, opcion;
    while (salir==0)
    {
        //cout<<" Poligono Estático "<<endl;
        cout<<"Ingrese la opcion deseada"<<endl;
        cout<<" 1) Polígono Estatico , ( lados, radio)"<<endl;
        cout<<" 2) Poligono con mouse"<<endl;
        cout<<" ESC) Salir"<<endl;
        cin>>opcion;
        switch(opcion)
        {
            case 1:
            {
                int lados,radio;
                poligono * poli = new poligono();
                cout<<"Numero de lados: "<<endl;
                cin >> lados;
                cout<<"Radio: "<<endl;
                cin>>radio;
                poli->setlado(lados);
                poli->setradio(radio);
                poli->normal();
                glFlush();

                int salir2=0, opcion2;

                while(salir2 == 0)
                {
                    cout<<"Transformaciones"<<endl;
                    cout<<"1) Traslacion"<<endl;
                    cout<<"2) Rotacion"<<endl;
                    cout<<"3) Escalado "<<endl;
                    cout<<"ESC) Salir"<<endl;
                    cin>>opcion2;
                    switch (opcion2) {
                    case 1:
                    {
                        int xt,yt;
                        cout<<"Traslacion"<<endl;
                        cout<<"Coordeanada X: ";
                        cin>>xt;
                        cout<<"Coordeanada Y: ";
                        cin>>yt;

                        glClear (GL_COLOR_BUFFER_BIT);
                        poli->traslacion(xt,yt);
                        poli->redibujar();
                        glFlush();
                    }
                        break;

                    case 2:
                    {
                        double ag;
                        cout<<"Rotacion"<<endl;
                        cout<<"Angulo: ";
                        cin>>ag;
                        glClear (GL_COLOR_BUFFER_BIT);
                        poli->rotacion(ag);
                        poli->redibujar();
                        glFlush();
                    }
                           break;
                    case 3:
                    {
                        int xt,yt;
                        cout<<"Escalado"<<endl;
                        cout<<"Coordeanada X: ";
                        cin>>xt;
                        cout<<"Coordeanada Y: ";
                        cin>>yt;

                        glClear (GL_COLOR_BUFFER_BIT);
                        poli->escalado(xt,yt);
                        poli->redibujar();
                        glFlush();
                    }
                           break;
                    case 27:
                        salir2=1;
                    }

                }
        }

            break;

            case 2:
                cout<<"Esta funcion aun no esta"<<endl;
            break;

            case 27:
                salir=1;
        }
    }
}

int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowPosition(800, 50);
 glutInitWindowSize(winWidth, winHeight);
 glutCreateWindow("Traslacion de Poligono Estático");
 init();
 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutMainLoop();
 system("PAUSE");
 return 0;
}
