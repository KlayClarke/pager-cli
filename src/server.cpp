#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <vector>
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

    std::vector<pollfd> fds = std::vector<pollfd>();
    fds.push_back({serverSocket, POLLIN, 0});

    nfds_t nfds = 0;
    int pollTimeout = 0;

    while (poll(fds.data(), fds.size(), pollTimeout) >= 0)
    {
        for (size_t i = 0; i < fds.size(); i++)
        {
            int curFd = fds[i].fd;
            int curRevents = fds[i].revents;
            if (curFd == serverSocket) {
                if (curRevents & POLLIN) {
                    int clientSocket;
                    if ((clientSocket = accept(serverSocket, nullptr, nullptr)) > 0) 
                    {
                        fds.push_back({clientSocket, POLLOUT, 0});
                    }
                }
            } else {
                std::cout << "curRevents: " << curRevents << std::endl;
                if (curRevents & 0x38) continue; // Skip if POLLERR, POLLHUP, POLLNVAL set
                else if (curRevents & POLLOUT) {
                    char buffer[1024] = {0};
                    recv(curFd, buffer, sizeof(buffer), 0);
                    std::cout << "Message from client " << curFd << ": " << buffer << std::endl;
                }
            }
        }
    };
}
// BUG: HUB only receives bytes after I close connection and start up again
// ^ NEED TO REMOVE CLOSED SESSIONS FROM FDS
// 00111000

void Server::NewClient()
{
    std::cout << "Created new client!" << std::endl;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    connect(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    std::string message = "";
    while (true) {
        std::cout << "Type q to quit. Anything else will be sent to hub" << std::endl;
        std::cin >> message;
        
        if (message == "q") break;

        int bytesSent = send(serverSocket, message.data(), message.size(), 0);
        std::cout << bytesSent << " bytes sent to hub" << std::endl;
    }
}