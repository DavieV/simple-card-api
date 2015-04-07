#ifndef _CARD_DV_
#define _CARD_DV_

#include <string>
#include <algorithm>

// Spades = 0
// Clubs = 1
// Diamonds = 2
// Hearts = 3

class card {
    private:
        int val_;
        int suit_;

    public:
        card(int val, int suit) : val_(val), suit_(suit) { }

        card(card const& c) : val_(c.val_), suit_(c.suit_) { }

        card& operator =(card const& c) {
            val_ = c.val_;
            suit_ = c.suit_;
            return *this;
        }

        card(card&& c) : val_(std::move(c.suit_)), suit_(std::move(c.suit_)) { }

        card& operator =(card&& c) {
            val_ = std::move(c.val_);
            suit_ = std::move(c.suit_);
            return *this;
        }

        int val() const { return val_; }
        int suit() const { return suit_; }

        bool operator <(card const& c) const {
            return val_ < c.val();
        }

        bool operator >(card const& c) const {
            return val_ > c.val();
        }

        ~card() { }

        std::string name() const {
            std::string n = "";

            // Card Value
            if (val_ <= 9)
                n += ('0' + val_);
            else if (val_ == 10)
                n += "10";
            else if (val_ == 11)
                n += 'J';
            else if (val_ == 12)
                n += 'Q';
            else if (val_ == 13)
                n += 'K';
            else
                n += 'A';

            // Card Suit
            if (suit_ == 0)
                n += 'S';
            else if (suit_ == 1)
                n += 'C';
            else if (suit_ == 2)
                n += 'D';
            else if (suit_ == 3)
                n += 'H';

            return n;
        }
};

#endif
