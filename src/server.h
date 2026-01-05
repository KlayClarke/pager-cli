#ifndef SERVER_H
#define SERVER_H

enum ServerTypes {
    Hub,
    Client,
    Uninitialized
};

class Server
{
private:
    int serverSocket;
public:
    Server();
    ~Server();
    
    void NewHub();
    void NewClient();
};

#endif //SERVER_H