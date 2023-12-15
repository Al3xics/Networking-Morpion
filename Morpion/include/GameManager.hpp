#pragma once

#include "Chat.hpp"
#include "Client.hpp"
#include "EndGamePopup.hpp"
#include "Morpion.hpp"
#include "ScoreManager.hpp"
#include "Server.hpp"

namespace MorpionGame {
    /**
     * @brief The GameManager class manages the overall game flow, including the game, score management, chat, and endgame pop-up.
     */
    class GameManager {
    public:
        /**
         * @brief Constructor for the GameManager class.
         * @param server : Reference to the server instance.
         * @param client : Reference to the client instance.
         */
        GameManager(Server& server, Client& client);

        /**
         * @brief Start a new game.
         * @param playerName1 : The name of the first player.
         * @param playerName2 : The name of the second player.
         */
        void startGame(std::string& playerName1, std::string& playerName2);
        /**
         * @brief Handle input events for the GameManager.
         * @param event : SFML event to handle.
         * @param window : SFML window for input handling.
         * @param param : Parameter indicating whether the GameManager is handling input for the server or client.
         * @param playerName1 : The name of the first player.
         * @param playerName2 : The name of the second player.
         */
        void handleInput(sf::Event& event, sf::RenderWindow& window, const std::string& param, std::string& playerName1, std::string& playerName2);
        /**
         * @brief Update the state of the GameManager.
         * @param param : Parameter indicating whether the GameManager is updating for the server or client.
         * @param server : Reference to the server instance.
         * @param client : Reference to the client instance.
         */
        void update(const std::string& param, Server& server, Client& client);
        /**
         * @brief Draw the game elements, scores, and chat on the SFML window.
         * @param window : SFML window for drawing.
         * @param playerName1 : The name of the first player.
         * @param playerName2 : The name of the second player.
         */
        void draw(sf::RenderWindow& window, std::string& playerName1, std::string& playerName2);

    private:
        Morpion morpion{ endGamePopup, scoreManager }; /** @brief The game instance. */
        Chat chat; /** @brief The chat instance. */
        ScoreManager scoreManager; /** @brief The score manager instance. */
        EndGamePopup endGamePopup; /** @brief The endgame pop-up instance. */
        Server& server; /** @brief Reference to the server instance. */
        Client& client; /** @brief Reference to the client instance. */
        bool gameActive; /** @brief Indicates whether the game is currently active. */
    };
}