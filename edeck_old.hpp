#ifndef _EDECK_DV_
#define _EDECK_DV_

#include "card.hpp"
#include "hand.hpp"
#include <vector>
#include <queue>
#include <random>
#include <ctime>
#include <functional>
#include <algorithm>
#include <iostream>

class edeck {
    public:
        std::vector<card> cards_;

        edeck() {
            for (int i = 0; i < 4; ++i) {
                for (int j = 9; j <= 14; ++j) {
                    cards_.emplace_back(j, i);
                }
            }
        }

        edeck(edeck const& d) : cards_(d.cards_) { }

        edeck& operator =(edeck const& d) {
            cards_ = d.cards_;
            return *this;
        }

        edeck(edeck&& d) : cards_(d.cards_) { }

        edeck& operator =(edeck&& d) {
            cards_ = d.cards_;
            return *this;
        }

        ~edeck() {
            cards_.clear();
        }

        std::queue<card> make_queue() const {
            std::queue<card> q;
            for (card c : cards_)
                q.push(c);
            return q;
        }

        std::vector<hand> deal(std::queue<card>& q) {
            std::vector<hand> hands;

            // fill the vector with default-constructed hand objects
            for (int i = 0; i < 4; ++i)
                hands.emplace_back();

            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 4; ++j) {
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
