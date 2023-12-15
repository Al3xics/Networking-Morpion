#pragma once

namespace MorpionGame {
    /**
     * @brief The ScoreManager class manages and displays scores for players.
     */
    class ScoreManager {
    public:
        /**
         * @brief Constructor for the ScoreManager class.
         */
        ScoreManager();
        /**
         * @brief Destructor for the ScoreManager class.
         */
        ~ScoreManager();

        /**
         * @brief Increase the score for the specified player.
         * @param player1 : True for Player 1, false for Player 2.
         */
        void increaseScore(bool player1);
        /**
         * @brief Get the scores of both players.
         * @return A pair representing the scores of Player 1 and Player 2.
         */
        std::pair<int, int> getScores();
        /**
         * @brief Draw the ScoreManager on the SFML window.
         * @param window : SFML window for drawing.
         * @param playerName1 : The name of the fisrt player.
         * @param playerName2 : The name of the second player.
         */
        void draw(sf::RenderWindow& window, std::string& playerName1, std::string& playerName2);

    private:
        int scorePlayer1; /** @brief Score for Player 1. */
        int scorePlayer2; /** @brief Score for Player 2. */
        sf::Font font; /** @brief Font for text rendering. */
        sf::Text player1Text; /** @brief Text displaying Player 1's score. */
        sf::Text player2Text; /** @brief Text displaying Player 2's score. */
        sf::Text titleText; /** @brief Text displaying the title "Joueurs". */
        sf::Text tempText; /** @brief Temporary text (unused). */

        sf::RectangleShape borderPlayer1; /** @brief Border for Player 1's score. */
        sf::RectangleShape borderPlayer2; /** @brief Border for Player 2's score. */
        sf::RectangleShape borderTitle; /** @brief Border for the title "Joueurs". */

        sf::Texture crossTexture; /** @brief Texture for the cross symbol. */
        sf::Texture circleTexture; /** @brief Texture for the circle symbol. */
        sf::Sprite crossSprite; /** @brief Sprite for the cross symbol. */
        sf::Sprite circleSprite; /** @brief Sprite for the circle symbol. */

    };
}