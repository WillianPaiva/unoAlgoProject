#include "main.h"
#include "Card.h"
#include "Colors.h"
#include "Potato.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
// there are other ways of getting a path relative to the executable, but this
// one is part of the STL soon (if you can talk about soon in c++ development)
#include <boost/filesystem.hpp>
using boost::filesystem::absolute;

// when testing, the main of gtest and this main function will collide,
// this prevents the collision, but it's an ugly hack like all ifdef branches
#ifdef UNIT_TESTS
#define MAIN not_main
#else
#define MAIN main
#endif

int idx = 0;
vector<Card *> cards;
vector<Potato *> potatoes;

int MAIN(int argc, char **argv) {
  // this way you can have a path relative to the executable
  // the absolute also gets rid of symlinks, so it should work pretty stable

  cout << RED << "reading cards from file" << RESET;
  breakLine();
  auto resource_path = absolute(argv[0]).parent_path() / "resources";
  fstream resource1((resource_path / "test2.txt").string());
  string line;
  // list of cards

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
  // get the first card
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
    potato->genSignatures(potatoes);
    breakLine();
    cout << GREEN << "signatures" << RESET << "\n";
    for(auto const &sig : potato->getSigs()){
      cout << CYAN << sig->toString() << RESET << "\n";
    }
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
