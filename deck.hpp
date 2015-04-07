#ifndef _DECK_DV_
#define _DECK_DV_

#include "card.hpp"
#include "hand.hpp"
#include <vector>
#include <queue>
#include <random>
#include <ctime>
#include <functional>
#include <algorithm>
#include <iostream>

class deck {
    public:
        std::vector<card> cards_;

        // Default constructor, builds a basic deck of cards
        deck() {
            for (int i = 0; i < 4; ++i) {
                for (int j = 2; j <= 14; ++j) {
                    cards_.emplace_back(j, i);
                }
            }
        }

        // Copy constructor
        deck(deck const& d) : cards_(d.cards_) { }

        // Copy assignment operator
        deck& operator =(deck const& d) {
            cards_ = d.cards_;
            return *this;
        }

        // Move constructor
        deck(deck&& d) : cards_(d.cards_) { }

        // Move assigment operator
        deck& operator =(deck&& d) {
            cards_ = d.cards_;
            return *this;
        }

        // Deck destructor
        ~deck() {
            cards_.clear();
        }

        // Returns the cards in a queue structure, to be used for dealing
        std::queue<card> make_queue() const {
            std::queue<card> q;
            for (card c : cards_)
                q.push(c);
            return q;
        }

        // deals a specified amount of cards to each player
        // pass the queue by reference, in order to make any changes permanent
        std::vector<hand> deal(std::queue<card>& q, int amt, int players) {
            std::vector<hand> hands;

            // Fill up the vector with default-constructed hand objects
            for (int i = 0; i < players; ++i)
                hands.emplace_back();

            for (int i = 0; i < amt; ++i) {
                for (int j = 0; j < players; ++j) {
                    hands[i].add_card(q.front());
                    q.pop();
                }
            }

            return hands;
        }

        void shuffle() {
            std::uniform_int_distribution<int> dist(0, 51);
            std::knuth_b gen;
            gen.seed(time(NULL));
            auto roll = std::bind(dist, gen);

            for (int i = 0; i < 52; ++i)
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
