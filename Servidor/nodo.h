//
// Created by ignacio on 8/3/21.
//
#include <cstdlib>

#ifndef NODO_H
#define NODO_H

class Nodo {
public:
    // Atributos
    int dato[1];
    Nodo * siguiente;


    // Constructores
    Nodo(){
        dato[0];
        dato[1];
        siguiente = NULL;
    }

    Nodo(int _dato, int referencia){
        dato[0] = _dato;
        dato[1] = referencia;
        siguiente = NULL;
    }

    Nodo(int _dato, int referencia, Nodo * _siguiente){
        dato[0] = _dato;
        dato[1] = referencia;
        siguiente = _siguiente;
    }

    void * operator new(size_t size){
        void * p = ::new Nodo();
        return p;
    }

    void operator delete(void * p){
        free(p);
    }

    void modifD(int _dato){
        dato[0] = _dato;
    }
    
    void modifR(int referencia){
        dato[1] = referencia;
    }

    int consulta(){
        return dato[0], dato[1];
    }
};

#endif
