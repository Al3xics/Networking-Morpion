#include "framework.hpp"
#include <stdexcept>

#pragma comment(lib, "Ws2_32.lib")


/*
Usefull link to understand Client/Server connection :
https://learn.microsoft.com/en-us/windows/win32/winsock/about-clients-and-servers
*/

/**
 * @brief The main function of the program.
 * @param argc : The number of command-line arguments.
 * @param argv : An array of command-line arguments.
 * @return An integer representing the exit status of the program.
*/
int main(int argc, char* argv[]) {
    try {
        // ---------- Request IP and Port to the user ----------
        ////std::cout << "Entrez l'adresse IP du serveur : ";
        ////std::cin >> serverIP;
        ////std::cout << "Entrez le port du serveur : ";
        ////std::cin >> serverPort;

        // Default server IP and port for demonstration purposes
        std::string serverIP = "127.0.0.1";
        std::string serverPort = "1111";

        // Initialize the application and launch it
        MorpionGame::App morpion{ serverIP, serverPort };
        if (argc > 1 && std::strcmp(argv[1], "server") == 0) {
            // ---------- Launch Server ----------
            morpion.runServer();


        } else if (argc > 1 && std::strcmp(argv[1], "client") == 0) {
            // ---------- Launch Client ----------
            morpion.runClient();
            

        } else {
            std::cout << "Please choose between those argument :\n\tserver\n\tclient" << std::endl;
        }
    } catch (std::exception e) {
        std::cout << e.what();
    }

    return 0;
} 