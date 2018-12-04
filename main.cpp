#include <iostream>
#include "Reader.h"
#include "Truck.h"
#include "Node.h"
#include "Solution.h"
#include "Construction.h"
#include "ReorderNodes.h"
#include "AddNodes.h"

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
    cout << "aca" << endl;

//    deletenode->setDeletableTrips(solution, 1);
//    cout << "ACA" << endl;
//    for (Trip *t: deletenode->deletableTrips){
//        cout << "deletable :" << t->finalNode->getId() << endl;
//    }
//    deletenode->deleteTrip(solution,1);
//
//    delete deletenode;


//    auto *swapNode = new reorderNodes();
//    for(Route *route: solution->routes){
////        cout << "inicio" << endl;
////        swapNode->printRoute(route);
//        for(int i = 0; i < route->trips.size()-1; ++i){
//            swapNode->removeTrip(i, route, solution);
//            swapNode->setBest(route, problemInstance);
//            swapNode->insertTrip(route, solution);
//        }
////        cout << "final" << endl;
////        swapNode->printRoute(route);
//    }
//    solution->printAll();

    auto *addNode = new AddNodes();

    addNode->movement(solution);

//    solution->printAll();

    delete solution;



    return 0;
}