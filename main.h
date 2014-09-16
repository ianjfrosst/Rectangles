#pragma once

struct pot {
    pot(int a, int b) {
        x = a;
        y = b;
    }
    int x, y;
};

class rct;

pot * randPot(int, int, int, int);
rct * getIntersect(int, int);
rct * getUnion(int, int);
bool nameComp(rct *, rct *);
bool isTaken(std::string);
bool ptInRect(pot *, rct *);
int randInt(int, int);
std::string randName();
int getInt(std::string, int, int);
int getName(std::string);
std::string getStr(std::string);
void pPot(pot *);
void pRct(rct *);
