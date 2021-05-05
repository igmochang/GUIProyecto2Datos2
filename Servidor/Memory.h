#ifndef MEMORY_H
#define MEMORY_H


#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include "listasimple.h"

/**
 * @brief Contains the memory logic of the program
 *  
 * @param tamano size in bytes of the malloc created 
 */
class Memory{
    public:
        void *memoryTotal;
        int memoryUsed;
	int tamanoT;
        int *entero;
        char *character;
        long *largo;
        float *flotante;
        double *doble;

        int contador;
    
    Memory(int tamano){
        if((memoryTotal = malloc(tamano))==NULL){
            std::cout << "No se pudo crear el espacio de memoria solicitado" << std::endl;
            tamanoT = tamano;
        } else{
            std::cout << "Espacio de memoria creado con: " << tamano << " bytes" << std::endl;
            
            entero = (int *)memoryTotal;
            character = (char *)memoryTotal;
            largo = (long *)memoryTotal;
            flotante = (float *)memoryTotal;
            doble = (double *)memoryTotal;
        }
    }
    bool Revisar(int);
    void* Agregar(std::string);
    void Eliminar();
    void Clear(void *);
};

/**
 * @brief Check if the size of the remaining memory is valid for create a new variable
 * @return boolean is surplus size memory
 */
bool Memory::Revisar(int espacio){
    if((memoryUsed+espacio) > tamanoT){
        std::cout << "Espacio en memoria insuficiente" << std::endl;
        return false;
    } else{
        return true;
    }
}

/**
 * @brief Add the new variable of the malloc with size of
 * @param espacio is the type of the variable
 * @return pointer of the memory location
 */
void* Memory::Agregar(std::string espacio){
    void *ptr;
    if(espacio == "int"){
        ptr = &entero[memoryUsed];
        contador += 1;
        memoryUsed += 4;
    }else if(espacio == "long"){
        ptr = &largo[memoryUsed];
        contador += 1;
        memoryUsed += 8;
    }else if(espacio == "char"){
        ptr = &character[memoryUsed];
        contador += 1;
        memoryUsed += 1;
    }else if(espacio == "float"){
        ptr = &flotante[memoryUsed];
        contador += 1;
        memoryUsed += 4;   
    }else if(espacio == "double"){
        ptr = &doble[memoryUsed];
        contador += 1;
        memoryUsed += 8;
    return ptr;
}
}

/**
 * @brief Delete the variable and delete the memory space
 * @param *prt pointer of the variable is allocated
 */
void Memory::Clear(void *ptr){
    free(ptr);
}

#endif
