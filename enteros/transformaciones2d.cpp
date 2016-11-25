#include "transformaciones2d.h"

transformaciones2d::transformaciones2d()
{
    vertices_ini = new points_float();
    vertices_fin= new points_float();
    matri =new lamatriz();
}

void transformaciones2d::matriz_traslacion()
{
    lamatriz * c = lamatriz();
    matri->matriz_traslacion(x,y);

    c->vertices_matriz()
    cout<<endl<<endl;
    matriz p = vertices_matriz(*vertices);
    int filas= vertices->size();
    imprimir(p,filas,3);


    cout<<endl<<endl;
    matriz result=multiplicacion(p,filas,3,ma,3);
    imprimir(result,filas,3);
    return result;
}

}
void transformaciones2d::graficar()
{
    cout<<"si esta entrando aqui"<<endl;
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
