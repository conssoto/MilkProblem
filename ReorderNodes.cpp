#include "ReorderNodes.h"

reorderNodes::reorderNodes(){};

reorderNodes::~reorderNodes(){};

void reorderNodes::removeTrip(int tripIndex, Route *route, ProblemInstance *problemInstance){
    this->bestIndex = tripIndex;
    this->node = route->trips[tripIndex]->finalNode;
    this->bestDistance = route->trips[tripIndex]->distance + route->trips[tripIndex+1]->distance;
    route->distance -= route->trips[tripIndex]->distance + route->trips[tripIndex+1]->distance;
    route->trips[tripIndex+1]->initialNode = route->trips[tripIndex]->initialNode;
    route->trips[tripIndex+1]->distance = problemInstance->calculateDistance(route->trips[tripIndex+1]->initialNode, route->trips[tripIndex+1]->finalNode);
    route->distance += route->trips[tripIndex+1]->distance;
    this->bestDistance -= route->trips[tripIndex+1]->distance;
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

void reorderNodes::insertTrip(Route *route, Solution *solution, ProblemInstance *problemInstance) {
    route->distance -= route->trips[this->bestIndex]->distance;
    Trip *trip = solution->newTrip(route->trips[this->bestIndex]->initialNode, this->node);
    route->trips[this->bestIndex]->initialNode = this->node;
    route->trips[this->bestIndex]->distance = problemInstance->calculateDistance(
            route->trips[this->bestIndex]->initialNode, route->trips[this->bestIndex]->finalNode);
    route->distance += route->trips[this->bestIndex]->distance + trip->distance;
    route->trips.insert(route->trips.begin() + this->bestIndex, trip);
}

void reorderNodes::printRoute(Route *route){
    cout << "Total distance: " << route->distance << endl;
    for(Trip *trip: route->trips){
    cout << trip->initialNode->getId() << "-" << trip->finalNode->getId() << ":" << trip->distance << "     ";
    }
    cout << endl;
}

