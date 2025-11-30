#ifndef DS_WET1_WINTER_2024_2025_HERD_H
#define DS_WET1_WINTER_2024_2025_HERD_H

#include "AVLtree.h"
#include "Horse.h"

class herd {
private:
    AVL<int, horse*> horses;

public:
    herd() = default;
    ~herd() {
        horses.destroyTree();
    };

    void addHorse(horse* h, int horseID) {
        try {
            horses.insertNode(horseID, h); //may throw std::bad_alloc
        } catch (const std::bad_alloc& e) {
            throw e;
        }
    }

    void removeHorse(int horseID) {
        horses.removeNode(horseID);
    }

    AVL<int, horse*>& getHorses() {
        return horses;
    }
};

#endif // DS_WET1_WINTER_2024_2025_HERD_H
