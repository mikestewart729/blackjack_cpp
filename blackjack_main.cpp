// TODO: Update the game logic to allow for more than one round to be played
// TODO: Update the game logic to allow the player to bet on a round
// TODO: Update the game logic to run until the player goes broke or quits

#include "blackjack.h"
#include "card.h"
#include "deck.h"
#include "iostream"

int main()
{
    // Initialize the game
    Blackjack game;

    // Play the game and print whether the player wins or loses
    std::string message { game.playGame() ? "You won, congrats!" : "You lost, sorry!" };

    // Display the message
    std::cout << message << '\n';

    return 0;
}