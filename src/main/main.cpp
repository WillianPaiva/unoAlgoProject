

#include "main.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Card.h"
#include "Colors.h"
#include "Potato.h"
#include "Signature.h"

using namespace std;

#include <boost/filesystem.hpp>
using boost::filesystem::absolute;

#ifdef UNIT_TESTS
#define MAIN not_main
#else
#define MAIN main
#endif

int idx = 0;
vector<Card *> cards;
vector<Potato *> potatoes;
vector<Signature *> sigs;
vector<Signature *> mergesigs;
vector<vector<Card *>> interpolations;

int MAIN(int argc, char **argv) {
  cout << RED << "reading cards from file" << RESET;
  breakLine();
  auto resource_path = absolute(argv[0]).parent_path() / "resources";
  fstream resource1((resource_path / "test2.txt").string());

  string line;

  while (resource1) {
    std::getline(resource1, line);
    if (line.size() > 2) {
      Card *c = new Card(line);
      cards.push_back(c);
    }
  }

  for (auto const &value : cards) {
    cout << GREEN << value->toString() << " " << RESET;
  }

  breakLine();
  cout << CYAN << "creating the depth first tree\n" << RESET;

  vector<Card *> temp;
  Potato *test = makeNext(cards, temp);

  potatoes.push_back(test);
  breakLine();

  while (!cards.empty()) {
    vector<Card *> temp2(potatoes.back()->getList());
    Potato *test2 = makeNext(cards, temp2);
    potatoes.push_back(test2);
  }

  for (auto const &potato : potatoes) {
    breakLine();
    cout << MAGENTA << "potato id : " << WHITE << potato->getId() << "\n"
         << RESET;
    for (auto const &value : potato->getList()) {
      cout << CYAN << value->toString() << RESET;
    }
    breakLine();
  }

  for (int x = 0; x < potatoes.size() - 1; x++) {
    genSignatures(potatoes[x], potatoes[x + 1]);
  }
  for (auto const &si : sigs) {
    cout << CYAN << si->toString() << RESET << "\n";
  }
  return EXIT_SUCCESS;
}

void breakLine() {
  cout << BOLDYELLOW << "\n===================================================="
                        "==============================\n"
       << RESET;
}

Potato *makeNext(vector<Card *> &restant, vector<Card *> &previous) {
  Potato *result = new Potato(idx);
  if (previous.empty()) {
    Card *c = restant[0];
    // remove the first card from the cards list
    restant.erase(cards.begin());
    // make the first potato
    result->makePotato(cards, c, result);
  } else {
    Card *c = previous[previous.size() - 1];
    previous.pop_back();
    Potato *temp = new Potato();
    temp->makePotato(restant, c, temp);
    if (temp->getList().size() < 2) {
      return makeNext(restant, previous);
    } else {
      for (auto const &value : previous) {
        result->add(value);
      }
      for (auto const &value : temp->getList()) {
        result->add(value);
      }
    }
  }
  idx++;
  return result;
}

void genSignatures(Potato *first, Potato *next) {
  interpolations.clear();
  vector<Card *> intersec(next->getIntersection(*first));

  for (auto const &card : next->getList()) {
    vector<Card *> temp(next->getList());
    int pos = find(temp.begin(), temp.end(), card) - temp.begin();
    temp.erase(temp.begin() + pos);
    vector<Card *> result;
    result.push_back(card);
    genSignatureCalc(temp, result, *card);
  }
  for (auto const &interp : interpolations) {
    sigcalc(interp, intersec);
  }
}

void genSignatureCalc(vector<Card *> cards, vector<Card *> result,
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
  interpolations.push_back(res);
}

void sigcalc(vector<Card *> interp, vector<Card *> intersec) {
  vector<Card *> lis;
  vector<Card *> used;
  char type;
  Card *begin = interp[0];
  Card *end = interp[interp.size() - 1];

  //,-------------------------
  //| if is a type a signature
  //`-------------------------

  if (find(intersec.begin(), intersec.end(), begin) != intersec.end() &&
      find(intersec.begin(), intersec.end(), end) != intersec.end()) {
    type = 'a';
    lis.push_back(begin);
    lis.push_back(end);
    for (auto const &d : interp) {
      if (find(intersec.begin(), intersec.end(), d) != intersec.end() &&
          !(find(lis.begin(), lis.end(), d) != lis.end())) {
        used.push_back(d);
      }
    }
  }

  //,-------------------------
  //| if is a type b signature
  //`-------------------------

  else if (find(intersec.begin(), intersec.end(), begin) != intersec.end()) {
    type = 'b';
    lis.push_back(begin);
    for (auto const &d : interp) {
      if (find(intersec.begin(), intersec.end(), d) != intersec.end() &&
          !(find(lis.begin(), lis.end(), d) != lis.end())) {
        used.push_back(d);
      }
    }
  }

  bool found = false;
  for (auto const &si : sigs) {
    if (si->equals(lis, used, type)) {
      if (si->getSize() < interp.size()) {
        si->setSize(interp.size());
      }
      found = true;
    }
  }
  if (!found && interp.size() > 1) {
    sigs.push_back(new Signature(lis, used, type, interp.size()));
  }
}

// void merge(vector<Card *> interception) {
//   for (auto const &s : sigs) {
//     for (auto const &m : mergesigs) {
//       if (s->getType() == 'a') {
//         if(m->getType() == 'a'){
//         }
//         if(m->getType() == 'b'){
//         }
//       }
//       if (s->getType() == 'b') {
//         if(m->getType() == 'a'){
//         }
//         if(m->getType() == 'b'){
//         }
//       }
//     }
//   }
// }

// void mergeAA(Signature * a, Signature * b){
//   for(auto const &us a->getUsed()){
//   }
//   if(a->getCards() != b->getCards()){
//   }
// }
// void mergeAB(Signature * a, Signature * b);
// void mergeBA(Signature * a, Signature * b);
// void mergeBB(Signature * a, Signature * b);
