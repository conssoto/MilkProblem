#include "Construction.h"

Construction::Construction(unsigned long alpha):alpha(alpha),totalProduction(0){};

Construction::~Construction(){
    cout<< "Deleting construction" << endl;

    for ( auto it = this->neighborhood.begin(); it != this->neighborhood.end(); ){
        this->neighborhood.erase(it);
    }
}

bool Construction::fitsInTruck(Route *route, Node *node){
    return route->remainingCapacity >= node->getProduction();
}

void Construction::deleteOptions(vector<Trip *> options, unsigned long alpha){
    for (int i = alpha; i < options.size(); ++i){
        delete options[i];
    }
}

vector<Trip *> Construction::getOptions(Solution *solution, int currentType, Node *currentNode) {
    vector<Trip *> options;
    for (int i = 0; i < solution->nodesXQuality[currentType - 1]; ++i) {
        Node *option = solution->unvisitedNodes[i];
        if (fitsInTruck(solution->routes.back(), option)) {
            options.push_back(solution->newTrip(currentNode, option));
        }
    }
    if (options.size() > this->alpha) {
        sort(options.begin(), options.end(), sortByDistance);
        deleteOptions(options, this->alpha);
        options.resize(this->alpha);
    }
    return options;
}

void Construction::setNeighborhood(Solution *solution, Route *currentRoute = nullptr) {
    if (currentRoute){
        if(currentRoute->trips.back()->finalNode == solution->plant){
            solution->distance-=currentRoute->trips.back()->distance; // disminuyo la distancia de vuelta a la plata
            currentRoute->distance -= currentRoute->trips.back()->distance;
            currentRoute->trips.pop_back(); //saco la vuelta a la planta
        }
        vector<Trip *> options(getOptions(solution,currentRoute->getType(), currentRoute->trips.back()->finalNode));
        if (options.empty()) {
            currentRoute->setFull();
            options.push_back(solution->newTrip(currentRoute->trips.back()->finalNode, solution->plant));
        }
        this->neighborhood = options;
    }
    else{
        Node *currentNode = solution->getCurrentNode();
        int currentType(solution->getUnsatisfiedType());

        //si volvio a la planta, por que ya se lleno el camion, se crea nueva ruta.
        if (currentNode->getId() == 0 && !solution->routes.back()->trips.empty()) {
            solution->addRoute(currentType);
        }
        vector<Trip *> options(getOptions(solution, currentType, currentNode));

        // si no hay opciones, vuelvo a la planta.
        if (options.empty()) {
            solution->routes.back()->setFull();
            options.push_back(solution->newTrip(currentNode, solution->plant));
        }
        this->neighborhood = options;
    }
}

void Construction::setTotalProduction(){
    this->totalProduction = 0;
    for(Trip *trip: this->neighborhood) { //siempre hay al menos uno, la planta
        this->totalProduction += trip->finalNode->getProduction();
    }
}

Trip *Construction::roulette() {
    setTotalProduction();
    if (this->totalProduction == 0) { //volver a la planta
        return this->neighborhood[0];
    }
    int beta = rand() % 101;
    double choiceProbability(0);
    int aux(0);
    for (Trip *trip: this->neighborhood) {
        if (beta > choiceProbability) {
            choiceProbability += trip->finalNode->getProduction() * 100.0 / this->totalProduction;
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

void Construction::updateIds(vector<Route *> routes){
    for (Route *r: routes){
        int routeId(r->getId());
        for (Trip *t: r->trips){
            t->setRouteId(routeId);
        }
    }
}

void Construction::feasibleSolution(Solution *solution) {
    // fase 1
    while (solution->getUnsatisfiedType() != -1) {
        setNeighborhood(solution);
        Trip *trip = roulette();
        solution->addTrip(trip, nullptr);
        solution->updateSolution(trip, nullptr);

        if (solution->unusedTrucks.empty() && !solution->routes.back()->trips.empty() &&
            solution->routes.back()->trips.back()->finalNode == solution->plant) {
            break; // iniciar fase 2
        }
    }
    cout << "FASE 1" << endl;
    solution->printAll();

    // fase 2
    while (solution->getUnsatisfiedType() != -1) {
        vector<Route *> unfilledRoutes(solution->getUnfilledRoutes());
        Route *currentRoute(unfilledRoutes.back());
        setNeighborhood(solution, currentRoute);
        Trip *trip = roulette();
        solution->addTrip(trip, currentRoute);
        solution->updateSolution(trip, currentRoute);
    }
    this->updateIds(solution->routes);
    cout << "FASE 2" << endl;
    solution->printAll();
}
