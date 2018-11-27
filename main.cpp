#include <iostream>
#include "Reader.h"
#include "Truck.h"
#include "Node.h"
#include "Solution.h"
#include "Construction.h"
#include "ReorderNodes.h"

using namespace std;

int main() {
//    cout << "Enter instance number: ";
//    cin.getline(instanceOption, 3);
    srand(3);
    ProblemInstance *problemInstance;

//    Reader r(instanceOption);
    Reader r("1");
    problemInstance = r.readInputFile();
    problemInstance->printAll();

    auto *solution = new Solution(problemInstance);
    auto *construction = new Construction(5);
//    auto *deletenode = new DeleteNode();

    construction->feasibleSolution(solution);
//    deletenode->setDeletableTrips(solution, 1);
//    cout << "ACA" << endl;
//    for (Trip *t: deletenode->deletableTrips){
//        cout << "deletable :" << t->finalNode->getId() << endl;
//    }
//    deletenode->deleteTrip(solution,1);
//
//    delete deletenode;
    auto *swapNode = new reorderNodes();
    for(Route *route: solution->routes){
        cout << "inicio" << endl;
        swapNode->printRoute(route);
        for(int i = 0; i < route->trips.size()-1; ++i){
            swapNode->removeTrip(i, route, problemInstance);
            swapNode->setBest(route, problemInstance);
            swapNode->insertTrip(route, solution, problemInstance);
        }
        cout << "final" << endl;
        swapNode->printRoute(route);
    }




    cout << "Distance cost: " << solution->kilometerCost *  solution->distance << endl;

    cout << "Milk cost: " << endl;
    double suma(0);
    for(int i = 0; i < solution->recollected.size(); ++i){
        suma +=solution->recollected[i] * solution->literCost[i];
        cout << solution->recollected[i] * solution->literCost[i] << endl;
    }
    cout << "Total Milk cost: " << suma << endl;

    delete solution;



    return 0;
}