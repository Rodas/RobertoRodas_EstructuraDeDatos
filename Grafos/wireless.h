#ifndef WIRELESS_H
#define WIRELESS_H
#include "grafo.h"






class WireLess
{
public:
    WireLess(); // por default 10 nodos, y alcance de 5.0
    WireLess(int nodos, float alcance,int ancho, int alto);
    void setAlcance(float al) { alcance=al;}
    float getAlcance () { return alcance; }
    ~WireLess() { delete grafo;}   // Corre el destructor de grafo
    Grafo *grafo;
private:
    float alcance;
    void removeAristasMayoresAlcance();


};

#endif // WIRELESS_H
