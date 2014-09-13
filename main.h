#pragma once

struct pot {int x, y;};

class rct;

pot newPot(int, int);
pot randPot(int, int, int, int);
rct * newRect(pot, pot);
bool isTaken(std::string);
int randInt(int, int);
int getInt(std::string, int, int);
std::string getStr(std::string);
void pPot(pot);
void pRct(rct *);
