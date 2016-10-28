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
  bool conect(Signature *s) {
    if ((this->type != s->type || this->type == 'b') &&
        !(this->type == 'c' || s->type == 'c')) {
    }
  }
  void setSize(int x);
  int getSize() { return this->size; }
};

#endif
