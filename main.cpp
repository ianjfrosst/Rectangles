#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>
#include "main.h"

std::vector<rct *> rcts;

pot newPot(int x, int y) {
    pot res;
    res.x = x;
    res.y = y;
    return res;
}

pot randPot(int minx, int maxx, int miny, int maxy) {
    return newPot(randInt(minx, maxx), randInt(miny, maxy));
}

class rct {
public:
    rct(pot bl, pot tr, std::string n) {
        botLeft = bl;
        topRight = tr;
        name = n;
    };

    pot botLeft, topRight;
    std::string name;
};

rct  * newRect(pot botLeft, pot topRight) {
    std::string name;
    do {
        name = "";
        for (int i = 0; i < 4; ++i) {
            name += randInt(97, 122);
        }
    } while (isTaken(name));
    rct * res = new rct(botLeft, topRight, name);
    return res;
}

bool isTaken(std::string name) {
    for (rct * i : rcts) {if (name == i->name) {return true;}}
    return false;
}

int randInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int getInt(std::string query, int min, int max) {
    int input = 0;
    while(true) {
        std::cout << query;
        std::cin >> input;
        if (std::cin.good()) {if (min <= input && input <= max) {return input;}}
        std::cout << "Error: input invalid\n";
        std::cin.clear();
    }
}

std::string getStr(std::string query) {
    std::string input;
    std::cout << query;
    std::cin >> input;
    return input;
}

void pPot(pot po) {
    std::cout << "(" << po.x << ", " << po.y << ")";
}

void pRct(rct * re) {
    std::cout << re->name << ": ";
    pPot(re->botLeft);
    std:: cout << " ";
    pPot(re->topRight);
    std::cout << std::endl;
}

int main() {
    srand(time(NULL));
    int numRect = getInt("Number of rectangles to generate (0-25): ", 0, 25);
    for (int i = 0; i < numRect; ++i) {
        rcts.push_back(newRect(randPot(0, 800, 0, 600), randPot(0, 800, 0, 600)));
    }

    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1) Display all rectangles\n";
        std::cout << "2) Create a rectangle\n";
        std::cout << "3) Delete a rectangle\n";
        std::cout << "4) Find intersection\n";
        std::cout << "5) Find union\n";
        std::cout << "6) Sort by name\n";
        std::cout << "7) Point in rectangle\n";
        std::cout << "8) Quit\n";

        switch (getInt("Choice: ", 1, 8)) {
            case 1:
                for (rct * i : rcts) {pRct(i);}
                break;

            case 2:

                break;

            case 3:

                break;

            case 4:

                break;

            case 5:

                break;

            case 6:

                break;

            case 7:

                break;

            case 8:
                return 0;

            default:
                break;


        }
    }
}