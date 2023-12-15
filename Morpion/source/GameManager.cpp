#include "framework.hpp"

namespace MorpionGame {
    GameManager::GameManager(Server& server, Client& client) : gameActive(true), server(server), client(client) {
        // Initializing the game manager if necessary
        std::cout << "GameManager created." << std::endl;
    }

    void GameManager::startGame(std::string& playerName1, std::string& playerName2) {
        // Reset and start the game
        morpion.resetGame(playerName1, playerName2);
        std::cout << "Game restarted." << std::endl;
        endGamePopup.resetPopup();
    }

    void GameManager::handleInput(sf::Event& event, sf::RenderWindow& window, const std::string& param, std::string& playerName1, std::string& playerName2) {
        if (gameActive) {
            // Handle input events only if the game is running
            morpion.handleInput(event, window, playerName1, playerName2);
            chat.handleInput(event, window, param, server, client, playerName1, playerName2);
            endGamePopup.handleInput(event, window);
            // If the user wants to start again after the game ends
            // Add handling of clicking on the "Replay" button here
            if (endGamePopup.isRestartRequested()) {
                startGame(playerName1, playerName2);
            }
        } else {
            // Handle input events for endgame pop-up
            if (endGamePopup.isRestartRequested()) {
                // Reset the game here
                startGame(playerName1, playerName2);
            }

        }
    }

    void GameManager::update(const std::string& param, Server& server, Client& client) {
        if (gameActive) {
            // Update logic only if game is running
            chat.update(param, server, client);
            scoreManager = morpion.getScoreManager();
        }
    }

    void GameManager::draw(sf::RenderWindow& window, std::string& playerName1, std::string& playerName2) {
        // Draw the game elements
        morpion.draw(window);
        scoreManager.draw(window, playerName1, playerName2);
        endGamePopup.draw(window);
        chat.draw(window);

    }
}