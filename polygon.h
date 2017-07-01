#ifndef POLYGON_H
#define POLYGON_H

#include <math.h>
#include "point.h"

/*
    Autor  :    Stefan Brück
    E-Mail :    <mailbockx@freenet.de>
    Datum  :    030811

    ToDo   :
*/

using namespace std;

namespace std
{

template <class T> __export class Polygon : public vector<T>
{
    public:
        Polygon() {}

        Polygon(const vector<T>& v)
        {
            for(unsigned int i=0; i<v.size(); i++) push_back(v[i]);
        }

        bool isInside(const T& p) const
        {
            // Speicher für pnpoly Parameter reservieren
            float *xp = new float[size()];
            float *yp = new float[size()];

            bool ret  = true;

            // Parameter für den pnpoly Algorithmus vorbereiten
            for(unsigned int i=0;i<size();i++)
            {
                xp[i] = at(i).x;    yp[i] = at(i).y;
            }

            // pnpoly aufrufen um zu prüfen ob der Punkt im Polygon liegt
            if( (pnpoly(size(),xp,yp,p.x,p.y) % 2) == 0 ) ret = false;

            // Speicher frei geben
            delete xp;  delete yp;

            return ret;
        }

        void toClosedPath()
        {
            double* w = new double[size()];
            double tw;
            T a(1e8,1e8,0);

            // Als Ankerpunkt den untersten linken Punkt auswählen
            for(unsigned int i=0; i<size(); i++) if( at(i).y < a.y ) a.y = at(i).y;
            for(unsigned int i=0; i<size(); i++) if( at(i).x < a.x && at(i).y == a.y) a.x = at(i).x;

            // Winkel bestimmen und in w als Sortierkriterium Speichern
            double dx,dy;

            for(unsigned int i=0;i<size();i++)
            {
                dx = (at(i)-a).x;   dy = (at(i)-a).y;

                if( dy==0 && dx < 0) w[i] = (180.0*(M_PI/180.0));
                else if( dy==0 )     w[i] = 0.0;
                else if( dx==0 )     w[i] = (90.0*(M_PI/180.0));
                else
                {
                    w[i] = atan(dy/dx);
                    if( dx<0 )
                        w[i] += M_PI;
                }
            }

            // Sortieren des Polygons
            for(unsigned int i=0;i<size()-1;i++)
                for(unsigned int j=i+1;j<size();j++)
                    if(w[i] > w[j])
                    {
                        tw    = w[i];   a     = at(i);
                        w[i]  = w[j];   at(i) = at(j);
                        w[j]  = tw;     at(j) = a;
                    }

            // Speicher frei geben
            delete w;
        }

    private:
        int pnpoly(int npol, float *xp, float *yp, float x, float y)
        {
            int i, j, c = 0;
            for (i = 0, j = npol-1; i < npol; j = i++)
            {
              if ((((yp[i]<=y) && (y<yp[j])) || ((yp[j]<=y) && (y<yp[i]))) &&
                    (x < (xp[j] - xp[i]) * (y - yp[i]) / (yp[j] - yp[i]) + xp[i]))  c = !c;
            }
            return c;
        }
};

}
#endif
