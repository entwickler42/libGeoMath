#ifndef CMD_H
#define CMD_H

/*
    Autor  :    Stefan Brück
    E-Mail :    <mailbockx@freenet.de>
    Datum  :    260811

    ToDo   :
*/

//-----------------------------------------------------------------------------
template <class T> __export T max(const T& x, const T& y)
{
    return (x > y ? x : y);
}

//-----------------------------------------------------------------------------
template <class T> __export T min(const T& x, const T& y)
{
    return (x < y ? x : y);
}

#endif
