#include <iostream>
#include <limits>
#include "headers/Search.h"
#include "headers/Run.h"

int main() {
    Search search("Zerind","Bucharest",R"(C:\Users\MoQing\Desktop\RomaniaMap\Romania.txt)");
    Run run(&search);
    while (true){
        run.showMenu();
        run.getChoice();
    }
}
