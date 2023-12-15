#include "framework.hpp"

namespace MorpionGame {
    ScoreManager::ScoreManager() : scorePlayer1(0), scorePlayer2(0) {
        // Initializing the Score Manager
        if (!font.loadFromFile("res/arial.ttf")) {
            // Handle error if font cannot be loaded
            std::cerr << "Erreur : Impossible de charger la police Arial." << std::endl;
        }

        if (!crossTexture.loadFromFile("res/crossscore.png") || !circleTexture.loadFromFile("res/circlescore.png")) {
            std::cerr << "Erreur : Impossible de charger les textures." << std::endl;
        }

        titleText.setFont(font);
        titleText.setCharacterSize(17);
        titleText.setFillColor(sf::Color::Yellow);
        titleText.setPosition(575, 75);
        titleText.setString("Joueurs");

        borderTitle.setSize(sf::Vector2f(330, 30));
        borderTitle.setFillColor(sf::Color::Black);
        borderTitle.setPosition(440, 75);
        borderTitle.setOutlineColor(sf::Color(0, 0, 0));
        borderTitle.setOutlineThickness(2.0f);

        crossSprite.setTexture(crossTexture);
        crossSprite.setPosition(450, 110);
        crossSprite.setScale(0.02f, 0.02f);

        borderPlayer1.setSize(sf::Vector2f(330, 40));
        borderPlayer1.setFillColor(sf::Color(74, 122, 111));
        borderPlayer1.setOutlineColor(sf::Color(0, 0, 0));
        borderPlayer1.setOutlineThickness(2.0f);
        borderPlayer1.setPosition(440, 100);

        circleSprite.setTexture(circleTexture);
        circleSprite.setPosition(444, 146);
        circleSprite.setScale(0.03f, 0.03f);

        borderPlayer2.setSize(sf::Vector2f(330, 40));
        borderPlayer2.setFillColor(sf::Color(80, 107, 82));
        borderPlayer2.setOutlineColor(sf::Color(0, 0, 0));
        borderPlayer2.setOutlineThickness(2.0f);
        borderPlayer2.setPosition(440, 140);

        player1Text.setFont(font);
        player1Text.setCharacterSize(17);
        player1Text.setFillColor(sf::Color::White);
        player1Text.setPosition(485, 110);

        player2Text.setFont(font);
        player2Text.setCharacterSize(17);
        player2Text.setFillColor(sf::Color::White);
        player2Text.setPosition(485, 150);
    }

    ScoreManager::~ScoreManager() {
        crossTexture.loadFromFile("res/crossscore.png");
        circleTexture.loadFromFile("res/circlescore.png");
    }

    void ScoreManager::increaseScore(bool player1) {
        if (player1) {
            scorePlayer1++;
            std::cout << "Player 1 score increased: " << scorePlayer1 << std::endl;
        } else {
            scorePlayer2++;
            std::cout << "Player 2 score increased: " << scorePlayer1 << std::endl;
        }
    }


    std::pair<int, int> ScoreManager::getScores() {
        return std::make_pair(scorePlayer1, scorePlayer2);
    }

    void ScoreManager::draw(sf::RenderWindow& window, std::string& playerName1, std::string& playerName2) {
        // Draw player scores
        player1Text.setString(playerName1 + " : " + std::to_string(scorePlayer1));
        player2Text.setString(playerName2 + " : " + std::to_string(scorePlayer2));

        window.draw(borderTitle);
        window.draw(borderPlayer1);
        window.draw(borderPlayer2);

        window.draw(titleText);
        window.draw(player1Text);
        window.draw(player2Text);

        window.draw(crossSprite);
        window.draw(circleSprite);

    }
}