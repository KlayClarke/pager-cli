#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "server.h"

Server::Server() {}

Server::~Server()
{
    close(serverSocket);
}

void Server::NewHub()
{
    std::cout << "Created new hub!" << std::endl;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    listen(serverSocket, 5);

    int clientSocket = accept(serverSocket, nullptr, nullptr);

    // recieving data
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Message from client: " << buffer << std::endl;
}

void Server::NewClient()
{
    std::cout << "Created new client!" << std::endl;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    connect(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    const char* message = "Hello, server!";
    send(serverSocket, message, strlen(message), 0);
}