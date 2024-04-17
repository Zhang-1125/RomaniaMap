//
// Created by MoQing on 2024/4/18.
//

#ifndef ROMANIAMAP_RUN_H
#define ROMANIAMAP_RUN_H

#include "Search.h"

class Run {
public:
    explicit Run(Search *searchPtr);
    void showMenu();
    void getChoice();
private:
    Search* searchPtr;
    static void hold();
};

#endif //ROMANIAMAP_RUN_H
