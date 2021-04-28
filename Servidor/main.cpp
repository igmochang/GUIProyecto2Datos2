#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <cstdlib>
#include <malloc.h>
#include <ctime>
#include <tuple>
#include "Server.h"
#include "Memory.h"
#include "listasimple.h"


int main(int argc, char *argv[]){

    int time = 10;
    int tamano = atoi(argv[2]);
    int puerto = atoi(argv[1]);
    Json::Reader reader;
    Json::Value data;
    ListaSimple<std::tuple<std::string, std::string, int>> * listaDatos = new ListaSimple<std::tuple<std::string, std::string, int>>();
    std::tuple<std::string, std::string, int> TuplaG, TuplaTem;

    Memory *Memoria = new Memory(tamano);
    std::cout << "Puerto del servidor:  " << puerto << std::endl;
    Server *Servidor = new Server(puerto);

    std::string text, revisar, textSalida;
    int espacio;
    char *limitF, *limitI;
    bool guardar;

    while(true){
    	textSalida = "";
    	guardar = false;
        if(double(clock()/CLOCKS_PER_SEC) > time){
            Memoria->Clear();
            time += 10;
        }
        
        text = Servidor->Recibir();
        reader.parse(text, data);

        revisar = data["tipo"].asString();

        if(revisar == "int") espacio = 4;
        else if(revisar == "long") espacio = 8;
        else if(revisar == "char") espacio = 1;
        else if(revisar == "float") espacio = 4;
        else if(revisar == "double") espacio = 8;
        else if(revisar == "reference") espacio = 4;

        if(Memoria->Revisar(espacio)){
            void *ptrMemoria = Memoria->Agregar(revisar);
            std::cout << ptrMemoria << std::endl;

            TuplaG = std::make_tuple(data["nombre"].asString(), data["tipo"].asString(), 1);
            listaDatos->insertar(TuplaG);

            for(int i=0; i<=listaDatos->size-1; i++){
                TuplaTem = listaDatos->obtenerPos(i);
                std::cout << std::get<0>(TuplaTem) << " " << std::get<1>(TuplaTem) << std::endl;
            }


            limitF = "}";
            limitI = "{";
            for(int i=0; i<(text.length()); i++){
            	if(text[i] == *limitF && guardar == true){
            		guardar = false;
            	}
            	else if(text[i] == *limitI && guardar == false){
           		textSalida += text[i];
           		guardar = true;
            	}else if(guardar == true){
            		textSalida += text[i];
            	}
            }
            textSalida += ",\"memoria\":\"0x102300\"";
            textSalida += ",\"referencia\":\"1\"}";


        } else{
            std::cout << "No hay espacio" << std::endl;
            text = "Null";
        }

        Servidor->Enviar(textSalida);
    }

    return 0;
}
