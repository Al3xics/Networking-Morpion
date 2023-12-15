#include "framework.hpp"
#include "Chat.hpp"
#include <sstream>

namespace MorpionGame {
    Chat::Chat() {

        if (!keyPressBuffer.loadFromFile("res/keypress.mp3")) {
            std::cerr << "Error: Unable to load key press sound file." << std::endl;
        }

        keyPressSound.setBuffer(keyPressBuffer);

        font.loadFromFile("res/arial.ttf");
        titleText.setFont(font);
        titleText.setCharacterSize(17);
        titleText.setFillColor(sf::Color::Yellow);
        titleText.setPosition(575, 235);
        titleText.setString("Dialogue");

        inputText.setFont(font);
        inputText.setCharacterSize(17);
        inputText.setFillColor(sf::Color::White);
        inputText.setPosition(445, 480);

        chatText.setFont(font);
        chatText.setCharacterSize(17);
        chatText.setFillColor(sf::Color::White);
        chatText.setPosition(450, 270);

        sendButton.setSize(sf::Vector2f(80, 30));
        sendButton.setFillColor(sf::Color::Black);
        sendButton.setPosition(685, 475);

        sendButtonText.setFont(font);
        sendButtonText.setCharacterSize(17);
        sendButtonText.setFillColor(sf::Color(59, 59, 60));
        sendButtonText.setString("Envoyer");

        sf::FloatRect textBounds = sendButtonText.getLocalBounds();
        sendButtonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        sendButtonText.setPosition(sendButton.getPosition() + sf::Vector2f(sendButton.getSize()) / 2.0f);

        cursor.setSize(sf::Vector2f(2, 20));
        cursor.setFillColor(sf::Color::White);
        cursor.setPosition(465, 470);
    }

    void Chat::handleInput(sf::Event& event, sf::RenderWindow& window, const std::string& param, Server& server, Client& client, std::string& playerName1, std::string& playerName2) {
        if (event.type == sf::Event::TextEntered && window.hasFocus()) {
            if (event.text.unicode < 128 || event.text.unicode > 255) {
                if (event.text.unicode == 13) {
                    if (param == "server") {
                        addMessage(playerName1 + ": " + inputBuffer, param, server, client);
                    } else if (param == "client") {
                        addMessage(playerName2 + ": " + inputBuffer, param, server, client);
                    }
                    inputBuffer.clear();
                } else if (event.text.unicode == 8) {
                    if (!inputBuffer.empty()) {
                        inputBuffer.pop_back();
                        keyPressSound.setVolume(20);
                        keyPressSound.play();
                    }
                } else {
                    if (inputBuffer.size() < maxInputLength) {
                        inputBuffer += static_cast<char>(event.text.unicode);
                        keyPressSound.setVolume(20);
                        keyPressSound.play();
                    }
                }
            }
        }

        cursor.setPosition(inputText.getPosition().x + inputText.getLocalBounds().width + 7, 480);

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                if (sendButton.getGlobalBounds().contains(mousePos)) {
                    if (param == "server") {
                        addMessage(playerName1 + ": " + inputBuffer, param, server, client);
                    } else if (param == "client") {
                        addMessage(playerName2 + ": " + inputBuffer, param, server, client);
                    }
                    inputBuffer.clear();
                }
            }
        }

        if (param == "server") {
            inputText.setString(playerName1 + ": " + inputBuffer);
        } else if (param == "client") {
            inputText.setString(playerName2 + ": " + inputBuffer);
        }

        tryReceiveData(param, server, client);
    }

    void Chat::update(const std::string& param, Server& server, Client& client) {
        static sf::Clock cursorBlinkTimer;
        if (cursorBlinkTimer.getElapsedTime().asSeconds() > 0.5) {
            cursorBlinkTimer.restart();
            cursor.setFillColor((cursor.getFillColor() == sf::Color::White) ? sf::Color::Transparent : sf::Color::White);
        }

        tryReceiveData(param, server, client);
    }

    void Chat::draw(sf::RenderWindow& window) {
        sf::RectangleShape border;
        sf::RectangleShape bordertext;
        sf::RectangleShape bordertitle;

        sf::FloatRect extendedBounds = sendButton.getGlobalBounds();
        extendedBounds.width += 50.0f;
        extendedBounds.height += 50.0f;

        bordertitle.setSize(sf::Vector2f(330, 30));
        bordertitle.setFillColor(sf::Color::Black);
        bordertitle.setOutlineColor(sf::Color(0, 0, 0));
        bordertitle.setOutlineThickness(2.0f);
        bordertitle.setPosition(440, 231);

        border.setSize(sf::Vector2f(330, 280));
        border.setFillColor(sf::Color(74, 122, 111));
        border.setOutlineColor(sf::Color(0, 0, 0));
        border.setOutlineThickness(2.0f);
        border.setPosition(440, 230);

        bordertext.setSize(sf::Vector2f(330, 40));
        bordertext.setFillColor(sf::Color(80, 107, 82));
        bordertext.setOutlineColor(sf::Color(0, 0, 0));
        bordertext.setOutlineThickness(2.0f);
        bordertext.setPosition(440, 470);

        window.draw(border);
        window.draw(bordertext);
        window.draw(bordertitle);

        window.draw(chatText);
        window.draw(titleText);
        window.draw(inputText);
        window.draw(sendButton);
        window.draw(sendButtonText);
        window.draw(cursor);
    }

    void Chat::addMessage(const std::string& message, const std::string& param, Server& server, Client& client) {
        std::string newText = chatText.getString();
        messages.clear();

        std::istringstream messageStream(newText);
        std::string individualMessage;
        while (std::getline(messageStream, individualMessage, '\n')) {
            messages.push_back(individualMessage);
        }

        messages.push_back(message);

        if (messages.size() > maxMessages) {
            messages.pop_front();
        }

        updateChatText(param, server, client);
    }

    void Chat::updateChatText(const std::string& param, Server& server, Client& client) {
        std::string chatString;
        for (const auto& message : messages) {
            chatString += message + "\n";
        }
        chatText.setString(chatString);

        if (param == "server") {
            server.sendDataToClient(chatString);
        } else if (param == "client") {
            client.sendDataToServer(chatString);
        }
    }

    void Chat::tryReceiveData(const std::string& param, Server& server, Client& client) {
        std::string chatString;

        if (param == "server") {
            chatString = server.tryReceiveDataFromClient();
        } else if (param == "client") {
            chatString = client.tryReceiveDataFromServer();
        }

        if (!chatString.empty()) {
            chatText.setString(chatString);
        }
    }
}