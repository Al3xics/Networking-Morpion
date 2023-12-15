#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>

namespace MorpionGame {
    /**
     * @brief The Server class represents a simple TCP server for MorpionGame.
     */
    class Server {
    public:
        /**
         * @brief Constructor for the Server class.
         * @param serverPort : Port of the server.
        */
        Server(const std::string& serverPort);
        /**
         * @brief Destructor of the Server class.
        */
        ~Server();

        /**
         * @brief Create the socket used by the server.
        */
        void createSocket();
        /**
         * @brief Bind the server socket to a network.
        */
        void bindSocket();
        /**
         * @brief Listen for any attempt to connect to server.
        */
        void listenOnSocket();
        /**
         * @brief Accept the connection to the client.
        */
        void acceptConnection();
        /**
         * @brief Check if data is available.
         * @return True if yes, else false.
        */
        bool isDataAvailable();
        /**
         * @brief Try to receive data from the client.
         * @return The data received from the client.
        */
        std::string tryReceiveDataFromClient();
        /**
         * @brief Send data to the client.
         * @param input : Data to send.
         * @return If data is sent, return true, else false.
        */
        bool sendDataToClient(const std::string& input);


    private:
        const std::string& serverPort; /** @brief Port of the server. */
        int iResult, iSendResult = 0; /** @brief result of different operations. */
        struct addrinfo* result = NULL, hints; /** @brief Stock data retrived with 'getaddrinfo()'. result : pointer to a struct (stock information)   |   hints : stock data */
        SOCKET listenSocket = INVALID_SOCKET; /** @brief The listening socket. */
        SOCKET clientSocket = INVALID_SOCKET; /** @brief Temporary client socket. */
        char receiveBuffer[1024]; /** @brief Buffer to receive data. */
    };
}