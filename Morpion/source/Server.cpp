#include "Server.hpp"

namespace MorpionGame {
    Server::Server(const std::string& serverPort) : serverPort(serverPort) {}

    Server::~Server() {
        freeaddrinfo(result); // free the memory allocated by getaddrinfo()
        closesocket(listenSocket);
    }

    void Server::createSocket() {
        ZeroMemory(&hints, sizeof(hints)); // initialize hints to zero
        hints.ai_family = AF_INET; // we are looking for IPv4 addresses
        hints.ai_socktype = SOCK_STREAM; // we are looking for flow type socket (TCP)
        hints.ai_protocol = IPPROTO_TCP; // we are looking for TCP protocols
        hints.ai_flags = AI_PASSIVE; // indicates that we intend to use the returned socket structure in a call to the bind function

        iResult = getaddrinfo(NULL, serverPort.c_str(), &hints, &result);
        if (iResult != 0) {
            std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
            throw std::runtime_error("getaddrinfo failed !");
        }

        listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

        if (listenSocket == INVALID_SOCKET) {
            std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
            throw std::runtime_error("server socket creation failed !");
        }
    }

    void Server::bindSocket() {
        iResult = bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
            throw std::runtime_error("bind server socket failed !");
        }
    }

    void Server::listenOnSocket() {
        iResult = listen(listenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR) {
            std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
            throw std::runtime_error("listen on server socket failed !");
        }
    }

    void Server::acceptConnection() {
        clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
            throw std::runtime_error("accept client socket failed !");
        }
    }

    bool Server::isDataAvailable() {
        // Implement logic to check if data is available for non-blocking receive
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(clientSocket, &readSet);

        timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        int result = select(static_cast<int>(clientSocket) + 1, &readSet, nullptr, nullptr, &timeout);

        return (result > 0 && FD_ISSET(clientSocket, &readSet));
    }

    std::string Server::tryReceiveDataFromClient() {
        if (isDataAvailable()) {
            iResult = recv(clientSocket, receiveBuffer, sizeof(receiveBuffer), 0);

            if (iResult == 0) {
                std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
                throw std::runtime_error("connection closing...");
            } else if (iResult < 0) {
                std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
                throw std::runtime_error("error receiving data from the client !");
            }

            return std::string(receiveBuffer, receiveBuffer + iResult);
        }

        return "";
    }

    bool Server::sendDataToClient(const std::string& input) {
        if (!input.empty() && input.find_first_not_of(' ') != std::string::npos) {
            iSendResult = send(clientSocket, input.c_str(), static_cast<int>(input.size()), 0);
            if (iSendResult == SOCKET_ERROR) {
                std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
                throw std::runtime_error("error sending data to client !");
            }
        }
        return iResult > 0;
    }

}