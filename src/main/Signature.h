#ifndef SIGNATURE_H
#define SIGNATURE_H

#include "Card.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Signature {
     vector<Card *> cards;
     vector<Card *> used;
     char type;
     int size;

public:
     Signature();
     Signature(vector<Card *> cards, vector<Card *> used, char type, int size);

     string toString();

     bool equals(vector<Card *> c, vector<Card *> u, char t) {
          return (this->cards == c && this->used == u && this->type == t);
     }

     // getters and setters

     void setSize(int x);
     int getSize() { return this->size; }
     void setType(char type) { this->type = type; }
     char getType() { return this->type; }
     void setUsed(vector<Card *> used) { this->used = used; }
     vector<Card *> getUsed() { return this->used; }
     void setCards(vector<Card *> cards) { this->used = cards; }
     vector<Card *> getCards() { return this->cards; }
};

#endif
