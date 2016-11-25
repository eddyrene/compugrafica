

#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include <algorithm>
#include <cstdio>
GLsizei winWidth = 640, winHeight = 480;



typedef pair<int, int > punto;
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
