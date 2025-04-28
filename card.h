#ifndef CARD_H
#define CARD_H

#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

enum Suit 
{
    heart,
    diamond,
    spade, 
    club,
    max_suits
};

class Card 
{
public:
    // Need this for initializing a deck, but should never be used in other contexts
    Card() = default;
    // Proper Card constructor
    // Requires a suit from the enum Suit defined above, as well as a value for the 
    // card between 1 and 13 inclusive. 1 = ace, 11 = jack, 12 = queen, 13 = king.
    Card(Suit suit, int value)
        : m_suit { suit }
        , m_value { value }
    {
        assert(1 <= value && 13 >= value);
    }

    // Getter member functions for Card class objects
    Suit getSuit() const { return m_suit; }
    int getValue() const { return m_value; }

    // String representation member functions
    // No break statements necessary because each preceding case returns and thus
    // there is no worry about fallthrough.
    std::string getSuitString() const 
    {
        switch (m_suit) 
        {
        case heart:     return "Hearts";
        case diamond:   return "Diamonds";
        case spade:     return "Spades";
        case club:      return "Clubs";
        default:        return "Unknown Suit";
        }
    }

    std::string getValueString() const 
    {
        switch (m_value)
        {
        case 1:     return "Ace";
        case 11:    return "Jack"; 
        case 12:    return "Queen";
        case 13:    return "King";
        default:    return std::to_string(m_value);
        }
    }

    // Define boolean methods for various comparisons of cards
    bool isSameSuit(const Card& other) const { return m_suit == other.m_suit; }
    bool isGreaterValue(const Card& other) const { return m_value > other.m_value; }
    bool isEqualValue(const Card& other) const { return m_value == other.m_value; }

    // Overload <<, ==, and != operators
    friend std::ostream& operator<<(std::ostream& out, const Card& card);
    friend bool operator==(const Card& card1, const Card& card2);
    friend bool operator!=(const Card& card1, const Card& card2);

private:
    // The card's suit from the enum Suit
    Suit m_suit {};
    // The card's value
    int m_value{};
};

// Definition for overloaded operator<<
std::ostream& operator<<(std::ostream& out, const Card& card)
{
    return out << card.getValueString() << " of " << card.getSuitString();
}

// Definition for overloaded operator== testing for equality of both suit and value
bool operator==(const Card& card1, const Card& card2)
{
    return (card1.m_suit == card2.m_suit && card1.m_value == card2.m_value);
}

// Now, use the overloaded operator== to quickly define operator!=
bool operator!= (const Card& card1, const Card& card2)
{
    return !(card1==card2);
}

#endif