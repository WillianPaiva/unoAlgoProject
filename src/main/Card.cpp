#include "Card.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <vector>

Card::Card(int x, int y) {
  this->number = x;
  this->color = y;
}

Card::Card(string s) {
  if (s.size() > 2) {
    vector<string> words;
    boost::split(words, s, boost::is_any_of(", "), boost::token_compress_on);

    this->number = atoi(words[1].c_str());
    this->color = atoi(words[0].c_str());
  }
}

Card::Card() {
  this->number = 0;
  this->color = 0;
}

int Card::getNumber() { return this->number; }

int Card::getColor() { return this->color; }

string Card::toString() {
  string result = "[" + to_string(color) + "," + to_string(number) + "]";
  return result;
}

int Card::hashCode() const {
  int prime = 31;
  int result = 1;
  result = prime * result + color;
  result = prime * result + number;
  return result;
}

bool Card::isNext(Card c) {

  return (this->number == c.getNumber() || this->color == c.getColor());
}
