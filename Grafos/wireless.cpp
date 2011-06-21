#include "wireless.h"

WireLess::WireLess()
{
    alcance=500.0;
    this->grafo = new Grafo(0,false);
    this->grafo->generarPosicionesRandom(3,3);
    this->grafo->calcularDistancias();
    this->removeAristasMayoresAlcance();



}

WireLess::WireLess(int nodos, float alcance,int ancho, int alto)
{
    this->alcance = alcance;
    this->grafo = new Grafo(nodos,false);
    this->grafo->generarPosicionesRandom(ancho,alto);
    //Esto calcula las distancias entre todo par de nodos
    this->grafo->calcularDistancias();
    // Sin embargo para efectos de la red inlambrica debemos
    // quitar todas aquellas aristas cuyo peso sea mayor al del alcance.
    this->removeAristasMayoresAlcance();


}

void WireLess::removeAristasMayoresAlcance()
{
    for (int i=0; i<this->grafo->getSize();i++)
    {
        for(int j=0; j<this->grafo->getSize();j++)
        {
            if (i!=j) // no son el mismo nodo
            {
              if(this->grafo->getPesoArista(i,j)> this->alcance)
                  this->grafo->removeArista(i,j);

            }

        }

    }
}
