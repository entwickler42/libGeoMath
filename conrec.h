#ifndef CONREC_H
#define CONREC_H

/*
    Autor  :    Stefan Brück , original by internet ;)
    E-Mail :    <mailbockx@freenet.de>
    Datum  :    030811

    ToDo   :
*/

#include <vector>
#include "cmd.h"

using namespace std;

namespace std
{

#define xsect(p1,p2) (h[p2]*xh[p1]-h[p1]*xh[p2])/(h[p2]-h[p1])
#define ysect(p1,p2) (h[p2]*yh[p1]-h[p1]*yh[p2])/(h[p2]-h[p1])

//---------------------------------------------------------------------------------------
template <class T> __export vector<T> conrec(const vector<T>& v, unsigned int nc = 1, float * z = &v)
{
    // Es wird ein 2 dimensionales Feld aus dem vector v angelegt
    unsigned int xmin=1e8, ymin=1e8, xmax=0, ymax=0,nx,ny;

    for(unsigned int i=0; i<v.size(); i++)
    {
        if( xmin > v[i].x ) xmin = v[i].x;
        if( ymin > v[i].y ) ymin = v[i].y;
        if( xmax < v[i].x ) xmax = v[i].x;
        if( ymax < v[i].y ) ymax = v[i].y;
    }

    // Dimensionen des Feldes
    nx = (xmax - xmin)+1;
    ny = (ymax - ymin)+1;

    // Speicher reservieren
    float** f = new float*[ny];
    for(unsigned int i=0; i<ny; i++) f[i] = new float[nx];

    // Feld mit den Werten aus v belegen
    for(unsigned int i=0; i<v.size(); i++)  f[v[i].y-ymin][v[i].x-xmin] = v[i].z;

    // Aufruf des conrec Algorithmus Variante 2
    vector<T> pv = conrec<T>(f,nx,ny,nc,z);

    // Speicher freigeben & Rückgabe
    delete f;
    return pv;
}

//---------------------------------------------------------------------------------------
template <class T> vector<T> __export  conrec(float** f, unsigned int nx, unsigned int ny, unsigned int nc = 1, float *z = &v)
{
    // Index der Punkte ( wird benötigt für den conrec Algorithmus )
    float *xv = new float[nx*ny];
    float *yv = new float[ny*ny];

    for(unsigned int i=0;i<nx;i++) xv[i] = i;
    for(unsigned int i=0;i<ny;i++) yv[i] = i;

    // Aufruf des original conrec Algorithmus
    vector<T> pv = conrec<T>(f,0,nx-1,0,ny-1,xv,yv,nc,z);

    // Speicher freigeben
    delete xv;  delete yv;

    return pv;
}

//---------------------------------------------------------------------------------------
template <class T> vector<T> __export conrec(float **d, int ilb, int iub, int jlb, int jub, float *x, float *y, int nc, float *z)
{
    vector<T> pv;

    float zmin, dmin, dmax, x1, x2, y1, y2, xh[5], yh[5], h[5];
    int i,j,k,m,m1,m2,m3,case_value, sh[5], im[4] = {0,1,1,0}, jm[4]={0,0,1,1};
    int castab[3][3][3] = { { {0,0,8},{0,2,5},{7,6,9} }, { {0,3,4},{1,3,1},{4,3,0} }, { {9,6,7},{5,2,0},{8,0,0} } };

    for (j=(jub-1);j>=jlb;j--)
    {
        for (i=ilb;i<=iub-1;i++)
        {
            float temp1,temp2;
            temp1 = min(d[j][i],d[j+1][i]);
            temp2 = min(d[j][i+1],d[j+1][i+1]);
            dmin = min(temp1,temp2);
            temp1 = max(d[j][i],d[j+1][i]);
            temp2 = max(d[j][i+1],d[j+1][i+1]);
            dmax = max(temp1,temp2);
            if (dmax>=z[0]&&dmin<=z[nc-1])
            {
                for (k=0;k<nc;k++)
                {
                    if (z[k]>=dmin&&z[k]<=dmax)
                    {
                        for (m=4;m>=0;m--)
                        {
                            if (m>0)
                            {
                                h[m] = d[j+jm[m-1]][i+im[m-1]]-z[k];
                                xh[m] = x[i+im[m-1]];
                                yh[m] = y[j+jm[m-1]];
                            }
                            else
                            {
                                h[0] = 0.25*(h[1]+h[2]+h[3]+h[4]);
                                xh[0]=0.5*(x[i]+x[i+1]);
                                yh[0]=0.5*(y[j]+y[j+1]);
                            }
                            if (h[m]>0.0)
                            {
                                sh[m] = 1;
                            }
                            else if (h[m]<0.0)
                            {
                                sh[m] = -1;
                            }
                            else
                                sh[m] = 0;
                        }
                        for (m=1;m<=4;m++)
                        {
                            m1 = m;
                            m2 = 0;
                            if (m!=4) m3 = m+1;
                            else m3 = 1;
                            case_value = castab[sh[m1]+1][sh[m2]+1][sh[m3]+1];
                            if (case_value!=0)
                            {
                                switch (case_value)
                                {
                                    case 1:
                                        x1=xh[m1];
                                        y1=yh[m1];
                                        x2=xh[m2];
                                        y2=yh[m2];
                                        break;
                                    case 2:
                                        x1=xh[m2];
                                        y1=yh[m2];
                                        x2=xh[m3];
                                        y2=yh[m3];
                                        break;
                                    case 3:
                                        x1=xh[m3];
                                        y1=yh[m3];
                                        x2=xh[m1];
                                        y2=yh[m1];
                                        break;
                                    case 4:
                                        x1=xh[m1];
                                        y1=yh[m1];
                                        x2=xsect(m2,m3);
                                        y2=ysect(m2,m3);
                                        break;
                                    case 5:
                                        x1=xh[m2];
                                        y1=yh[m2];
                                        x2=xsect(m3,m1);
                                        y2=ysect(m3,m1);
                                        break;
                                    case 6:
                                        x1=xh[m3];
                                        y1=yh[m3];
                                        x2=xsect(m1,m2);
                                        y2=ysect(m1,m2);
                                        break;
                                    case 7:
                                        x1=xsect(m1,m2);
                                        y1=ysect(m1,m2);
                                        x2=xsect(m2,m3);
                                        y2=ysect(m2,m3);
                                        break;
                                    case 8:
                                        x1=xsect(m2,m3);
                                        y1=ysect(m2,m3);
                                        x2=xsect(m3,m1);
                                        y2=ysect(m3,m1);
                                        break;
                                    case 9:
                                        x1=xsect(m3,m1);
                                        y1=ysect(m3,m1);
                                        x2=xsect(m1,m2);
                                        y2=ysect(m1,m2);
                                        break;
                                    default:
                                    break;
                                }
                                pv.push_back(T(x1,y1,z[k]));
                                pv.push_back(T(x2,y2,z[k]));
                            }
                        }
                    }
                }
            }
        }
    }
    return pv;
}

}

#endif


 