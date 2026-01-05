#include <iostream>
#include <cstring>
#include "server.h"

int main(int argc, char **argv) {
    ServerTypes serverType = Uninitialized;
    if (argc > 2) {
        for (size_t i = 0; i < argc; i++)
        {
            if (argc > i+1 & std::strcmp(argv[i], "-st") == 0) {
                if (std::strcmp(argv[i+1], "hub") == 0) serverType = Hub;
                else if (std::strcmp(argv[i+1], "client") == 0) serverType = Client;
                break;
            }
        }
    } else {
        std::cout << "Insufficient arguments. Expected --server-type arg with either 'hub' or 'client'. Exiting!" << std::endl;
        return EXIT_FAILURE;
    }

    Server serv;
    switch (serverType)
    {
    case Hub:
        serv.NewHub();
        break;
    case Client:
        serv.NewClient();
        break;
    default:
        std::cout << "Bad server type. Expected --server-type arg with either 'hub' or 'client'. Exiting!" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}