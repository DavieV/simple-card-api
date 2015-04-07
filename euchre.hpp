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

// Possible additions:
// scoring system
// basic game loop
// trump selection
// player queries regarding valid plays

class euchre {
    public:
        std::vector<card> cards_;

        euchre() {
            for (int i = 0; i < 4; ++i) {
                for (int j = 9; j <= 14; ++j) {
                    cards_.emplace_back(j, i);
                }
            }
        }

        euchre(euchre const& d) : cards_(d.cards_) { }

        euchre& operator =(euchre const& d) {
            cards_ = d.cards_;
            return *this;
        }

        euchre(euchre&& d) : cards_(d.cards_) { }

        euchre& operator =(euchre&& d) {
            cards_ = d.cards_;
            return *this;
        }

        ~euchre() {
            cards_.clear();
        }

        // Return the deck of cards in queue form, to be used for dealing
        std::queue<card> make_queue() const {
            std::queue<card> q;
            for (card c : cards_)
                q.push(c);
            return q;
        }

        std::vector<hand> deal(std::queue<card>& q) const {
            std::vector<hand> hands;

            // fill the vector with default-constructed hand objects
            for (int i = 0; i < 4; ++i)
                hands.emplace_back();

            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 4; ++j) {
                    hands[j].add_card(q.front());
                    q.pop();
                }
            }

            return hands;
        }

        card trick(int trump, card c1, card c2, card c3, card c4) const {
            std::vector<card> follow{c2, c3, c4};
            card cand = c1;  // c1 is default candidate

            // Iterate through the cards to determine a winner
            for (card c : follow) {
                if (suit(trump, c) == suit(trump, cand))
                    cand = max_c(trump, cand, c);
                else if (suit(trump, c) == trump && suit(trump, cand) != trump)
                    cand = c;
            }

            return cand;
        }

        // Returns a vector of cards which are currently valid to play
        std::vector<card> valid_plays(hand h, int trump, card lead) {
            std::vector<card> valid;
            bool l;

            for (card c : h.cards_) {
                if (suit(trump, c) == suit(trump, lead));
                    l = true;
            }

            for (card c : h.cards_) {
                if (l) {
                    if (suit(trump, c) == suit(trump, lead))
                        valid.push_back(c);
                } else {
                    valid.push_back(c);
                }
            }

            return valid;
        }

        // Return the min of two cards, includes whether they are trump
        card min_c(int trump, card c1, card c2) const {
            // If both cards are trump, return the lesser of the two
            if (c1.suit() == trump && c2.suit() == trump)
                return (c1 < c2) ? c1 : c2;
            // If one card is trump and one isn't, return the non-trump
            else if (c1.suit() != trump && c2.suit() == trump)
                return c1;
            else if (c2.suit() != trump && c1.suit() == trump)
                return c2;
            else
                return (c1 < c2) ? c1 : c2;
        }

        // Return the max of two cards, includes whether they are trump
        card max_c(int trump, card c1, card c2) const {
            if (suit(trump, c1) == suit(trump, c2)) {
                if (is_r_bower(trump, c1))
                    return c1;
                if (is_r_bower(trump, c2))
                    return c2;
                if (is_l_bower(trump, c1))
                    return c1;
                if (is_l_bower(trump, c2))
                    return c2;
                return (c1 > c2) ? c1 : c2;
            } else {
                if (c1.suit() == trump)
                    return c1;
                if (c2.suit() == trump)
                    return c2;
                return (c1 > c2) ? c1 : c2;
            }
        }

        // Determines if c is right bower based on trump
        bool is_r_bower(int trump, card c) const {
            return (c.suit() == trump && c.val() == 11);
        }

        // Determines if c is left bower based on trump
        bool is_l_bower(int trump, card c) const {
            if (trump == 0)
                return (c.suit() == 1 && c.val() == 11);
            if (trump == 1)
                return (c.suit() == 0 && c.val() == 11);
            if (trump == 2)
                return (c.suit() == 3 && c.val() == 11);
            return (c.suit() == 2 && c.val() == 11);
        }

        // Free suit() function which accounts for trump when checking suit
        int suit(int trump, card c) const {
            if (is_l_bower(trump, c))
                return trump;
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

        void sort_cards() {
            std::sort(cards_.begin(), cards_.end());
        }

        void print_cards() const {
            for (card c : cards_)
                std::cout << c.name() << " ";
            std::cout << std::endl;
        }
};

#endif
