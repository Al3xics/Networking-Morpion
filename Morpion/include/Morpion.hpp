#pragma once

#include "EndGamePopup.hpp"
#include "ScoreManager.hpp"

namespace MorpionGame {
    /**
     * @brief The Morpion class represents the game logic.
     */
    class Morpion {
    public:
        /**
         * @brief Constructor for the Morpion class.
         * @param endGamePopup : Reference to the EndGamePopup instance.
         * @param scoreManager : Reference to the ScoreManager instance.
         */
        Morpion(EndGamePopup& endGamePopup, ScoreManager& scoreManager);

        /**
         * @brief Destructor for the Morpion class.
        */
        ~Morpion();

        /**
         * @brief Handle input events for the game.
         * @param event : SFML event to handle.
         * @param window : SFML window for input handling.
         * @param playerName1 : Name of the first player.
         * @param playerName2 : Name of the second player.
         */
        void handleInput(sf::Event& event, sf::RenderWindow& window, std::string& playerName1, std::string& playerName2);
        /**
         * @brief Draw the game on the SFML window.
         * @param window : SFML window for drawing.
         */
        void draw(sf::RenderWindow& window);

        /**
         * @brief Check if the game is over.
         * @return True if the game is over, false otherwise.
         */
        bool isGameOver() const;
        /**
         * @brief Check for alignment in the grid.
         * @param startX : Starting X coordinate.
         * @param startY : Starting Y coordinate.
         * @param texture : Pointer to the texture to check alignment.
         * @return True if alignment is found, false otherwise.
         */
        bool checkAlignment(int startX, int startY, const sf::Texture* texture);
        /**
         * @brief Reset the game for a new round.
         * @param playerName1 : Name of the first player.
         * @param playerName2 : Name of the second player.
         */
        void resetGame(std::string& playerName1, std::string& playerName2);
        /**
         * @brief Check for a win in the game.
         * @param playerName1 : Name of the first player.
         * @param playerName2 : Name of the second player.
         */
        void checkForWin(std::string& playerName1, std::string& playerName2);

        /**
         * @brief Get the ScoreManager associated with the game.
         * @return Reference to the ScoreManager instance.
         */
        ScoreManager& getScoreManager() {
            return scoreManager;
        }
        /**
         * @brief Get the EndGamePopup associated with the game.
         * @return Reference to the EndGamePopup instance.
         */
        EndGamePopup& getEndGamePopup() {
            return endGamePopup;
        }

    private:
        /**
         * @brief Enumeration representing players in the game.
         */
        enum class Player {
            None,
            Player1,
            Player2
        };

        /**
         * @brief Switch the current player in the game.
         * @param playerName1 : Name of the first player.
         * @param playerName2 : Name of the second player.
         */
        void switchPlayer(std::string& playerName1, std::string& playerName2);

        static const int gridSize = 13; /** @brief Size of the grid. */
        int movesCount; /** @brief Count of moves made in the game. */

        sf::RectangleShape grid[gridSize][gridSize]; /** @brief 2D array representing the grid. */
        sf::Text playerTurnText; /** @brief Text displaying the current player's turn. */
        sf::Font font; /** @brief Font for text rendering. */

        sf::Texture crossTexture; /** @brief Texture for the cross symbol. */
        sf::Texture circleTexture; /** @brief Texture for the circle symbol. */

        sf::SoundBuffer crossSoundBuffer; /** @brief Sound buffer for the cross sound. */
        sf::SoundBuffer circleSoundBuffer; /** @brief Sound buffer for the circle sound. */
        sf::SoundBuffer winSoundBuffer; /** @brief Sound buffer for the win sound. */
        sf::Sound crossSound; /** @brief Sound for the cross symbol. */
        sf::Sound circleSound; /** @brief Sound for the circle symbol. */
        sf::Sound winSound; /** @brief Sound for the win event. */

        sf::CircleShape musicButton; /** @brief Represents the button for toggling music. */
        sf::Texture musicOnTexture; /** @brief Texture for the music-on state. */
        sf::Texture musicOffTexture; /** @brief Texture for the music-off state. */

        sf::Music backgroundMusic; /** @brief Background music for the game. */

        Player currentPlayer; /** @brief Current player in the game. */

        EndGamePopup& endGamePopup; /** @brief Reference to the EndGamePopup instance. */
        ScoreManager& scoreManager; /** @brief Reference to the ScoreManager instance. */
    };
}