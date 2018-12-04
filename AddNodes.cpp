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
//    route->remainingCapacity =-route->trips[tripIndex]->finalNode->production;
//
//    route->trips.erase(route->trips.begin() + tripIndex); // borrar trip
//};

bool AddNodes::fitsInTruck(Route *route, Node *node){
    return route->remainingCapacity >= node->getProduction();
}

void AddNodes::deleteOptions(vector<Trip *> options, int aux = 1){
    for (int i = aux; i < options.size(); ++i){
        delete options[i]; // se borran los trips menos el primero
    }
    options.clear(); // se borran todos los punteros
}

Trip *AddNodes::getBestNeighbor(Solution *solution, Route *route, Trip *trip) { //solo positivos!
    vector<Trip *> options;
    Trip *selectedTrip = nullptr;
    Node *currentNode = trip->initialNode;
    Node *nextNode = trip->finalNode;

    for (int i = 0; i < solution->nodesXQuality[route->getTypeIndex()]; ++i) {
        Node *option = solution->unvisitedNodes[i];
        if (fitsInTruck(route, option)) {

            cout << "fits:" << option->getId() << endl;
            auto fakeTrip = solution->fakeTrip(currentNode, option, nextNode, route->id);
            if(fakeTrip->benefit > 0){
                options.push_back(fakeTrip);
            }
            else{
                cout << "negative benefit" << endl;
                delete fakeTrip;
            }
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
    cout << "en la ruta" << route->id << endl;

    for(Trip *trip: route->trips){
        cout << "para el nodo " << trip->initialNode->getId() << endl;
        Trip *selectedTrip = getBestNeighbor(solution, route, trip);
        if (selectedTrip){
            cout << "selectedTrip: " << endl;
            selectedTrip->printAll();
            options.push_back(selectedTrip);
        }
    }
    this->neighborhood = options;
}

void AddNodes::setTotalBenefit(){
    this->totalBenefit = 0;
    for(Trip *trip: this->neighborhood) { //siempre hay al menos uno, la planta
        this->totalBenefit += trip->benefit;
    }
}


Trip *AddNodes::roulette() {
    setTotalBenefit();
    int beta = rand() % 101;
    double choiceProbability(0);
    int aux(0);
    for (Trip *trip: this->neighborhood) {
        if (beta > choiceProbability) {
            choiceProbability += trip->benefit * 100.0 / this->totalBenefit;
        }
        if ((beta < choiceProbability) || (choiceProbability == 100)) {
            aux++;
            deleteOptions(this->neighborhood, aux);
            return trip;
        }
        aux++;
        delete trip;
    }

}

void AddNodes::insertTrip(Trip *selectedTrip, Solution *solution) {
    auto route = solution->routes[selectedTrip->routeId-1];
    for(int i = 0; i < route->trips.size(); ++i){
        if(route->trips[i]->initialNode == selectedTrip->initialNode){
            this->insertPosition = i;
            break;
        }
    }

    Trip *bestTrip = route->trips[this->insertPosition];

    route->distance -= bestTrip->distance;
    Trip *newTrip = solution->newTrip(bestTrip->initialNode, selectedTrip->finalNode);


    bestTrip->initialNode = selectedTrip->finalNode;
    bestTrip->distance = solution->problemInstance->calculateDistance(bestTrip->initialNode, bestTrip->finalNode);
    bestTrip->setBenefit(solution->calculateBenefit(bestTrip));

    route->distance += bestTrip->distance + newTrip->distance;
    route->remainingCapacity -= newTrip->finalNode->production;

    route->trips.insert(route->trips.begin() + this->insertPosition, newTrip);
    delete selectedTrip;
}


void AddNodes::movement(Solution *solution){
    for(Route *route: solution->routes){
        setNeighborhood(solution, route);
        if(!this->neighborhood.empty()){
            cout << "neigthbor: " << endl;
            for (Trip *trip: this->neighborhood){
                trip->printAll();
            }
            Trip *selectedTrip = roulette();
            cout << "selected: " << selectedTrip->initialNode->getId() << endl;
            insertTrip(selectedTrip, solution);
        }
        else{
            cout << "no neighborhood" << endl;
        }
    }

    cout << "inserted: " << endl;
    solution->printAll();

}
