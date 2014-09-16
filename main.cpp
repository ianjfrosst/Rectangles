#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "main.h"

std::vector<rct *> rcts;

pot * randPot(int minx, int maxx, int miny, int maxy) {
    return new pot(randInt(minx, maxx), randInt(miny, maxy));
}

class rct {
public:
    rct(pot * botLeft, pot * topRight, std::string n) {
        bl = botLeft;
        tr = topRight;
        name = n;
    };

    ~rct(){
        delete(bl);
        delete(tr);
    };

    pot * bl, * tr;
    std::string name;
};

rct * getIntersect(int i1, int i2) {
    rct * n = rcts[i1];
    rct * m = rcts[i2];

    if (!(n->bl->x <= m->tr->x && n->tr->x >= m->bl->x && n->bl->y <= m->tr->y && n->tr->y >= m->bl->y)) return nullptr;

    std::vector<int> xVec, yVec;

    xVec.push_back(n->bl->x);
    xVec.push_back(n->tr->x);
    xVec.push_back(m->bl->x);
    xVec.push_back(m->tr->x);

    yVec.push_back(n->bl->y);
    yVec.push_back(n->tr->y);
    yVec.push_back(m->bl->y);
    yVec.push_back(m->tr->y);

    std::sort(xVec.begin(), xVec.end());
    std::sort(yVec.begin(), yVec.end());

    return new rct(new pot(xVec[2], yVec[2]), new pot(xVec[3], yVec[3]), "");
}

rct * getUnion(int i1, int i2) {
    rct * n = rcts[i1];
    rct * m = rcts[i2];
    pot * a = new pot(std::min(n->bl->x, m->bl->x), std::min(n->bl->y, m->bl->y));
    pot * b = new pot(std::max(n->tr->x, m->tr->x), std::max(n->tr->y, m->tr->y));
    rct * re = new rct(a, b, "");
    return re;
}

bool nameComp(rct * i, rct * j) {
    return std::strcmp(i->name.c_str(), j->name.c_str()) < 0;
}

bool isTaken(std::string name) {
    for (rct * i : rcts) {if (name == i->name) {return true;}}
    return false;
}

bool ptInRect(pot * p, rct * r) {
    return r->bl->x <= p->x && p->x <= r->tr->x && r->bl->y <= p->y && p->y <= r->tr->y;
}

int randInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

std::string randName() {
    std::string name;
    do {
        name = "";
        for (int i = 0; i < 4; ++i) {name += randInt(97, 122);}
    } while (isTaken(name));
    return name;
}

int getInt(std::string query, int min, int max) {
    int input = 0;
    while(true) {
        std::cout << query;
        std::cin >> input;
        if (std::cin.good()) {if (min <= input && input <= max) {return input;}}
        std::cout << "Error: Input invalid\n";
        std::cin.clear();
    }
}

int getName(std::string query) {
    std::string input;
    while (true) {
        std::cout << query;
        std::cin >> input;
        for (int i = 0; i < rcts.size(); ++i) {if (rcts[i]->name == input) {return i;}}
        std::cout << "Error: Input invalid\n";
        std::cin.clear();
    }
}

std::string getStr(std::string query) {
    std::string input;
    std::cout << query;
    std::cin >> input;
    return input;
}

void pPot(pot * po) {
    std::cout << "(" << po->x << ", " << po->y << ")";
}

void pRct(rct * re) {
    std::cout << re->name << ": ";
    pPot(re->bl);
    std:: cout << " ";
    pPot(re->tr);
    std::cout << std::endl;
}

int main() {
    srand(time(NULL));
    int numRect = getInt("Number of rectangles to generate (0-25): ", 0, 25);
    for (int i = 0; i < numRect; ++i) {
        pot * a = randPot(0, 800-1, 0, 600-1);
        pot * b = randPot(a->x+1, 800, a->y+1, 600);
        rcts.push_back(new rct(a, b, randName()));
    }

    while (true) {
        std::cout << "1) Display all rectangles\n";
        std::cout << "2) Create a rectangle\n";
        std::cout << "3) Delete a rectangle\n";
        std::cout << "4) Find intersection\n";
        std::cout << "5) Find union\n";
        std::cout << "6) Sort by name\n";
        std::cout << "7) Point in rectangle\n";
        std::cout << "8) Quit\n";

        int ind1, ind2;
        pot * a, * b;
        rct * re;
        std::string name;

        switch (getInt("Choice: ", 1, 8)) {
            case 1:
                for (rct * i : rcts) {pRct(i);}
                break;

            case 2:
                do {
                    name = getStr("Enter a name for the new rectangle: ");
                } while (isTaken(name));
                a = new pot(getInt("Bottom left x: ", 0, 800-1), getInt("Bottom left y: ", 0, 800));
                b = new pot(getInt("Top right x: ", a->x+1, 800), getInt("Top right y: ", a->y+1, 600));
                rcts.push_back(new rct(a, b, name));
                break;

            case 3:
                ind1 = getName("Enter the name of the rectangle to delete: ");
                rcts.erase(rcts.begin()+ind1);
                break;

            case 4:
                ind1 = getName("Enter the name of rectangle 1: ");
                ind2 = getName("Enter the name of rectangle 2: ");
                re = getIntersect(ind1, ind2);
                if (re != nullptr) {
                    pRct(re);
                } else {
                    std::cout << "Rectangles do not intersect\n";
                }
                delete(re);
                break;

            case 5:
                ind1 = getName("Enter the name of rectangle 1: ");
                ind2 = getName("Enter the name of rectangle 2: ");
                re = getUnion(ind1, ind2);
                pRct(re);
                delete(re);
                break;

            case 6:
                std::sort(rcts.begin(), rcts.end(), nameComp);
                break;

            case 7:
                ind1 = getName("Enter name of rectangle: ");
                a = new pot(getInt("Enter x of point: ", 0, 800), getInt("Enter y of point: ", 0, 600));
                if (ptInRect(a, rcts[ind1])) {
                    std::cout << "Point is in rectangle\n";
                } else {
                    std::cout << "Point is not in rectangle\n";
                }
                break;

            case 8:
                for (rct * i : rcts) {delete(i);}
                return 0;

            default:
                break;
        }
    }
}