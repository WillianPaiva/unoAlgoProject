#pragma once
#include "Potato.h"
#include "Signature.h"
#include "Card.h"
// returns the interval at which the program frobnicates
// may also throw InvalidOperation of the frobnication interval can't be retrieved
void GetFrobnicationInterval();

void genSignatureCalc(vector<Card *> cards,
                      vector<Card *> result,
                              Card actual);

void sigcalc(vector<Card *> interp, vector<Card *> intersec);
void genSignatures(Potato *first, Potato *next);
void addSig(Signature newSig);
void breakLine();
Potato *makeNext(vector<Card *> &restant, vector<Card *> &previous);
void merge(vector<Card *> interception);
void mergeAA(Signature * a, Signature * b);
void mergeAB(Signature * a, Signature * b);
void mergeBA(Signature * a, Signature * b);
void mergeBB(Signature * a, Signature * b);
