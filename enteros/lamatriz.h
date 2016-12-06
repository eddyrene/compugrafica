#ifndef LAMATRIZ_H
#define LAMATRIZ_H

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//#define SM (CLS / sizeof (double))

typedef vector< vector<float> > matriz;
typedef vector<pair<float,float> > points_float;

class lamatriz{
    private:
        matriz v,ide, result;
        int filas, col;
        points_float * vec_puntos;

        public:

        lamatriz() { filas =0 ; col =0; vec_puntos = new points_float(); this->matriz_identidad();}
        matriz getmatriz(){return v;}
        void setmatriz(matriz b){v=b;}
        matriz get_identidad(){return ide;}

        matriz get_resultado(){return result;}

        void imprimir_identidad()
        {
            cout<<"imprimiendo matriz"<<endl;
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                    cout<<ide[i][j]<<"\t";
                cout<<endl;
            }
            cout<<endl;
        }

        void imprimir_result()
        {
            for(int i=0;i<filas;i++)
            {
                for(int j=0;j<col;j++)
                    cout<<result[i][j]<<"\t";
                cout<<endl;
            }
            cout<<endl;
        }
        void imprimir_actual()
        {
            for(int i=0;i<filas;i++)
            {
                for(int j=0;j<col;j++)
                    cout<<v[i][j]<<"\t";
                cout<<endl;
            }
            cout<<endl;
        }

        void crear_matriz( matriz & mat , int a , int b)
        {
            //cout<<"crear matriz"<<endl;
            this->filas=a; this->col=b;
            //cout<<"crear matriz"<<endl;
            (mat).resize(a);
            //cout<<"crear matriz"<<endl;
            for(int i=0;i<a;i++)
                (mat)[i].resize(b);
        }
        void crear_matriz( int a , int b)
        {
            //cout<<"crear matriz"<<endl;
            this->filas=a; this->col=b;
            //cout<<"crear matriz"<<endl;
            v.resize(a);
            //cout<<"crear matriz"<<endl;
            for(int i=0;i<a;i++)
                v[i].resize(b);
        }

        void matriz_identidad()
        {
            int a=3;
            int b=3;
            (ide).resize(a);
            //cout<<"crear matriz"<<endl;
            for(int i=0;i<a;i++)
                (ide)[i].resize(b);
            for(int i=0;i<a;i++)
            {
                for(int j=0;j<b;j++){
                    if(i==j)
                    {
                        ide[i][j]=1;
                    }
                    else
                        ide[i][j]=0;
                }
            }
        }

        void llenar_matriz( int a , int b)
        {
            for(int i=0;i<a;i++)
            {
                for(int j=0;j<b;j++){
                    cout<<"M["<<i<<"]["<<j<<"]: ";
                         cin>>v[i][j];}
            }
        }
        void llenar_ceros(matriz &mat, int a , int b)
        {
            for(int i=0;i<a;i++)
            {
                for(int j=0;j<b;j++){
                        mat[i][j]=0; }
            }
        }
        void multiplicacion(matriz A,int m,int n, matriz B ,int o)
        {
            result.clear();
            crear_matriz(result,m,o);
            //llenar_ceros(m,o);
            for(int i=0;i<m;i++)
                for(int j=0;j<n;j++)
                    for(int k=0;k<o;k++)

                        result[i][j]+=A[i][k]*B[k][j];
           // return v;
        }

        void rmultiplicacion(int m,int n,int o)
        {
            filas=m;
            result.resize(m);
            for(int i=0;i<m;i++)
                result[i].resize(o);
            llenar_ceros(result,filas,n);
            for(int i=0;i<m;i++)
                for(int j=0;j<n;j++)
                    for(int k=0;k<o;k++)
                        result[i][j]+=v[i][k]*ide[k][j];

           imprimir_result();
        }

        void  vertices_matriz(points_float * a)
        {
            int f = a->size();
            crear_matriz(f,3);
            for(int i=0;i<f;i++)
            {
                v[i][0]= a->at(i).first;
                v[i][1]= a->at(i).second;
                v[i][2]= 1;
            }

           imprimir_actual();
        }

        points_float * matriz_to_vertices()
        {
            vec_puntos->clear();
            for(int i=0;i<filas;i++)
            {
                vec_puntos->push_back(make_pair(result[i][0],result[i][1]));
            }
               return vec_puntos;
        }


        matriz multiplicacion2(matriz &A,int N, matriz &B)
        {
           /* double SM=32;
            matriz res;
            crear_matriz(N,N);
            llenar_ceros(N,N);
            for (int i1 = 0; i1 < N/SM; i1 += SM)
                for (int j1 = 0; j1 < N/SM; j1 += SM)
                    for ( int k1 = 0; k1 <N/SM; k1 += SM)
                        for (int i = i1; i<i1+SM&&i<N;i++)
                            for	(int j=j1;j<j1+SM&&j<N;j++)
                                for	(int k=k1;k<k1+SM&&k<N;k++)
                                    res[i][j]+=A[i][k]*B[k][j];
            return res;*/
        }

        void matriz_traslacion(int a, int b)
        {
            ide.clear();
            this->matriz_identidad();
            this->ide[2][0]=a;
            this->ide[2][1]=b;
            this->imprimir_identidad();
        }

        void  matriz_rotacion(double a)
        {
            ide.clear();
            this->matriz_identidad();
            float ang=(float)(a)*3.14159f/180.0f;
            this->ide[0][0]=cos(ang);
            this->ide[0][1]=sin(ang);
            this->ide[1][0]=-sin(ang);
            this->ide[1][1]=cos(ang);
            this->imprimir_identidad();
        }
        void matriz_escalado(float tx, float ty)
        {
            ide.clear();
            matriz_identidad();
            ide[0][0]=tx;
            ide[1][1]=ty;
            this->imprimir_identidad();
        }
};

#endif

