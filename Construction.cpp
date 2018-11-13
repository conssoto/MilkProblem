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
        if (fitsInTruck(solution->routes.back(), option)) { // TODO eliminar trips
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

void Construction::setNeighborhood(Solution *solution) {
    Node *currentNode = solution->getCurrentNode();
    int currentType(solution->getUnsatisfiedType());
    cout << currentType << endl;

    //si volvio a la planta, por que ya se lleno el camion, se crea nueva ruta.
    if (currentNode->getId() == 0 && !solution->routes.back()->trips.empty()) {
        solution->addRoute(currentType);
    }
    vector<Trip *> options(getOptions(solution, currentType, currentNode));

    // si no hay opciones, vuelvo a la planta.
    if (options.empty()) {
        options.push_back(solution->newTrip(currentNode, solution->plant));
    }
    this->neighborhood = options;
}

void Construction::setTotalProduction(){
    this->totalProduction = 0;
    for(Trip *trip: this->neighborhood) { //siempre hay al menos uno, la planta
        this->totalProduction += trip->finalNode->getProduction();
    }
}

Trip *Construction::roulette() { // TODO borrar los no selectionados

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



void Construction::feasibleSolution(Solution *solution) {
    int count(0);
    while(solution->getUnsatisfiedType()!=-1){
        cout << "------------------------ while it: " << count << endl;
        solution->printAll();
        setNeighborhood(solution);
        Trip *trip = roulette();
        solution->addTrip(trip);

        solution->updateSolution(trip);
        cout << "aca" << endl;

        count ++;

    }
}