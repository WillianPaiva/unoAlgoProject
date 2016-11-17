#include "Signature.h"

Signature::Signature(vector<Card *> cards, vector<Card *> used, char type,
                     int size) {
  this->cards = cards;
  this->used = used;
  this->type = type;
  this->size = size;
}

string Signature::toString() {
  std::ostringstream oss;
  oss << "{(";

  for(auto const &value : cards){
    oss << value->toString();
  }
  oss << ")," << type << ",{";
  for(auto const &value : used){
    oss << value->toString();
  }
  return oss.str();
}

void Signature::setSize(int x){
  this->size = x;
}
