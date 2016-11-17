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

<<<<<<< HEAD
=======
vector<Signature *> Potato::getSigs() { return this->sigs; }

void Potato::genSignatures(vector<Potato *> p) {

  for (auto const &card : this->cards) {
    vector<Card *> temp(cards);
    int pos = find(temp.begin(), temp.end(), card) - temp.begin();
    temp.erase(temp.begin() + pos);
    vector<Card *> result;
    result.push_back(card);
    genSignatureCalc(temp, result, *card);
  }
  for (auto const &value : p) {
    if (value->getId() != this->id) {
      for (auto const &l : this->interpolations) {
        vector<Card *> intesec(this->getIntersection(*value));
        vector<Card *> lis;
        vector<Card *> used;
        char type;
        Card *begin = l[0];
        Card *end = l[l.size() - 1];
        if (find(intesec.begin(), intesec.end(), begin) != intesec.end() &&
            find(intesec.begin(), intesec.end(), end) != intesec.end()) {
          type = 'a';
          lis.push_back(begin);
          lis.push_back(end);
          for (auto const &d : l) {
            if (find(intesec.begin(), intesec.end(), d) != intesec.end() &&
                !(find(lis.begin(), lis.end(), d) != lis.end())) {
              used.push_back(d);
            }
          }
        } else if (find(intesec.begin(), intesec.end(), begin) !=
                   intesec.end()) {
          type = 'b';
          lis.push_back(begin);
          for (auto const &d : l) {
            if (find(intesec.begin(), intesec.end(), d) != intesec.end() &&
                !(find(lis.begin(), lis.end(), d) != lis.end())) {
              used.push_back(d);
            }
          }
        } else if (find(intesec.begin(), intesec.end(), end) != intesec.end()) {
          type = 'b';
          lis.push_back(end);
          for (auto const &d : l) {
            if (find(intesec.begin(), intesec.end(), d) != intesec.end() &&
                !(find(lis.begin(), lis.end(), d) != lis.end())) {
              used.push_back(d);
            }
          }
        } else {
          type = 'c';
          for (auto const &d : l) {
            if (find(intesec.begin(), intesec.end(), d) != intesec.end()) {
              used.push_back(d);
            }
          }
        }
        bool found = false;
        for(auto const &si : this->sigs){
          if(si->equals(lis, used,type,this->id,value->getId())){
            if(si->getSize() < l.size()){
              si->setSize(l.size());
            }
            found = true;
          }

        }
        if(!found && l.size() > 1){   
          this->sigs.push_back(new Signature(lis,used,type,l.size(),this->id,value->getId()));
        }
      }
    }
  }
}

void Potato::genSignatureCalc(vector<Card *> cards, vector<Card *> result,
                              Card actual) {
  if (!cards.empty()) {
    for (auto const &card : cards) {
      if (actual.isNext(*card)) {
        vector<Card *> temp(cards);
        int pos = find(temp.begin(), temp.end(), card) - temp.begin();
        temp.erase(temp.begin() + pos);
        vector<Card *> r(result);
        r.push_back(card);
        genSignatureCalc(temp, r, *card);
      }
    }
  }
  vector<Card *> res(result);
  this->interpolations.push_back(res);
}
>>>>>>> master
