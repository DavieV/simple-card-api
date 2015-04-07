#ifndef _CARD_DV_
#define _CARD_DV_

#include <string>

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

        card(card const& c) : val_(c.val()), suit_(c.suit()) { }

        card& operator =(card const& c) {
            val_ = c.val();
            suit_ = c.suit();
            return *this;
        }

        card(card&& c) : val_(c.val()), suit_(c.suit()) { }

        card& operator =(card&& c) {
            val_ = c.val();
            suit_ = c.suit();
            return *this;
        }

        int val() const { return val_; }
        int suit() const { return suit_; }

        bool operator <(card c) const {
            return val_ < c.val();
        }

        bool operator >(card c) const {
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
