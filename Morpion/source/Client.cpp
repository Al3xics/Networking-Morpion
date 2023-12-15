#include "Client.hpp"

namespace MorpionGame {
    Client::Client(const std::string& serverIP, const std::string& serverPort) : serverIP(serverIP), serverPort(serverPort) {}

    Client::~Client() {
        freeaddrinfo(result); // free the memory allocated by getaddrinfo()
        closesocket(connectSocket);
    }

    void Client::createSocket() {
        ZeroMemory(&hints, sizeof(hints)); // initialize hints to zero
        hints.ai_family = AF_INET; // we are looking for IPv4 addresses
        hints.ai_socktype = SOCK_STREAM; // we are looking for flow type socket (TCP)
        hints.ai_protocol = IPPROTO_TCP; // we are looking for TCP protocols

        iResult = getaddrinfo(serverIP.c_str(), serverPort.c_str(), &hints, &result); // get data associated to the 'serverIP', and stock it in 'result'
        if (iResult != 0) {
            std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
            throw std::runtime_error("getaddrinfo failed !");
        }

        connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol); // create a socket

        if (connectSocket == INVALID_SOCKET) {
            std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
            throw std::runtime_error("client socket creation failed !");
        }
    }

    void Client::connectToServer() {
        iResult = connect(connectSocket, result->ai_addr, (int)result->ai_addrlen); // connect to server
        if (iResult == SOCKET_ERROR) {
            connectSocket = INVALID_SOCKET;
            std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
            throw std::runtime_error("failed to connect to the server !");
        }
    }

    bool Client::sendDataToServer(const std::string& input) {
        if (!input.empty() && input.find_first_not_of(' ') != std::string::npos) {
            iResult = send(connectSocket, input.c_str(), static_cast<int>(input.size()), 0);
            if (iResult == SOCKET_ERROR) {
                std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
                throw std::runtime_error("error sending data to server !");
            }
        }
        return iResult > 0;
    }

    bool Client::isDataAvailable() {
        // Implement logic to check if data is available for non-blocking receive
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(connectSocket, &readSet);

        timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        int result = select(static_cast<int>(connectSocket) + 1, &readSet, nullptr, nullptr, &timeout);

        return (result > 0 && FD_ISSET(connectSocket, &readSet));
    }

    std::string Client::tryReceiveDataFromServer() {
        if (isDataAvailable()) {
            iResult = recv(connectSocket, receiveBuffer, sizeof(receiveBuffer), 0);

            if (iResult == 0) {
                std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
                throw std::runtime_error("connection closed by server !");
            } else if (iResult < 0) {
                std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
                throw std::runtime_error("error receiving data from the server !");
            }

            return std::string(receiveBuffer, receiveBuffer + iResult);
        }

        return "";
    }

}