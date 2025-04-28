#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <string_view>

class DeckException
{
public:
    DeckException(std::string_view error)
        : m_error { error }
    {  
    }

    const std::string& getError() const { return m_error; }

private:
    std::string m_error;
};

class Deck
{
public:
    // Constructor for decks
    Deck()
    {
        for (int i { 0 }; i < m_num_suits; ++i)
        {
            for (int j { 0 }; j < m_vals_per_suit; ++j)
            {
                m_deck[static_cast<std::size_t>(i * 13 + j)]
                    // Recall that card values are defined to start at 1, not 0
                    // hence the +1 in the Card constructor below;
                    = Card { m_suits[i % 4], (j % m_vals_per_suit) + 1};
            }
        }
        // Ensure that a newly initialized deck is shuffled
        shuffle();
    }

    // Shuffle the deck. 
    void shuffle()
    {
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(m_deck.begin(), m_deck.end(), g);
    }

    // Print out the deck, for debugging
    void printDeck() const
    {
        for (const Card& card : m_deck)
        {
            std::cout << card << '\n';
        }
    }

    // Deal a card from the deck
    Card& deal()
    {
        if (m_deal_idx >= (m_num_suits * m_vals_per_suit))
        {
            throw DeckException("Tried to deal more cards than are in the deck!");
        }

        return m_deck[static_cast<std::size_t>(m_deal_idx++)];
    }

private:
    // Hold the 52 cards of a standard deck
    std::array<Card, 52> m_deck;
    // Keep track of which cards have been dealt
    int m_deal_idx { 0 };

    // Auxiliary/helper variables
    Suit m_suits[4] { Suit::heart, Suit::diamond, Suit::spade, Suit::club };
    const int m_num_suits { 4 };
    const int m_vals_per_suit { 13 };
};

#endif