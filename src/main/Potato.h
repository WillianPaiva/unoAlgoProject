#ifndef POTATO_H
#define POTATO_H

#include "Card.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Potato {
  vector<Card *> cards;
  vector<vector<Card *>> interpolations;
  int id;

public:
  Potato();
  Potato(int x);
  void add(Card *c);
  vector<Card *> getList();
  int size();
  int getId();
  vector<Card *> getIntersection(Potato p);
  string toString();
  void makePotato(vector<Card *> &cards, Card *c, Potato *p);
  bool getNext(vector<Card *> &cards, Card &c, Potato *p);
};

#endif
