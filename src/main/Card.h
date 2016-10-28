#ifndef CARD_H
#define CARD_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
using namespace std;

class Card {
  int number;
  int color;

public:
  int getNumber();
  int getColor();
  Card(int x, int y);
  Card(string s);
  Card();
  bool operator==(const Card &rhs) const {
    return this->number == rhs.number && this->color == rhs.color ;
  }
  string toString();
  bool isNext(Card c);
  int hashCode() const;
};
#endif
