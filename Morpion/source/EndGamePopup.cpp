#include "framework.hpp"

namespace MorpionGame {
    EndGamePopup::EndGamePopup() : visible(false), restartRequested(false) {
        if (!font.loadFromFile("res/arial.ttf")) {
            // Handle error if font cannot be loaded
            std::cerr << "Erreur : Impossible de charger la police Arial." << std::endl;
        }

        restartButton.setSize(sf::Vector2f(100, 25));
        restartButton.setFillColor(sf::Color(0, 0, 0));
        restartButton.setOutlineColor(sf::Color(59, 59, 60));
        restartButton.setOutlineThickness(2.0f);
        restartButton.setPosition(670, 187);

        restartText.setFont(font);
        restartText.setCharacterSize(17);
        restartText.setFillColor(sf::Color(59, 59, 60));
        restartText.setPosition(683, 188);
        restartText.setString("Revanche");

        messageText.setFont(font);
        messageText.setCharacterSize(17);
        messageText.setFillColor(sf::Color::White);
        messageText.setPosition(130, 480);

    }

    void EndGamePopup::resetPopup() {
        visible = false;
        restartRequested = false;
    }

    void EndGamePopup::show(bool player1Wins, std::string& playerName1, std::string& playerName2) {
        visible = true;
        restartRequested = false;  // Reset the reboot request

        if (player1Wins) {
            messageText.setString(playerName1 + " a gagné !");
        } else {
            messageText.setString(playerName2 + " a gagné !");
        }

        restartText.setString("Revanche"); // Setting the text for the "Replay" button
    }

    void EndGamePopup::handleInput(sf::Event& event, sf::RenderWindow& window) {
        if (visible) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f worldCoords = window.mapPixelToCoords(mousePosition);

                sf::FloatRect extendedBounds = restartButton.getGlobalBounds();
                extendedBounds.width += 10.0f;
                extendedBounds.height += 10.0f;

                if (extendedBounds.contains(worldCoords)) {
                    std::cout << "Clic sur le bouton Rejouer détecté !" << std::endl;
                    resetPopup();  // Reset the popup
                    restartRequested = true;
                }
            }
        }
    }

    void EndGamePopup::draw(sf::RenderWindow& window) {
        if (visible) {
            // Draw the background and message of the pop-up
            window.draw(messageText);
        }

        // Draw the “Replay” button
        window.draw(restartButton);
        window.draw(restartText);
    }

    bool EndGamePopup::isRestartRequested() const {
        return restartRequested;
    }
}