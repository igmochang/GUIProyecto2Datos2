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
    ListaSimple<int> *listaPuntero = new ListaSimple<int>();

    std::tuple<std::string, std::string, int> TuplaG, TuplaTem;

    Memory *Memoria = new Memory(tamano);
    std::cout << "Puerto del servidor:  " << puerto << std::endl;
    Server *Servidor = new Server(puerto);

    std::string text, revisar, textSalida, puntero;
    int espacio, refe;
    char *limitF, *limitI;
    bool guardar, temporal;

    while(true){
    	textSalida = "";
    	guardar = false;
        if(double(clock()/CLOCKS_PER_SEC) > time){
            if(temporal == false && listaPuntero->size != 0){
                for(int i=0; i<=listaPuntero->size-1; i++){
                //void *ptrTem = listaPuntero->obtenerPos(i);
                //Memoria->Clear(ptrTem);
                //listaPuntero->eliminar(ptrTem);
            }}
            time += 10;
        }
        
        text = Servidor->Recibir();
        reader.parse(text, data);

        revisar = data["tipo"].asString();
        if(revisar == "int"){ espacio = 4; } else if(revisar == "long") { espacio = 8; }
        else if(revisar == "char"){ espacio = 1; } else if(revisar == "float") { espacio = 4; }
        else if(revisar == "double"){ espacio = 8; } 

        if(data["corchete"].asString() == "true"){ temporal = true; } else{ temporal = false; }

        if(Memoria->Revisar(espacio)){
            void *ptrMemoria = Memoria->Agregar(revisar);
            std::cout << ptrMemoria << std::endl;
            //char n = ptrMemoria;
            //std::string hola = std::to_string(n);
            refe = 1;
            TuplaG = std::make_tuple(data["nombre"].asString(), data["tipo"].asString(), 1);
            listaDatos->insertar(TuplaG);
            
            if(temporal){
		std::cout << "hola";
            }

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
            textSalida += ",\"referencia\":\"" + std::to_string(refe) + "\"}";


        } else{
            std::cout << "No hay espacio" << std::endl;
            text = "Null";
        }

        Servidor->Enviar(textSalida);
    }

    return 0;
}
