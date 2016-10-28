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
  int potato1;
  int potato2;

public:
  Signature();
  Signature(vector<Card *> cards, vector<Card *> used, char type, int size, int potato1, int potato2);
  string toString();
  bool equals(vector<Card *> c, vector<Card *> u, char t, int p1, int p2) {
    return (this->cards == c && this->used == u && this->type == t && this->potato1==p1 && this->potato2==p2);
  }
  bool conect(Signature *s) {
    if ((this->type != s->type || this->type == 'b') &&
        !(this->type == 'c' || s->type == 'c')) {
			
    }
  }
  
  int getPotato1(){return this->potato1;}
  int getPotato2(){return this->potato2;}
  char getType(){return this->type;}
  
  void setSize(int x);
  int getSize() { return this->size; }
};

#endif
