//
// Created by MoQing on 2024/4/18.
//
#include <iostream>
#include "../headers/Run.h"

Run::Run(Search *searchPtr) {
    this->searchPtr = searchPtr;
}


void Run::showMenu() {
    std::cout<<"-----------------------RomaniaMap-----------------------"<<std::endl;
    std::cout<<"Please choose the algorithm you want to use:\n"
             <<"\t1.BFS\n"
             <<"\t2.DFS\n"
             <<"\t3.UCS\n"
             <<"\t4.GBFS\n"
             <<"\t5.IDDFS\n"
             <<"\t6.AStar\n"
             <<"      -----------\n"
             <<"\t0.Exit"<<std::endl;
}

void Run::getChoice() {
    int choice;
    std::cout<<"Please input your choice:";
    std::cin>>choice;
    switch (choice) {
        case 1:
            searchPtr->BFS();
            break;
        case 2:
            searchPtr->DFS();
            break;
        case 3:
            searchPtr->UCS();
            break;
        case 4:
            searchPtr->GBFS();
            break;
        case 5:
            std::cout<<"Please choose the depth you want to search:";
            int depth;
            std::cin>>depth;
            searchPtr->IDDFS(depth);
            break;
        case 6:
            searchPtr->AStar();
            break;
        case 0:
            exit(0);
        default:
            std::cout<<"Wrong choice!"<<std::endl;
            break;
    }
    hold();
}

void Run::hold() {
    std::cout<<"Press Enter to continue..."<<std::endl;
    std::cin.get();
    std::cin.get();
}


