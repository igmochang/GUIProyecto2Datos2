#include <iostream>
#include <cstdlib>
#include <malloc.h>
//#include "Server.h"
#include "Memory.h"
#include <ctime>


int main(int argc, char *argv[]){

    int time = 10;
    int tamano = 1024;
    //int tamano = atoi(argv[2]);
    //int puerto = atoi(argv[1]);

    //std::cout << "Puerto del servidor:  " << puerto << std::endl;
    
    //Server *Servidor = new Server(puerto);
    Memory *Memoria = new Memory(tamano);
    std::string text, revisar;
    int espacio;

    while(true){
        if(double(clock()/CLOCKS_PER_SEC) > time){
            Memoria->Clear();
            time += 10;
        }
        
        revisar = "long";
        //text, revisar = Servidor->Recibir();
        if(revisar == "int") espacio = 4;
        else if(revisar == "long") espacio = 8;
        else if(revisar == "char") espacio = 1;
        else if(revisar == "float") espacio = 4;
        else if(revisar == "double") espacio = 8;
        else if(revisar == "reference") espacio = 4;
        if(Memoria->Revisar(espacio)){
            void *ptrMemoria = Memoria->Agregar(revisar);
            std::cout << ptrMemoria << std::endl;
        } else{
            std::cout << "No hay espacio" << std::endl;
            text = "Null";
        }

        //Servidor->Enviar(text);
    }

    return 0;
}
