#pragma once

#include "Client.hpp"
#include "Server.hpp"

namespace MorpionGame {
    /**
     * @brief The Chat class represents a simple chat feature for the game.
    */
    class Chat {
    public:
        /**
         * @brief Constructor for the Chat class.
        */
        Chat();

        int maxInputLength = 20; /** @brief Maximum lenght of the message. */

        /**
         * @brief Handles input events for the chat.
         * @param event : The SFML event to handle.
         * @param window : The SFML window for input focus.
         * @param param : The parameter indicating whether the chat is associated with a server or client.
         * @param server : Reference to the Server object.
         * @param client : Reference to the Client object.
         * @param playerName1 : Name of the first player.
         * @param playerName2 : Name of the second player.
        */
        void handleInput(sf::Event& event, sf::RenderWindow& window, const std::string& param, Server& server, Client& client, std::string& playerName1, std::string& playerName2);
        /**
         * @brief Updates the chat logic.
         * @param param : The parameter indicating whether the chat is associated with a server or client.
         * @param server : Reference to the Server object.
         * @param client : Reference to the Client object.
        */
        void update(const std::string& param, Server& server, Client& client);
        /**
         * @brief Draws the chat on the SFML window.
         * @param window : The SFML window for drawing.
        */
        void draw(sf::RenderWindow& window);

    private:
        /**
         * @brief Adds a message to the chat.
         * @param message : The message to add.
         * @param param : The parameter indicating whether the chat is associated with a server or client.
         * @param server : Reference to the Server object.
         * @param client : Reference to the Client object.
        */
        void addMessage(const std::string& message, const std::string& param, Server& server, Client& client);
        /**
         * @brief Updates the chat text with the messages.
         * @param param : The parameter indicating whether the chat is associated with a server or client.
         * @param server : Reference to the Server object.
         * @param client : Reference to the Client object.
        */
        void updateChatText(const std::string& param, Server& server, Client& client);
        /**
         * @brief Tries to receive data for the chat.
         * @param param : The parameter indicating whether the chat is associated with a server or client.
         * @param server : Reference to the Server object.
         * @param client : Reference to the Client object.
        */
        void tryReceiveData(const std::string& param, Server& server, Client& client);

        sf::RectangleShape sendButton; /** @brief Represents the rectangular button for sending messages in the chat. */
        sf::Text sendButtonText; /** @brief Represents the text displayed on the send button in the chat. */
        sf::Font font; /** @brief Represents the font used for text rendering in the chat. */
        sf::Text chatText; /** @brief Represents the text area displaying chat messages. */
        sf::Text inputText; /** @brief Represents the text input area for composing messages in the chat. */
        sf::Text titleText; /** @brief Represents the title text indicating the purpose of the chat area. */
        std::deque<std::string> messages; /** @brief Represents a deque of messages in the chat. */
        std::string inputBuffer; /** @brief Represents the buffer for storing the user's input in the chat. */
        sf::RectangleShape cursor; /** @brief Represents the cursor indicator in the chat text input area. */
        sf::SoundBuffer keyPressBuffer; /** @brief Represents the sound buffer for keypress sound in the chat. */
        sf::Sound keyPressSound; /** @brief Represents the sound for keypress in the chat. */


        const std::size_t maxMessages = 9; /** @brief Represents the maximum number of messages to display in the chat. */
    };
}