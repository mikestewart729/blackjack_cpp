#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "card.h"
#include "deck.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector> // Note that while a deck is fixed size, a hand may change size

class BlackjackPlayer
{
public:
    // Constructor for creating a player with an empty hand and score of zero
    BlackjackPlayer() { };

    // Add a card to the player hand
    void addToHand(const Card& card) { m_hand.push_back(card); }

    // Print the player hand
    void printHand() const
    {
        for (const Card& card : m_hand)
        {
            std::cout << card << '\n';
        }
    }

    // setter and getter member functions. No setter for m_hand, use addToHand instead
    const std::vector<Card>& getHand() const { return m_hand; }
    int getScore() const { return m_score; }
    void setScore(int score) { m_score = score; }

private:
    // Use a vector since hands by nature change size
    std::vector<Card> m_hand;
    int m_score { 0 };
};

class Blackjack
{
public:
    Blackjack()
    {
        // Deal two cards to the player and the dealer from m_deck in alternating order
        for (int i { 0 }; i < 2; ++i)
        {
            m_player.addToHand(m_deck.deal());
            m_dealer.addToHand(m_deck.deal());
        }
        updateScore(m_player);
        updateScore(m_dealer);
    }

    // Auxiliary function to determine if a hand contains an Ace
    bool handHasAce(BlackjackPlayer& player)
    {
        for (const Card& card : player.getHand())
        {
            if (card.getValue() == 1)
            {
                return true;
            }
        }
        return false;
    }

    // Check if the player has gone bust (i.e. score over 21)
    bool isBust(const BlackjackPlayer& player) const { return player.getScore() > 21; }

    // Calculate the score of a BlackjackPlayer hand and update the player
    void updateScore(BlackjackPlayer& player)
    {
        int temp_score { 0 };
        for (const Card& card : player.getHand()) 
        {
            // Handle the score for face cards, having value 10
            if (card.getValue() >= 11)
            {
                temp_score += 10;
            }
            // Aces are worth 11 points
            else if (card.getValue() == 1)
            {
                temp_score += 11;
                // However, an ace can also score 1 if scoring 11 causes a bust
                if (temp_score > 21)
                {
                    temp_score -= 10;
                }
            }
            else
            {
                // add the value to the score
                temp_score += card.getValue();
            }
        }
        player.setScore(temp_score);
    }

    // Function to hit the player and the dealer
    void hit(BlackjackPlayer& player) { player.addToHand(m_deck.deal()); }
    // Think about refactoring these two functions and the above. 
    void hitPlayer()
    {
        hit(m_player);
        updateScore(m_player);
    }
    void hitDealer()
    {
        hit(m_dealer);
        updateScore(m_dealer);
    }

    // Get the player and dealer scores
    int getPlayerScore() const { return m_player.getScore(); }
    int getDealerScore() const { return m_dealer.getScore(); }

    // Display method for player hand
    // Player can always see all of their cards
    void displayPlayerHand() 
    {
        std::cout << "Your hand is:\n";
        for (const Card& card : m_player.getHand())
        {
            std::cout << card << '\n';
        }
        std::cout << "Your score is: " << m_player.getScore() << "\n\n";
    }

    // Display the dealer's hand. The player can only see the dealer's first card
    // until after the player either goes bust or chooses to stand
    void displayDealerHand(bool player_stands)
    {
        std::cout << "The Dealer's hand is:\n";
        if (!player_stands)
        {
            // The dealer plays after the player, so there are only two cards in the
            // dealer's hand at this point
            std::cout << m_dealer.getHand()[static_cast<std::size_t>(0)] << '\n';
            std::cout << "Facedown card\n\n";
        }
        else
        {
            for (const Card& card : m_dealer.getHand())
            {
                std::cout << card << '\n';
            }
            std::cout << "The Dealer's score is: " << m_dealer.getScore() << "\n\n";
        }
    }

    // Get input from the player to either hit or stand
    char getPlayerInput()
    {
        while (true)
        {
            std::cout << "Would you like to (h)it or (s)tand? ";
            char choice {};
            std::cin >> choice;

            // Handle erroneous inputs
            if (!std::cin)
            {
                std::cin.clear();
                std::cout << "That wasn't a valid selection, please pick again.\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            // Remove anything beyond the first input character, up to the return key
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!(choice == 'h' || choice == 's'))
            {
                std::cout << "That wasn't a valid selection. Please choose again.\n";
                continue;
            }

            // If we've made it this far, we've entered 'h' or 's'.
            return choice;
        }
    }

    // Main game loop for one hand of blackjack
    // Figure out how to refactor this so it doesn't need to be a boolean return
    bool playGame()
    {
        // First, display the player and dealer hands appropriately and ask
        // if the player would like to hit or stand
        // The player plays until they go bust or else stand
        while (!isBust(m_player) && !player_stands)
        {
            displayPlayerHand();
            displayDealerHand(player_stands);
            char choice { getPlayerInput() };
            if (choice == 'h')
            {
                hitPlayer();
            }
            else if (choice == 's')
            {
                player_stands = true;
            }
            else
            {
                // Should never reach this block
                std::cout << "Invalid input selected.\n";
            }
        }
        displayPlayerHand();
        if (isBust(m_player))
        {
            std::cout << "You went bust! You lose this round.\n";
            return false;
        }
        // Now run the dealer's turn. The dealer must stand on 17.
        while (m_dealer.getScore() < 17)
        {
            hitDealer();
        }
        displayDealerHand(player_stands);

        // Now check the win/loss conditions
        if (isBust(m_dealer))
        {
            std::cout << "The Dealer went bust! You win this round!\n";
            return true;
        }

        // In the case of a tie, the dealer wins
        if (getPlayerScore() > getDealerScore())
        {
            return true;
        }
        // Return false, because the dealer has the same or greater score
        return false;
    }

private:
    Deck m_deck;
    BlackjackPlayer m_player;
    BlackjackPlayer m_dealer;
    bool player_stands { false };
};

#endif