#include "framework.hpp"

namespace MorpionGame {
    App::App(const std::string& serverIP, const std::string& serverPort) : window(sf::VideoMode(780, 520), "TicTacTech", sf::Style::Close), serverIP(serverIP), serverPort(serverPort) {
        initWinsock();
    }

    App::~App() {
        WSACleanup();
    }

    void App::initWinsock() {
        iResult = WSAStartup(MAKEWORD(2, 2), &wsadata); // MAKEWORD(2,2) --> request version 2.2 of Winsock
        if (iResult != 0) {
            std::cout << "WSAGetLastError : " << WSAGetLastError() << std::endl;
            throw std::runtime_error("WSAStartup failed !");
        }
    }

    void App::runServer() {
        try {
            std::cout << "****************\n*    SERVER    *\n****************\n\n";

            std::string playerName1, playerName2;
            std::cout << "Enter your name :" << std::endl;
            std::cin >> playerName1;

            server.createSocket();
            server.bindSocket();
            server.listenOnSocket();
            server.acceptConnection();

            server.sendDataToClient(playerName1);

            while (true) {
                std::string receivedData = server.tryReceiveDataFromClient();
                if (!receivedData.empty()) {
                    playerName2 = receivedData;
                    break;
                }
            }

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        std::cout << "Window closed" << std::endl;
                    }

                    // Manage input events using the GameManager
                    //std::cout << "Event type: " << event.type << std::endl;   // To find out the input type of an input
                    gameManager.handleInput(event, window, "server", playerName1, playerName2);

                }

                if (!window.isOpen()) {
                    break; // Exit the loop if the window is closed
                }

                // Update the logic using the GameManager
                gameManager.update("server", server, client);

                // Clear the screen
                window.clear(sf::Color(16, 112, 129));

                // Draw game elements using GameManager
                gameManager.draw(window, playerName1, playerName2);

                // Show what was drawn
                window.display();
            }

            std::cout << "\n\n****************\n*    SERVER    *\n****************";
        } catch (std::exception e) {
            std::cout << "Error : " << e.what() << std::endl;
        }
    }

    void App::runClient() {
        try {
            std::cout << "****************\n*    CLIENT    *\n****************\n\n";

            std::string playerName1, playerName2;
            std::cout << "Enter your name :" << std::endl;
            std::cin >> playerName2;

            client.createSocket();
            client.connectToServer();

            client.sendDataToServer(playerName2);

            while (true) {
                std::string receivedData = client.tryReceiveDataFromServer();
                if (!receivedData.empty()) {
                    playerName1 = receivedData;
                    break;
                }
            }

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        std::cout << "Window closed" << std::endl;
                    }

                    // Manage input events using the GameManager
                    //std::cout << "Event type: " << event.type << std::endl;   // To find out the input type of an input
                    gameManager.handleInput(event, window, "client", playerName1, playerName2);

                }

                if (!window.isOpen()) {
                    break; // Exit the loop if the window is closed
                }

                // Update the logic using the GameManager
                gameManager.update("client", server, client);

                // Clear the screen
                window.clear(sf::Color(16, 112, 129));

                // Draw game elements using GameManager
                gameManager.draw(window, playerName1, playerName2);

                // Show what was drawn
                window.display();
            }

            std::cout << "\n\n****************\n*    CLIENT    *\n****************";
        } catch (std::exception e) {
            std::cout << "Error : " << e.what() << std::endl;
        }
    }

}