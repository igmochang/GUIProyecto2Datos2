//
// Created by ignacio on 8/3/21.
//

#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include "nodo.h"
#include <stddef.h>

template<class DATO>
class ListaSimple {

private:

public:
    Nodo<DATO> * inicio;
    int size;

    // Constructores
    ListaSimple(){
        inicio = NULL;
    }

    // Metodos
    void insertar(DATO);
    bool estaVacia();
    void eliminar(DATO);
    DATO obtenerPos(int);
};

template<class DATO>
void ListaSimple<DATO>::insertar(DATO _dato){
    if (inicio == NULL) {
        inicio = new Nodo<DATO>(_dato);
        size += 1;
    }else {
        Nodo<DATO> * tmp = inicio;
        while (tmp->siguiente != NULL){
            tmp = tmp->siguiente;
        }
        Nodo<DATO> * nuevo = new Nodo<DATO>(_dato);
        tmp->siguiente = nuevo;
        nuevo->siguiente = NULL;
        size += 1;
    }
}

template<class DATO>
void ListaSimple<DATO>::eliminar(DATO _dato){
    if (!estaVacia()){
        if (_dato == inicio->dato) {
            Nodo<DATO> * eliminado = inicio;
            inicio = inicio->siguiente;
            eliminado->siguiente = NULL;
            delete eliminado;
            size -= 1;
        }
        else {
            Nodo<DATO> * nodo_anterior = inicio;
            Nodo<DATO> * tmp;
            tmp = inicio;
            while (tmp != NULL){
                if (tmp->dato == _dato){
                    nodo_anterior->siguiente = tmp->siguiente;
                    tmp->siguiente = NULL;
                    delete tmp;
                    size -= 1;
                }
                nodo_anterior = tmp;
                tmp = tmp->siguiente;
            }
        }
    }
}


template<class DATO>
DATO ListaSimple<DATO>::obtenerPos(int Pos){
    Nodo<DATO> *tmp = inicio;
    int i=0;
    if(tmp != NULL){
        if(Pos == 0){
            return tmp->dato;
        }
        while(i < Pos && i <= size){
            tmp = tmp->siguiente;
            i += 1; 
    }   return tmp->dato; 
    }
}

template<class DATO>
bool ListaSimple<DATO>::estaVacia(){
    return inicio == NULL;
}


#endif
