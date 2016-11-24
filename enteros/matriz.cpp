#include <iostream>
#include <vector>

using namespace std;

//#define SM (CLS / sizeof (double))

typedef vector<int> array;
typedef vector<vector<float> > matriz;
typedef pair<float, float> ver;
typedef vector<pair<float,float> > vfpoints;

void imprimir(matriz &v, int a , int b)
{
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<b;j++)
            cout<<v[i][j]<<"\t";
        cout<<endl;
    }
}

void crear_matriz(matriz &v, int a , int b)
{
    v.resize(a);
    for(int i=0;i<a;i++)
        v[i].resize(b);
}
void matriz_identidad(matriz &v,int a, int b)
{
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<b;j++){
            if(i==j)
            {
                v[i][j]=1;
            }
            else
                v[i][j]=0;
        }
    }
}

void llenar_matriz(matriz &v, int a , int b)
{
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<b;j++){
            cout<<"M["<<i<<"]["<<j<<"]: ";
                 cin>> v[i][j];}
    }
}
void llenar_ceros(matriz &v, int a , int b)
{
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<b;j++){
                v[i][j]=0; }
    }

}
matriz multiplicacion(matriz &A,int m,int n, matriz &B ,int o)
{
    matriz C;
    crear_matriz(C,m,o);
    llenar_ceros(C,m,o);
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            for(int k=0;k<o;k++)
                C[i][j]+=A[i][k]*B[k][j];

    return C;
}

matriz vertices_matriz(vfpoints &a)
{
    matriz C;
    int f = a.size();
    crear_matriz(C,f,3);
    for(int i=0;i<f;i++)
    {
        C[i][0]= a[i].first;
        C[i][1]= a[i].second;
        C[i][2]= 1;
    }

    return C;
}

matriz multiplicacion2(matriz &A,int N, matriz &B)
{
    double SM=32;
    matriz res;
    crear_matriz(res,N,N);
    llenar_ceros(res,N,N);
    for (int i1 = 0; i1 < N/SM; i1 += SM)
        for (int j1 = 0; j1 < N/SM; j1 += SM)
            for ( int k1 = 0; k1 <N/SM; k1 += SM)
                for (int i = i1; i<i1+SM&&i<N;i++)
                    for	(int j=j1;j<j1+SM&&j<N;j++)
                        for	(int k=k1;k<k1+SM&&k<N;k++)
                            res[i][j]+=A[i][k]*B[k][j];
    return res;
}
