#include <iostream>
#include "headers/Search.h"
#include "headers/Run.h"

int main() {
    Search search("Zerind","Bucharest","Romania.txt");
    Run run(&search);
    while (true){
        run.showMenu();
        run.getChoice();
    }
}
