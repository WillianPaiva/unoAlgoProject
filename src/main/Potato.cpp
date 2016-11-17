#include "Potato.h"

Potato::Potato(int x) { this->id = x; }
Potato::Potato() { this->id = 0; }

void Potato::add(Card *c) { this->cards.push_back(c); }

vector<Card *> Potato::getList() { return this->cards; }

int Potato::size() { return this->cards.size(); }

int Potato::getId() { return this->id; }

vector<Card *> Potato::getIntersection(Potato p) {
  vector<Card *> intersection;
  vector<Card *> listB = p.getList();
  for (auto x = this->cards.begin(); x != this->cards.end(); x++) {
    if (find(listB.begin(), listB.end(), *x) != listB.end()) {
      intersection.push_back(*x);
    }
  }
  return intersection;
}

void Potato::makePotato(vector<Card *> &cards, Card *c, Potato *p) {
  p->add(c);
  Card actual = *c;
  while (getNext(cards, actual, p)) {
  }
}

bool Potato::getNext(vector<Card *> &cards, Card &c, Potato *p) {

  for (std::size_t i = 0; i < cards.size(); i++) {
    if (c.isNext(*cards[i])) {
      p->add(cards[i]);
      c = *cards[i];
      cards.erase(cards.begin() + i);
      return true;
    }
  }
  return false;
}

