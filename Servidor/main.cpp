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
    ListaSimple<std::tuple<std::string, std::string, int, *void>> * listaDatos = new ListaSimple<std::tuple<std::string, std::string, int, *void>>();
    std::tuple<std::string, std::string, int, *void> TuplaG, TuplaTem;

    Memory *Memoria = new Memory(tamano);

    Server *Servidor = new Server(puerto);
    std::cout << "Puerto del servidor:  " << puerto << std::endl;

    std::string text, revisar, textSalida;
    int espacio;
    char *limit;

    while(true){
    	textSalida = "";
        if(double(clock()/CLOCKS_PER_SEC) > time){
            Memoria->Clear();
            time += 10;
        }
        
        text = Servidor->Recibir();
        reader.parse(text, data);

        revisar = data["Tipo"];

        if(revisar == "int") espacio = 4;
        else if(revisar == "long") espacio = 8;
        else if(revisar == "char") espacio = 1;
        else if(revisar == "float") espacio = 4;
        else if(revisar == "double") espacio = 8;
        else if(revisar == "reference") espacio = 4;

        if(Memoria->Revisar(espacio)){
            void *ptrMemoria = Memoria->Agregar(revisar);
            std::cout << ptrMemoria << std::endl;

            TuplaG = std::make_tuple(data["nombre"], data["tipo"], 1, ptrMemoria);
            listaDatos->insertar(TuplaG);

            for(int i=0; i<=listaDatos->size; i++){
                TuplaTem = listaDatos->obtenerPos(i);
                std::cout << std::get<0>(TuplaTem) << " " << std::get<3> << endl;
            }


            limit = "}";
            for(int i=0; i<(text.length()-2); i++){
            	if(text[i] != *limit){
           		textSalida += text[i];
            	} }
            textSalida += ",\"Memoria\":\"0x102300\"";
            textSalida += ",\"Referencia\":\"1\"";
            std::cout << textSalida << std::endl;


        } else{
            std::cout << "No hay espacio" << std::endl;
            text = "Null";
        }

        Servidor->Enviar(textSalida);
    }

    return 0;
}
