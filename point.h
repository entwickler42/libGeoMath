#ifndef POINT_H
#define POINT_H

#include "math.h"
#include <vector>

/*
    Autor  :    Stefan Brück
    E-Mail :    <mailbockx@freenet.de>
    Datum  :    030811

    ToDo   :    -
*/

using namespace std;

namespace std
{

template <class A, class B, class C> __export class Point
{
    public:
        A x; B y; C z;

        Point() {};

        Point(const A& x, const B& y, const C& z)
        {
            assign(x,y,z);
        }

        void operator = ( const Point<A,B,C>& p ) const
        {
            assign(p.x, p.y, p.z);
        }

        bool operator == ( const Point<A,B,C>& p ) const
        {
            return compare(p);
        }

        bool operator > ( const Point<A,B,C>& p ) const
        {
            return ( z > p.z );
        }

        bool operator < ( const Point<A,B,C>& p ) const
        {
            return ( z < p.z );
        }


        Point<A,B,C> operator - ( const Point<A,B,C>& p)
        {
            // x und y werden um x und y von p vermindert
            Point<A,B,C> tp(x,y,z);

            tp.x -= p.x;            tp.y -= p.y;

            return tp;
        }

        void operator -= ( const Point<A,B,C>& p)
        {
            // vektorisieren & zuweisen
            x -= p.x;            y -= p.y;
        }

        double distance(const Point<A,B,C>& p)
        {
            Point<A,B,C> tp(x,y,z);
            tp -= p;

            return sqrt((tp.x*tp.x)*(tp.y*tp.y));
        }

        inline void assign(const A& x, const B& y, const C& z)
        {
            // Hier bekommt ein objekt x,y und z Werte
            Point<A,B,C>::x = x;    Point<A,B,C>::y = y;    Point<A,B,C>::z = z;
        }

        inline bool compare( const Point<A,B,C>& p )
        {
            // Wenn x,y und z gleich sind gelten die Punkte als gleich ,)
            return ( x == p.x && y == p.y && z == p.z );
        }
};

// Default Typen
typedef Point<int, int, float> Point1f;
typedef Point<float, float, float> Point3f;

typedef std::vector<Point1f> Point1fVec;
typedef std::vector<Point3f> Point3fVec;

// Funktion zum testen ob ein vector aus Punkten einen Punkt enthält
template <class T> bool __export hasPoint(const vector<T>& v, const T& p)
{
    for(unsigned int i=0;i<v.size();i++) if( v[i] == p ) return true;

    return false;
};

// Funktion um einen Punktvector nach Wert z zu sortieren
template <class T> __export vector<T> sortPointsByHeight(const vector<T>& v)
{
    vector<T> sv = v;
    T         p(0,0,0);

    for(unsigned int i=0;i<sv.size()-1;i++)
        for(unsigned int j=i+1;j<sv.size();j++)
            if(sv[i].z > sv[j].z)
            {
                p = sv[i];
                sv[i] = sv[j];
                sv[j] = p;
            }

    return sv;
};

// Funktion um aus einem Punktvector alle Punkte zwischen 2 Kriterika zu extrahieren
template <class T> vector<T> __export pointsBetween(float min, float max, const vector<T>& v)
{
    vector<T> pb;

    for(unsigned int i=0;i<v.size();i++)
        if( (v[i].z > min) && (v[i].z <= max) ) pb.push_back(v[i]);

    return pb;
};

}

#endif
