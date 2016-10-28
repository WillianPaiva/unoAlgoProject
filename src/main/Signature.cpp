#include "Signature.h"

Signature::Signature(vector<Card *> cards, vector<Card *> used, char type,
                     int size, int potato1, int potato2) {
  this->cards = cards;
  this->used = used;
  this->type = type;
  this->size = size;
  this->potato1=potato1;
  this->potato2=potato2;
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
  oss << "}}," << size << "(" << potato1 << "),(" << potato2 << ")" ;
  return oss.str();
}

void Signature::setSize(int x){
  this->size = x;
}
