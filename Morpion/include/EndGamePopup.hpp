#pragma once

namespace MorpionGame {
    /**
     * @brief The EndGamePopup class represents a pop-up displayed at the end of the game.
     */
    class EndGamePopup {
    public:
        /**
         * @brief Constructor for the EndGamePopup class.
         */
        EndGamePopup();
        /**
         * @brief Reset the pop-up window.
        */
        void resetPopup();

        /**
         * @brief Show the end-of-game pop-up with the result.
         * @param player1Wins : True if Player 1 wins, false if Player 2 wins.
         * @param playerName1 : Name of the first player.
         * @param playerName2 : Name of the second player.
         */
        void show(bool player1Wins, std::string& playerName1, std::string& playerName2);
        /**
         * @brief Handle user input for the end-of-game pop-up.
         * @param event : The SFML event to handle.
         * @param window : The SFML window to draw on.
         */
        void handleInput(sf::Event& event, sf::RenderWindow& window);
        /**
         * @brief Draw the end-of-game pop-up on the window.
         * @param window : The SFML window to draw on.
         */
        void draw(sf::RenderWindow& window);
        /**
         * @brief Check if a restart of the game is requested.
         * @return True if restart is requested, false otherwise.
         */
        bool isRestartRequested() const;

    private:
        bool visible; /** @brief Indicates whether the end-of-game pop-up is visible. */
        bool restartRequested; /** @brief Indicates whether a restart of the game is requested. */
        sf::RectangleShape restartButton; /** @brief The restart button. */
        sf::Font font; /** @brief The font used for text in the pop-up. */
        sf::Text messageText;/** @brief The text displaying the game result in the pop-up. */
        sf::Text restartText; /** @brief The text instructing how to restart the game in the pop-up. */
    };
}