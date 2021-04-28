//
// Created by ignacio on 8/3/21.
//

#ifndef NODO_H
#define NODO_H

#include <stddef.h>

template<class DATO>
class Nodo {
public:
    DATO dato;
    Nodo<DATO> * siguiente;


    // Constructores
    Nodo(){
        dato;
        siguiente = NULL;
    }

    Nodo(DATO _dato){
        dato = _dato;
        siguiente = NULL;
    }

    Nodo(DATO _dato, Nodo<DATO> * _siguiente){
        dato = _dato;
        siguiente = _siguiente;
    }

    void operator delete(void * p){
        free(p);
    }

    void modif(DATO _dato){
        dato = _dato;
    }

    DATO consulta(){
        return dato;
    }
};

#endif
