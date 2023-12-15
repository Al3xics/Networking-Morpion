#include "framework.hpp"
#include "Morpion.hpp"
#include "ScoreManager.hpp"

namespace MorpionGame {
    Morpion::Morpion(EndGamePopup& endGamePopup, ScoreManager& scoreManager) : currentPlayer(Player::Player1), movesCount(0), endGamePopup(endGamePopup), scoreManager(scoreManager) {

        // Initializing the game
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                grid[i][j].setSize(sf::Vector2f(30, 30));
                grid[i][j].setOutlineThickness(2);
                grid[i][j].setOutlineColor(sf::Color::Black);
                grid[i][j].setPosition(static_cast<float>(i) * 30 + 20, static_cast<float>(j) * 30 + 75);
            }
        }

        // Loading fonts and images
        if (!font.loadFromFile("res/arial.ttf")) {
            // Handle error if font cannot be loaded
            std::cerr << "Erreur : Impossible de charger la police Arial." << std::endl;
        }

        if (!crossTexture.loadFromFile("res/cross.png") || !circleTexture.loadFromFile("res/circle.png")) {
            std::cerr << "Erreur : Impossible de charger les textures." << std::endl;
        }

        if (!crossSoundBuffer.loadFromFile("res/cross.mp3") || !circleSoundBuffer.loadFromFile("res/circle.mp3")) {
            std::cerr << "Erreur : Impossible de charger les fichiers audio." << std::endl;
        }

        if (!winSoundBuffer.loadFromFile("res/win.mp3")) {
            std::cerr << "Erreur : Impossible de charger le fichier audio de victoire." << std::endl;
        }

        // Loading textures for the music button
        if (!musicOnTexture.loadFromFile("res/music_on.png") || !musicOffTexture.loadFromFile("res/music_off.png")) {
            std::cerr << "Erreur : Impossible de charger les textures du bouton musical." << std::endl;
        }

        // Loading music
        if (!backgroundMusic.openFromFile("res/background_music.mp3")) {
            std::cerr << "Erreur : Impossible de charger la musique de fond." << std::endl;
        }

        // Initializing the music button
        musicButton.setRadius(13);
        musicButton.setPosition(632, 187);
        musicButton.setTexture(&musicOnTexture);

        winSound.setBuffer(winSoundBuffer);
        crossSound.setBuffer(crossSoundBuffer);
        circleSound.setBuffer(circleSoundBuffer);

        // Starting music (it will play in a loop)
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(15);
        backgroundMusic.play();

        // Initialization of the player's turn
        playerTurnText.setFont(font);
        playerTurnText.setCharacterSize(20);
        playerTurnText.setPosition(330, 20);
        playerTurnText.setString("Tour du Joueur 1");
    }

    Morpion::~Morpion() {
        backgroundMusic.stop();
    }

    void Morpion::handleInput(sf::Event& event, sf::RenderWindow& window, std::string& playerName1, std::string& playerName2) {
        // Managing the click on the musical button
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldCoords = window.mapPixelToCoords(mousePosition);

            if (musicButton.getGlobalBounds().contains(worldCoords)) {
                // Switch between textures and turn music on/off
                if (musicButton.getTexture() == &musicOnTexture) {
                    musicButton.setTexture(&musicOffTexture);
                    backgroundMusic.pause();
                } else {
                    musicButton.setTexture(&musicOnTexture);
                    backgroundMusic.play();
                }

                return;  // Exit the function if the click was on the music button
            }
        }

        // Added the !isGameOver() condition to allow clicking only if the game is not over
        if (!isGameOver() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldCoords = window.mapPixelToCoords(mousePosition);

            std::cout << "Mouse clicked at (" << worldCoords.x << ", " << worldCoords.y << ")" << std::endl;


            if (!isGameOver()) {
                for (int i = 0; i < gridSize; ++i) {
                    for (int j = 0; j < gridSize; ++j) {
                        if (grid[i][j].getGlobalBounds().contains(worldCoords)) {
                            std::cout << "Clicked on grid cell (" << i << ", " << j << ")" << std::endl;

                            // Check if the box is empty
                            if (grid[i][j].getTexture() == nullptr) {
                                std::cout << "Grid cell is empty, assigning texture" << std::endl;

                                // Fill in the box with the current player's shape
                                if (currentPlayer == Player::Player1) {
                                    grid[i][j].setTexture(&crossTexture);
                                    crossSound.setVolume(30);
                                    crossSound.play();
                                } else {
                                    grid[i][j].setTexture(&circleTexture);
                                    circleSound.setVolume(30);
                                    circleSound.play();
                                }

                                // Increment movement counter
                                movesCount++;

                                // Check if there is a winner or if it is a draw
                                checkForWin(playerName1, playerName2);

                                // Move on to the next player
                                switchPlayer(playerName1, playerName2);
                            } else {
                                std::cout << "Grid cell is not empty, skipping" << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }

    void Morpion::draw(sf::RenderWindow& window) {
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                window.draw(grid[i][j]);
            }
        }

        window.draw(playerTurnText);
        window.draw(musicButton);
    }

    bool Morpion::isGameOver() const {
        // The game is over if someone has won or if there is a draw
        return (movesCount == gridSize * gridSize) /*|| (currentPlayer != Player::None)*/;
    }

    void Morpion::checkForWin(std::string& playerName1, std::string& playerName2) {
        // Check if there is a winner
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if (grid[i][j].getTexture() != nullptr) {
                    const sf::Texture* texture = grid[i][j].getTexture();
                    if (checkAlignment(i, j, texture)) {
                        // A player has won, display the end of game window
                        std::cout << "Player won!" << std::endl;

                        // Adding score (Check that scoreManager is correctly declared and accessible)
                        bool player1Won = (texture == &crossTexture);
                        std::cout << "Player " << (player1Won ? 1 : 2) << " won!" << std::endl;
                        scoreManager.increaseScore(player1Won);
                        // Increase the winning player's score
                        std::pair<int, int> scores = scoreManager.getScores();
                        std::cout << "Scores: Player 1 - " << scores.first << ", Player 2 - " << scores.second << std::endl;

                        // Play the sound of victory
                        winSound.setVolume(15);
                        winSound.play();

                        // Show end of game window
                        endGamePopup.show(texture == &crossTexture, playerName1, playerName2);  // If the texture is that of the cross, player 1 wins
                        return;
                    }
                }
            }
        }

        // If no wins and the number of moves reaches the size of the board, it is a draw
        if (movesCount == gridSize * gridSize) {
            std::cout << "It's a draw!" << std::endl;
        }
    }

    bool Morpion::checkAlignment(int startX, int startY, const sf::Texture* texture) {
        // Checks alignment in all directions
        int count = 0;

        // Check horizontal alignment
        for (int i = 0; i < 5; ++i) {
            if (startX + i >= 0 && startX + i < gridSize && grid[startX + i][startY].getTexture() == texture) {
                count++;
            } else {
                break;
            }
        }

        if (count >= 5) {
            std::cout << "Horizontal alignment detected!" << std::endl;
            return true;
        }

        count = 0;  // Resets the counter

        // Check vertical alignment
        for (int i = 0; i < 5; ++i) {
            if (startY + i >= 0 && startY + i < gridSize && grid[startX][startY + i].getTexture() == texture) {
                count++;
            } else {
                break;
            }
        }

        if (count >= 5) {
            std::cout << "Vertical alignment detected!" << std::endl;
            return true;
        }

        count = 0;  // Resets the counter

        // Checks diagonal (downward) alignment
        for (int i = 0; i < 5; ++i) {
            if (startX + i >= 0 && startX + i < gridSize && startY + i >= 0 && startY + i < gridSize &&
                grid[startX + i][startY + i].getTexture() == texture) {
                count++;
            } else {
                break;
            }
        }

        if (count >= 5) {
            std::cout << "Diagonal (descending) alignment detected!" << std::endl;
            return true;
        }

        count = 0;  // Resets the counter

        // Checks diagonal (rising) alignment
        for (int i = 0; i < 5; ++i) {
            if (startX - i >= 0 && startX - i < gridSize && startY + i >= 0 && startY + i < gridSize &&
                grid[startX - i][startY + i].getTexture() == texture) {
                count++;
            } else {
                break;
            }
        }

        if (count >= 5) {
            std::cout << "Diagonal (ascending) alignment detected!" << std::endl;
            return true;
        }

        return false;
    }


    void Morpion::switchPlayer(std::string& playerName1, std::string& playerName2) {
        // Move on to the next player
        if (currentPlayer == Player::Player1) {
            playerTurnText.setString("Tour de " + playerName2);
            currentPlayer = Player::Player2;
        } else if (currentPlayer == Player::Player2) {
            playerTurnText.setString("Tour de " + playerName1);
            currentPlayer = Player::Player1;
        }
    }

    void Morpion::resetGame(std::string& playerName1, std::string& playerName2) {
        // Reset for a new game
        currentPlayer = Player::Player1;
        movesCount = 0;

        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                // Remove cell textures
                grid[i][j].setTexture(nullptr);

            }
        }

        playerTurnText.setString("Tour de " + playerName1);
    }
}