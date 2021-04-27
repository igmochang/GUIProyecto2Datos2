//
// Created by ignacio on 8/3/21.
//

#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include "nodo.h"

class ListaSimple {

private:

public:
    Nodo * inicio;

    // Constructores
    ListaSimple(){
        inicio = NULL;
    }

    // Metodos
    void insertarAlInicio(int, int);
    bool estaVacia();
    int buscar(int);
    void eliminar(int);
    void eliminarPos(int);
};

void ListaSimple::insertarAlInicio(int _dato, int referencia){
    if (inicio == NULL) {
        inicio = new Nodo(_dato, referencia);
    }else {
        Nodo * nuevo = new Nodo(_dato, referencia);
        nuevo->siguiente = inicio;
        inicio = nuevo;
    }
}

void ListaSimple::eliminar(int _dato){
    if (!estaVacia()){
        if (_dato == inicio->dato[0]) {
            Nodo * eliminado = inicio;
            inicio = inicio->siguiente;
            eliminado->siguiente = NULL;
            delete eliminado;
        }
        else {
            Nodo * nodo_anterior = inicio;
            Nodo * tmp;
            tmp = inicio;
            while (tmp != NULL){
                if (tmp->dato[0] == _dato){
                    nodo_anterior->siguiente = tmp->siguiente;
                    tmp->siguiente = NULL;
                    delete tmp;
                }
                nodo_anterior = tmp;
                tmp = tmp->siguiente;
            }
        }
    }
}


void ListaSimple::eliminarPos(int Pos){
    if (!estaVacia()){
        if(Pos == 0){
            Nodo * eliminado = inicio;
            inicio = inicio->siguiente;
            eliminado->siguiente = NULL;
            delete eliminado;
        } else{
            Nodo * nodo_anterior = inicio;
            Nodo * tmp;
            tmp = inicio;
            int i;
            while (tmp != NULL && i < Pos){
                nodo_anterior = tmp;
                tmp = tmp->siguiente;
                i += 1;
            }
            nodo_anterior->siguiente = tmp->siguiente;
            tmp->siguiente = NULL;
            delete tmp;
        }
    }
}

bool ListaSimple::estaVacia(){
    return inicio == NULL;
}

int ListaSimple::buscar(int referencia){
    if (!estaVacia()){
        Nodo * tmp = inicio;
        int i=1;
        while (tmp != NULL){
            if (tmp->dato[1] == referencia){
                return i;
            }
            i += 1;
            tmp = tmp->siguiente;
        }
    }
}

#endif