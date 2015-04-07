#ifndef _EUCHRE_DV_H_
#define _EUCHRE_DV_H_

#include "edeck.hpp"
#include "card.hpp"
#include <vector>

class euchre {
    private:
        edeck deck_;

    public:
        euchre() : deck_() { }

        void shuffle() {
            deck_.shuffle();
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
        int suit(int trump, card c1) const {
            if (is_l_bower(trump, c1))
                return trump;
            return c1.suit();
        }

        /*
         * AI NOTES:
         *  - function to determine if the hand is winnable
         *      - based on cards currently in play
         *      - eventually create more advanced probalistic version
         */
};

#endif
