/**
 * @file Client.h
 * @author Johnny Aguero
 * @brief Create the Client socket and the necessary logic
 * @version 0.1
 * @date 2021-05-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <QString>


/**
 * @brief create the client socket
 */
class Client{
    public:
        int bufsize = 1024;
        char buffer[1024];
        int client;
        int portNum = 1500;
        const char* ip = "127.0.0.1";
        Json::Reader reader;
        Json::Value dataR, dataS;
        Json::StyledWriter writer;
    
    //Constructor
    Client(){
        struct sockaddr_in server_addr;
        client = socket(AF_INET, SOCK_STREAM, 0);

        if (client < 0){
            std::cout << "\nError al establecer el socket" << std::endl;
            exit(1);
        }

        std::cout << "\n=> Socket del cliente creado" << std::endl;
        
        server_addr.sin_addr.s_addr = inet_addr(ip);
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(portNum);

        if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
            std::cout << "=> Conectando al servidor en el puerto: " << portNum << std::endl;
        
        std::cout << "=> Esperando confirmacion" << std::endl;
        recv(client, buffer, bufsize, 0);
        std::cout << "=> conexion confirmada  ";  
        std::cout << buffer << std::endl;
    }

    //Metodos
    std::array<std::string, 5> Recibir();
    void Enviar(std::string);

};

/**
 * @brief Receive the menssage of the server
 * @return string array that contains data
 */
std::array<std::string, 5> Client::Recibir(){
    int bufsizeR = 1024;
    char bufferR[1024];

    recv(client, bufferR, bufsizeR, 0);
    std::string text = bufferR;

    reader.parse(text, dataR);
    std::string mem = dataR["memoria"].asString();
    std::string ref = dataR["referencia"].asString();
    std::string nom = dataR["nombre"].asString();
    std::string val = dataR["valor"].asString();
    std::string tipo = dataR["tipo"].asString();

    std::array<std::string, 5> data {{tipo, nom, val, mem, ref}};

    return data;
    
}

/**
 * @brief send the menssage of the server
 * @return string menssage to send at the server.
 */
void Client::Enviar(std::string text){
    int bufsizeS = 1024;
    char bufferS[1024];
    reader.parse(text, dataS);
    std::string data = writer.write(dataS);
    std::copy(data.begin(), data.end(), bufferS);
    send(client, bufferS, bufsizeS, 0);
}

#endif
