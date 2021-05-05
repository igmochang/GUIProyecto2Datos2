#ifndef MEMORY_H
#define MEMORY_H


#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include "listasimple.h"

class Memory{
    public:
        void *memoryTotal;
        int *memoryUsed;

        int *entero;
        char *character;
        long *largo;
        float *flotante;
        double *doble;
        //void *reference;

        int contadorInt, contadorChar, contadorLong, contadorFloat, contadorDouble, contadoReference;
    
    Memory(int tamano){
        if((memoryTotal = malloc(tamano))==NULL){
            std::cout << "No se pudo crear el espacio de memoria solicitado" << std::endl;
        } else{
            std::cout << "Espacio de memoria creado con: " << tamano << " bytes" << std::endl;
            
            entero = (int *)memoryTotal;
            character = (char *)memoryTotal;
            largo = (long *)memoryTotal;
            flotante = (float *)memoryTotal;
            doble = (double *)memoryTotal;
            //reference = (void *)memoryTotal;
        }
    }
    bool Revisar(int);
    void* Agregar(std::string);
    void Eliminar();
    void Clear(void *);
};

bool Memory::Revisar(int espacio){
    if((memoryUsed+espacio) > memoryTotal){
        std::cout << "Espacio en memoria insuficiente" << std::endl;
        return false;
    } else{
        return true;
    }
}

void* Memory::Agregar(std::string espacio){
    void *ptr;
    if(espacio == "int"){
        ptr = &entero[memoryUsed];
        contadorInt += 1;
        memoryUsed += 4;
    }else if(espacio == "long"){
        ptr = &largo[contadorLong];
        contadorLong += 1;
        memoryUsed += 8;
    }else if(espacio == "char"){
        ptr = &character[contadorChar];
        contadorChar += 1;
        memoryUsed += 1;
    }else if(espacio == "float"){
        ptr = &flotante[contadorFloat];
        contadorFloat += 1;
        memoryUsed += 4;   
    }else if(espacio == "double"){
        ptr = &doble[contadorDouble];
        contadorDouble += 1;
        memoryUsed += 8;
    }/*else if(espacio == "reference"){
        ptr = &reference[contadoReference];
        contadoReference += 1;
        memoryUsed += 4;
    }*/
    return ptr;
}

void Memory::Clear(void *ptr){
    free(ptr);
}

#endif