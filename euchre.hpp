#ifndef _EUCHRE_DV_
#define _EUCHRE_DV_

#include "card.hpp"
#include "hand.hpp"
#include <vector>
#include <queue>
#include <random>
#include <ctime>
#include <functional>
#include <algorithm>
#include <iostream>

class euchre {
    private:
        std::vector<card> cards_;
        suits trump_;
        int dealer_;

    public:
        // ------------------------------------------------------
        // -------------------- Constructors --------------------
        // ------------------------------------------------------

        // Default constructor fills in the vector of cards with a euchre deck
        euchre() {
            int i = 0;
            int j = 0;
            for (suits s = suits::spades; i < 4; ++s, ++i) {
                for (card_val v = card_val::nine; j < 6; ++v, ++j) {
                    cards_.emplace_back(v, s);
                }
                j = 0;
            }
            dealer_ = 0;
        }

        // Copy constructor
        euchre(euchre const& d) : cards_(d.cards_), dealer_(d.dealer_)  { }

        // Copy assignment operator
        euchre& operator =(euchre const& d) {
            cards_ = d.cards_;
            dealer_ = d.dealer_;
            return *this;
        }

        // Move constructor
        euchre(euchre&& d) : 
            cards_(std::move(d.cards_)),
            dealer_(std::move(d.dealer_))
        { }

        // Move assignment operator
        euchre& operator =(euchre&& d) {
            cards_ = std::move(d.cards_);
            dealer_ = std::move(d.dealer_);
            return *this;
        }

        ~euchre() {
            cards_.clear();
        }

        // ---------------------------------------------------------
        // ------------------ Get/Set Functions --------------------
        // ---------------------------------------------------------

        std::vector<card> cards() { return cards_; }
    
        suits trump() { return trump_; }

        int dealer() { return dealer_; }

        void set_trump(suits t) { trump_ = t; }

        void change_dealer() { dealer_ = (dealer_ + 1) % 4; }

        // ----------------------------------------------------------
        // ------------------ Utility Functions ---------------------
        // ----------------------------------------------------------
 
        // Return the deck of cards in queue form, to be used for dealing
        std::queue<card> make_queue() const {
            std::queue<card> q;
            for (card c : cards_)
                q.push(c);
            return q;
        }

        // Deals each player a hand using a queue. The remaining cards on the
        // queue are the kiddy (the queue is passed by reference)
        std::vector<hand> deal(std::queue<card>& q) const {
            std::vector<hand> hands(4);

            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 4; ++j) {
                    hands[j].add_card(q.front());
                    q.pop();
                }
            }

            return hands;
        }

        // Returns the winner of a trick based on the 4 cards in play
        // as well as the current trump suit
        card trick(card c1, card c2, card c3, card c4) const {
            std::vector<card> follow{c2, c3, c4};
            card cand = c1;  // c1 is default candidate

            // Iterate through the cards to determine a winner
            for (card c : follow) {
                if (suit(c) == suit(cand))
                    cand = max_c(cand, c);
                else if (suit(c) == trump_)
                    cand = c;
            }

            return cand;
        }

        // Returns a vector of valid cards in the hand which are valid
        // to play based on the current trump
        std::vector<card> valid_plays(hand h, card lead) {
            std::vector<card> valid;
            bool l;

            // Determine if the player has at least one card that is the same
            // suit as the lead
            for (card c : h.cards()) {
                if (suit(c) == suit(lead)) {
                    l = true;
                    break;
                }
            }

            // If l is true add only cards of the valid suit
            // otherwise all cards are valid
            for (card c : h.cards()) {
                if (l) {
                    if (suit(c) == suit(lead))
                        valid.push_back(c);
                } else {
                    valid.push_back(c);
                }
            }

            return valid;
        }

        // Return the min of two cards, includes whether they are trump
        card min_c(card c1, card c2) const {
            if (suit(c1) == suit(c2)) {
                if (is_r_bower(c1))
                    return c2;
                if (is_r_bower(c2))
                    return c1;
                if (is_l_bower(c1))
                    return c2;
                if (is_l_bower(c2))
                    return c1;
                return (c1 < c2) ? c1 : c2;
            } else {
                if (suit(c1) == trump_)
                    return c2;
                if (suit(c2) == trump_)
                    return c1;
                return (c1 < c2) ? c1 : c2;
            }
        }

        // Return the max of two cards, includes whether they are trump
        card max_c(card c1, card c2) const {
            if (suit(c1) == suit(c2)) {
                if (is_r_bower(c1))
                    return c1;
                if (is_r_bower(c2))
                    return c2;
                if (is_l_bower(c1))
                    return c1;
                if (is_l_bower(c2))
                    return c2;
                return (c1 > c2) ? c1 : c2;
            } else {
                if (suit(c1) == trump_)
                    return c1;
                if (suit(c2) == trump_)
                    return c2;
                return (c1 > c2) ? c1 : c2;
            }
        }

        // Determines if c is right bower based on trump
        bool is_r_bower(card c) const {
            return (c.suit() == trump_ && c.val() == card_val::jack);
        }

        // Determines if c is left bower based on trump
        bool is_l_bower(card c) const {
            if (trump_ == suits::spades)
                return (c.suit() == suits::clubs && c.val() == card_val::jack);
            if (trump_ == suits::clubs)
                return (c.suit() == suits::spades && c.val() == card_val::jack);
            if (trump_ == suits::diamonds)
                return (c.suit() == suits::hearts && c.val() == card_val::jack);
            return (c.suit() == suits::diamonds && c.val() == card_val::jack);
        }

        // Free suit() function which accounts for trump when checking suit
        suits suit(card c) const {
            if (is_l_bower(c))
                return trump_;
            return c.suit();
        }

        // Shuffle the deck by randomly swapping the card at every index
        void shuffle() {
            std::uniform_int_distribution<int> dist(0, 23);
            std::knuth_b gen;
            gen.seed(time(NULL));
            auto roll = std::bind(dist, gen);

            for (int i = 0; i < 24; ++i)
                std::swap(cards_[i], cards_[roll()]);
        }

        // Sorts the cards based on their basic values, ignores trump
        void sort_cards() {
            std::sort(cards_.begin(), cards_.end());
        }

        void print_cards() const {
            for (card c : cards_)
                std::cout << c << " ";
            std::cout << std::endl;
        }
};

#endif
