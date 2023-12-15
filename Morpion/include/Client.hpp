#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <WinSock2.h>
#include <WS2tcpip.h>

namespace MorpionGame {
    /**
     * @brief The Client class represents a client for the game.
     */
    class Client {
    public:
        /**
         * @brief Constructor for the Client class.
         * @param serverIP : IP adress of the server.
         * @param serverPort : Port of the server.
        */
        Client(const std::string& serverIP, const std::string& serverPort);
        /**
         * @brief Destructor of the Client class.
        */
        ~Client();

        /**
         * @brief Create the socket used by the client.
        */
        void createSocket();
        /**
         * @brief Connect the client to the server.
        */
        void connectToServer();
        /**
         * @brief Send data to the server.
         * @param input : Data to send.
         * @return If data is sent, return true, else false.
        */
        bool sendDataToServer(const std::string& input);
        /**
         * @brief Check if data is available.
         * @return True if yes, else false.
        */
        bool isDataAvailable();
        /**
         * @brief Receive data from the server.
         * @return The data received from the server.
        */
        std::string tryReceiveDataFromServer();


    private:
        const std::string& serverIP; /** @brief IP of the server. */
        const std::string& serverPort; /** @brief Port of the server. */
        int iResult = 0; /** @brief result of different operations. */
        struct addrinfo* result = NULL, hints; /** @brief Stock data retrived with 'getaddrinfo()'. result : pointer to a struct (stock information)   |   hints : stock data */
        SOCKET connectSocket = INVALID_SOCKET; /** @brief The client socket. */
        char receiveBuffer[1024]; /** @brief Buffer to receive data. */
    };
}