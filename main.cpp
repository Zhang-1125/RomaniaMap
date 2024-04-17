#include <iostream>
#include "headers/Search.h"


int main() {
    Search search("Arad","Bucharest");
    search.Init(R"(C:\Users\MoQing\Desktop\RomaniaMap\Romania.txt)");
    search.AStar();
    return 0;
}


