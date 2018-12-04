#include "ReorderNodes.h"

reorderNodes::reorderNodes(){};

reorderNodes::~reorderNodes(){};

void reorderNodes::removeTrip(int tripIndex, Route *route, Solution *solution) {
    Trip *nextTrip = route->trips[tripIndex + 1];

    this->bestIndex = tripIndex;
    this->node = route->trips[tripIndex]->finalNode;
    this->bestDistance = route->trips[tripIndex]->distance + nextTrip->distance;

    route->distance -= route->trips[tripIndex]->distance + nextTrip->distance;

    nextTrip->initialNode = route->trips[tripIndex]->initialNode;
    nextTrip->distance = solution->problemInstance->calculateDistance(nextTrip->initialNode, nextTrip->finalNode);
    nextTrip->setBenefit(solution->calculateBenefit(nextTrip));

    route->distance +=nextTrip->distance;

    this->bestDistance -= nextTrip->distance;
    route->trips.erase(route->trips.begin() + tripIndex); // borrar trip
};

void reorderNodes::setBest(Route *route, ProblemInstance *problemInstance) {
    for (int i = 1; i < route->trips.size(); ++i) {
        int a(problemInstance->calculateDistance(route->trips[i]->initialNode, this->node));
        int b(problemInstance->calculateDistance(this->node, route->trips[i]->finalNode));
        if (a + b - route->trips[i]->distance <= this->bestDistance and i != this->bestIndex) {
            this->bestDistance = a + b - route->trips[i]->distance;
            this->bestIndex = i;
            break;
        }
    }
}

void reorderNodes::insertTrip(Route *route, Solution *solution) {
    Trip *bestTrip = route->trips[this->bestIndex];

    route->distance -= bestTrip->distance;
    Trip *trip = solution->newTrip(bestTrip->initialNode, this->node);


    bestTrip->initialNode = this->node;
    bestTrip->distance = solution->problemInstance->calculateDistance(bestTrip->initialNode, bestTrip->finalNode);
    bestTrip->setBenefit(solution->calculateBenefit(bestTrip));

    route->distance += bestTrip->distance + trip->distance;

    route->trips.insert(route->trips.begin() + this->bestIndex, trip);
}

void reorderNodes::printRoute(Route *route){
    cout << "Total distance: " << route->distance << endl;
    for(Trip *trip: route->trips){
    cout << trip->initialNode->getId() << "-" << trip->finalNode->getId() << ":" << trip->distance << "     ";
    }
    cout << endl;
}

