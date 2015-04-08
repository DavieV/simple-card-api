#ifndef _CARD_DV_
#define _CARD_DV_

#include <string>
#include <algorithm>
#include <iostream>

enum class suits {spades, clubs, diamonds, hearts};

enum class card_val {two, three, four, five, six, seven, eight, nine,
                    ten, jack, queen, king, ace};

suits& operator ++(suits& s) {
    switch (s) {
        case suits::spades:
            s = suits::clubs;
            break;
        case suits::clubs:
            s = suits::diamonds;
            break;
        case suits::diamonds:
            s = suits::hearts;
            break;
        default:
            break;
    }
    return s;
}

card_val& operator ++(card_val& v) {
    switch (v) {
        case card_val::two:
            v = card_val::three;
            break;
        case card_val::three:
            v = card_val::four;
            break;
        case card_val::four:
            v = card_val::five;
            break;
        case card_val::five:
            v = card_val::six;
            break;
        case card_val::six:
            v = card_val::seven;
            break;
        case card_val::seven:
            v = card_val::eight;
            break;
        case card_val::eight:
            v = card_val::nine;
            break;
        case card_val::nine:
            v = card_val::ten;
            break;
        case card_val::ten:
            v = card_val::jack;
            break;
        case card_val::jack:
            v = card_val::queen;
            break;
        case card_val::queen:
            v = card_val::king;
            break;
        case card_val::king:
            v = card_val::ace;
            break;
        default:
            break;
    }
    return v;
}

class card {
    private:
        card_val val_;
        suits suit_;

    public:
        card(card_val v, suits s) : val_(v), suit_(s) { }

        card(card const& c) : val_(c.val_), suit_(c.suit_) { }

        card& operator =(card const& c) {
            val_ = c.val_;
            suit_ = c.suit_;
            return *this;
        }

        card(card&& c) : val_(std::move(c.val_)), suit_(std::move(c.suit_)) { }

        card& operator =(card&& c) {
            val_ = std::move(c.val_);
            suit_ = std::move(c.suit_);
            return *this;
        }

        card_val val() const { return val_; }
        suits suit() const { return suit_; }

        bool operator <(card const& c) const {
            return val_ < c.val();
        }

        bool operator >(card const& c) const {
            return val_ > c.val();
        }
};



std::ostream& operator <<(std::ostream& os, suits const& s) {
    std::string n;

    switch (s) {
        case suits::spades:
            n = "S";
            break;
        case suits::clubs:
            n = "C";
            break;
        case suits::diamonds:
            n = "D";
            break;
        case suits::hearts:
            n = "H";
            break;
        default:
            break;
    }

    os << n;
    return os;
}

std::ostream& operator <<(std::ostream& os, card_val const& v) {
    std::string n;

    switch (v) {
        case card_val::two:
            n = "2";
            break;
        case card_val::three:
            n = "3";
            break;
        case card_val::four:
            n = "4";
            break;
        case card_val::five:
            n = "5";
            break;
        case card_val::six:
            n = "6";
            break;
        case card_val::seven:
            n = "7";
            break;
        case card_val::eight:
            n = "8";
            break;
        case card_val::nine:
            n = "9";
            break;
        case card_val::ten:
            n = "10";
            break;
        case card_val::jack:
            n = "J";
            break;
        case card_val::queen:
            n = "Q";
            break;
        case card_val::king:
            n = "K";
            break;
        case card_val::ace:
            n = "A";
            break;
        default:
            break;
    }

    os << n;
    return os;
}

std::ostream& operator <<(std::ostream& os, card const& c) {
    os << c.val() <<  c.suit();
    return os;
}

#endif
