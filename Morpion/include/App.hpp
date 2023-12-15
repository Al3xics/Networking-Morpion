#pragma once

#include "Client.hpp"
#include "GameManager.hpp"
#include "Server.hpp"

namespace MorpionGame {
    /**
     * @brief The App class represents the Morpion application, which can act as both a server and a client.
    */
    class App {
    public:
        /**
         * @brief Constructor for the MorpionApp class.
         * @param serverIP : IP adress of the server.
         * @param serverPort : Port of the server.
        */
        App(const std::string& serverIP, const std::string& serverPort);
        /**
         * @brief Destructor of the MorpionApp class.
        */
        ~App();


        /**
         * @brief Initialize Winsock.
        */
        void initWinsock();
        /**
         * @brief Launch the server for the morpion.
        */
        void runServer();
        /**
         * @brief Launch the client for the morpion.
        */
        void runClient();

    private:
        sf::RenderWindow window; /** @brief SFML RenderWindow for graphical interface. */
        GameManager gameManager{ server, client }; /** @brief Game manager for Morpion. */

        WSADATA wsadata; /** @brief Stock version of Winsock */
        const std::string& serverIP; /** @brief IP of the server. */
        const std::string& serverPort; /** @brief Port of the server. */
        int iResult = 0; /** @brief result of different operations. */
        Server server{ serverPort }; /** @brief Initialize a server. */
        Client client{ serverIP, serverPort }; /** @brief Initialize a client. */
    };
}