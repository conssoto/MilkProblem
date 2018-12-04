#include "AddNodes.h"

AddNodes::AddNodes() = default;

AddNodes::~AddNodes(){
    for (Trip *t: this->neighborhood){
        delete t; // se borran los trips menos el primero
    }
    this->neighborhood.clear(); // se borran todos los punteros
}

//void AddNodes::removeTrip(int tripIndex, Route *route, Solution *solution) {
//    Trip *nextTrip = route->trips[tripIndex + 1];
//
//    route->distance -= route->trips[tripIndex]->distance + nextTrip->distance;
//    nextTrip->initialNode = route->trips[tripIndex]->initialNode;
//    nextTrip->distance = solution->problemInstance->calculateDistance(nextTrip->initialNode, nextTrip->finalNode);
//    nextTrip->setBenefit(solution->calculateBenefit(nextTrip));
//    route->distance +=nextTrip->distance;
//
//
//
//    route->trips.erase(route->trips.begin() + tripIndex); // borrar trip
//};

bool AddNodes::fitsInTruck(Route *route, Node *node){
    return route->remainingCapacity >= node->getProduction();
}

void AddNodes::deleteOptions(vector<Trip *> options){
    for (int i = 1; i < options.size(); ++i){
        delete options[i]; // se borran los trips menos el primero
    }
    options.clear(); // se borran todos los punteros
}

Trip *AddNodes::getBestNeighbor(Solution *solution, Route *route, Trip *trip) {
    vector<Trip *> options;
    Trip *selectedTrip = nullptr;
    Node *currentNode = trip->initialNode;
    Node *nextNode = trip->finalNode;

    for (int i = 0; i < solution->nodesXQuality[route->getTypeIndex()]; ++i) {
        Node *option = solution->unvisitedNodes[i];
        if (fitsInTruck(route, option)) { // TODO eliminar trips

            cout << "fits:" << option->getId() << endl;
            options.push_back(solution->fakeTrip(currentNode, option, nextNode));
        }
    }
    if (!options.empty()) {
        sort(options.begin(), options.end(), sortByBenefit);
        selectedTrip = options[0]; //puntero apunta al trip
        deleteOptions(options); // elimina punteros y trips?
    }
    return selectedTrip;
}

void AddNodes::setNeighborhood(Solution *solution, Route *route){
    vector <Trip *> options;
    cout << "en " << route->id << " caben: " << endl;

    for(Trip *trip: route->trips){
        cout << "para el nodo: " << trip->initialNode->getId() << endl;
        Trip *selectedTrip = getBestNeighbor(solution, route, trip);
        if (selectedTrip){
            cout << "selectedTrip: " << endl;
            selectedTrip->printAll();
            options.push_back(selectedTrip);
        }
    }
    this->neighborhood = options;
    cout << "neigthbor: " << endl;
    for (Trip *trip: this->neighborhood){
        trip->printAll();
    }
}

