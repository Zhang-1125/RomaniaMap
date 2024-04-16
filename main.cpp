#include <iostream>
#include "headers/Search.h"
#include <queue>

int main() {
    Node Zerind("Zerind");
    Node Arad("Arad");
    Node Sibiu("Sibiu");
    Node Oradea("Oradea");
    Node Timisoara("Timisoara");
    Node Lugoj("Lugoj");
    Node Mehadia("Mehadia");
    Node Drobeta("Drobeta");
    Node Craiova("Craiova");
    Node Pitesti("Pitesti");
    Node RimnicuVilcea("RimnicuVilcea");
    Node Bucharest("Bucharest");
    Node Fagaras("Fagaras");
    Node Giurgiu("Giurgiu");
    Node Urziceni("Urziceni");
    Node Eforie("Eforie");
    Node Hirsova("Hirsova");
    Node Vaslui("Vaslui");
    Node Iasi("Iasi");
    Node Neamt("Neamt");

    Zerind.addNeighbor(&Arad,75,&Oradea,71);                                       // start
    Arad.addNeighbor(&Zerind,75,&Sibiu,140,&Timisoara,118);
    Sibiu.addNeighbor(&Arad,140,&Oradea,151,&Fagaras,99,&RimnicuVilcea,80);
    Oradea.addNeighbor(&Zerind,71,&Sibiu,151);
    Timisoara.addNeighbor(&Arad,118,&Lugoj,111);
    Lugoj.addNeighbor(&Timisoara,111,&Mehadia,70);
    Mehadia.addNeighbor(&Lugoj,70,&Drobeta,75);
    Drobeta.addNeighbor(&Mehadia,75,&Craiova,120);
    Craiova.addNeighbor(&Drobeta,120,&Pitesti,138,&RimnicuVilcea,146);
    Pitesti.addNeighbor(&Craiova,138,&RimnicuVilcea,97,&Bucharest,101);
    Bucharest.addNeighbor(&Pitesti,101,&Urziceni,85,&Giurgiu,90,&Fagaras,211);          // goal
    RimnicuVilcea.addNeighbor(&Sibiu,80,&Craiova,146,&Pitesti,97);
    Fagaras.addNeighbor(&Sibiu,99,&Bucharest,211);
    Giurgiu.addNeighbor(&Bucharest,90);
    Urziceni.addNeighbor(&Bucharest,85,&Vaslui,142,&Hirsova,98);
    Hirsova.addNeighbor(&Urziceni,98,&Eforie,86);
    Vaslui.addNeighbor(&Urziceni,142,&Iasi,92);
    Iasi.addNeighbor(&Vaslui,92,&Neamt,87);
    Neamt.addNeighbor(&Iasi,87);
    Eforie.addNeighbor(&Hirsova,86);

    Search search(&Arad,&Bucharest);

    search.UCS();

    return 0;
}
