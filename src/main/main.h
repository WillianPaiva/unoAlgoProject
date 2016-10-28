#pragma once
#include "Potato.h"
#include "Card.h"
// returns the interval at which the program frobnicates
// may also throw InvalidOperation of the frobnication interval can't be retrieved
void GetFrobnicationInterval();

void breakLine();
Potato *makeNext(vector<Card *> &restant, vector<Card *> &previous);
