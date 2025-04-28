// TODO: Update the game logic to allow the player to bet on a round
// TODO: Update the game logic to run until the player goes broke or quits

#include "blackjack.h"
#include "card.h"
#include "deck.h"
#include "iostream"

int main()
{
    char choice { 'y' };
    while (choice == 'y')
    {
        // Initialize the game
        Blackjack game;

        // Play the game and print whether the player wins or loses
        std::string message { game.playGame() ? "You won, congrats!" : "You lost, sorry!" };

        // Display the message
        std::cout << message << '\n';

        // Ask if the player would like to play again
        std::cout << "Play another hand? [y/n] ";
        std::cin >> choice;

        if (!std::cin)
            {
                std::cin.clear();
                std::cout << "That wasn't a valid selection, please pick again.\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

        // Remove anything beyond the first input character, up to the return key
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}