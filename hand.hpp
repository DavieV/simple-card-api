#ifndef _DV_HAND_
#define _DV_HAND_

#include "card.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

class hand {
    private:
        std::vector<card> cards_;

    public:
        hand() : cards_() { }

        hand(hand const& h) : cards_(h.cards_) { }

        hand& operator =(hand const& h) {
            cards_ = h.cards_;
            return *this;
        }

        hand(hand&& h) : cards_(std::move(h.cards_)) { }

        hand& operator =(hand&& h) {
            cards_ = std::move(h.cards_);
            return *this;
        }

        ~hand() {
            cards_.clear();
        }

        std::vector<card> cards() { return cards_; }

        void add_card(card c) {
            cards_.emplace_back(c);
        }

        void swap_cards(card c, int i) {
            cards_[i] = c;
        }

        void remove_card(int i) {
            cards_.erase(cards_.begin() + i);
        }

        void sort_cards() {
            std::sort(cards_.begin(), cards_.end());
        }

        void print_hand() const {
            for (card c : cards_)
                std::cout << c << " ";
            std::cout << std::endl;
        }
};

#endif
