#include <iostream>
#include "poligono.h"



using namespace std;
/*
 * Nombre: Eddy Rene Caceres Huacarpuma TUX
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
/*
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(-winWidth/2, winWidth/2, -winHeight/2, winHeight/2);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();

*/
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(0,winWidth,0,winHeight);
 glMatrixMode(GL_MODELVIEW);

}

void init()
{
     glClearColor(0,0,0,0);
}



/*

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
poligono * polin=new poligono();


void display1()
{

    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);

    int salir=1, opcion;
    while (salir!=0)
    {
        //cout<<" Poligono Estático "<<endl;
        cout<<"Ingrese la opcion deseada"<<endl;
        cout<<" 1) Polígono Estatico , ( lados, radio)"<<endl;
        //cout<<" 2) Poligono con mouse"<<endl;
        cout<<" ESC) Salir"<<endl;
        cin>>opcion;
       // cout<<opcion<<endl;
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
                poli->rellenar();
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
                        poli->rotacion_compuesta(ag);
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
        case 0:
            salir=0;
        }
    }
    return;
}

void display2()
{

}

typedef pair<int, int > punto;
typedef struct nodo{
    int  yalto;
    float xinter, difx;
    nodo * siguiente;
}nodo;

void insert_nodo(nodo * lista, nodo * pnodo)
{
    nodo * p , * q = lista;
    p=q->siguiente;
    while(p!=NULL)
    {
        if(pnodo->xinter<p->xinter)
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
    pnodo->xinter=lower.first;
    if(upper.second<yComp)
        pnodo->yalto=upper.second-1;
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
        for(i=p1->xinter;i<p2->xinter;i++)
        {
            glBegin(GL_POINTS);
               glVertex2d(i, scan);
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
            p->xinter=p->xinter+p->difx;
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

void scanfill(int cnt,  punto * pts)
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

void relleno_concavo()
{
    cout<<"tamaño:"<<polin->ivertices->size()<<endl;
       punto * puntos=new punto[polin->ivertices->size()];//;polin->ivertices->size()];

       for(int i=0;i< polin->ivertices->size();i++)
       {
           puntos[i]=make_pair(polin->ivertices->at(i).first,polin->ivertices->at(i).second);
           cout<<puntos[i].first<< ", "<<puntos[i].second<<endl;
       }

      /* puntos[0]=make_pair(129,124);
       puntos[1]=make_pair(156,30);
       puntos[2]=make_pair(99,77);
       puntos[3]=make_pair(22,10);
       puntos[4]=make_pair(26,118);*/
       /*
       puntos[0]=make_pair(129,124);
       puntos[1]=make_pair(156,30);
       puntos[2]=make_pair(99,77);
       puntos[3]=make_pair(22,10);
       puntos[4]=make_pair(26,118);
       */
       glClear (GL_COLOR_BUFFER_BIT);
       glColor3f (0.0, 1.0, 1.0);
       //scanfill(polin->ivertices->size(),puntos);
       cout<<"aqui llega"<<endl;
       try {
           scanfill(polin->ivertices->size(),puntos);
       } catch (const exception  & e) {
        cout<<"error aqui: "<< e.what() <<endl;
       }


      // glFlush();
 }


void mouse(int button, int state, int x, int y)
{

    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
               // cout<<"coordenada"<<x-winWidth/2<<" "<<winHeight/2-y<<endl;
                cout<<"coordenada"<<x<<" "<<winHeight-y<<endl;
                //polin->insert_vertice(x-winWidth/2,winHeight/2-y);
                polin->insert_vertice(x,winHeight-y);
                glClear (GL_COLOR_BUFFER_BIT);
                polin->redibujar_mouse();

                glFlush();
                // glutIdleFunc(spinDisplay);
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
            {
                glClear (GL_COLOR_BUFFER_BIT);
                 //polin->ivertices->push_back(make_pair(polin->ivertices->at(0).first,polin->ivertices->at(0).second));
                 polin->redibujar();
                 relleno_concavo();
                 glFlush();
                // cout<<"cuando termine presione  0"<<endl;
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
                         polin->traslacion(xt,yt);
                         polin->redibujar();
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
                         polin->rotacion_compuesta(ag);
                         polin->redibujar();
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
                         polin->escalado_compuesto(xt,yt);
                         polin->redibujar();
                         glFlush();
                     }
                         break;
                     case 0:
                         salir2=1;
                     }
                 }
            }
                // glutIdleFunc(NULL);
            break;
        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_DOWN)
                return;
                // glutIdleFunc(NULL);
         break;
      default:
         break;
   }
    /*glColor3d(1,0,1);
    glBegin(GL_POINTS);
        glVertex2d(0,0);
    glEnd();*/

}
int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowPosition(800, 50);
 glutInitWindowSize(winWidth, winHeight);
 glutCreateWindow("Traslacion de Poligono Estático");
 init();
 glutMouseFunc(mouse);
 glutReshapeFunc(reshape);
 //glutDisplayFunc(display1);
 glutDisplayFunc(display2);
 glutMainLoop();
system("PAUSE");
 return 0;
}
