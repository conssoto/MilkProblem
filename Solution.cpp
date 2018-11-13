#include "Solution.h"

Solution::Solution(ProblemInstance *problemInstance){
    this->distance = 0;
    setRecollected(problemInstance->getNumberOfQualities());

    this->literCost = {0.03, 0.021, 0.009};
    this->kilometerCost = 220;

    this->plant = new Node(0, 0, 0);
    this->unsatisfiedDemand = problemInstance->qualities;
    setUnusedTrucks(problemInstance->trucks);
    setUnvisitedNodes(problemInstance->nodes);
    setQualities(problemInstance->getNumberOfQualities());

    this->addRoute(1);

    this->problemInstance = problemInstance;
}

Solution::~Solution() {
    cout << "Deleting Solution" << endl;

    delete(this->plant);
    this->plant = nullptr;

    for ( auto it = this->unusedTrucks.begin(); it != this->unusedTrucks.end(); ){
        this->unusedTrucks.erase(it);
    }

    for ( auto it = this->unvisitedNodes.begin(); it != this->unvisitedNodes.end(); ){
        this->unvisitedNodes.erase(it);
    }

    for ( auto it = this->routes.begin(); it != this->routes.end(); ){
        this->routes.erase(it);     // TODO eliminar el trip si se hace con new
    }

    delete problemInstance;
    this->problemInstance = nullptr;
}

void Solution::setRecollected(double size){
    for(int i = 0; i < size; ++i){
        this->recollected.push_back(0);
    }
}

void Solution::setQualities(double size){
    vector<int> aux;
    for(int i = 0; i < size; ++i){
        aux.push_back(0);
    }
    for(Node *node: this->unvisitedNodes){
        aux[node->getTypeIndex()]++;
    }
    for(int i = 0; i < size+1; ++i){
        int init = 0;
        if(i!=0){
            this->nodesXQuality.push_back(accumulate(&aux[0],&aux[i],init));
        }
    }
}

void Solution::setUnusedTrucks(vector<Truck *> trucks){
    for (Truck *truck: trucks){
        Truck *copy = truck;
        addTruck(copy);
    }
}

void Solution::setUnvisitedNodes(vector<Node *> nodes){
    for (Node * node: nodes){
        Node *copy = node;
        this->addNode(copy);
    }
}

void Solution::addNode(Node *node){return this->unvisitedNodes.push_back(node);}

void Solution::addTruck(Truck *truck){this->unusedTrucks.push_back(truck);}

void Solution::addTrip(Trip *trip){
    this->routes.back()->trips.push_back(trip);
}

Trip *Solution::newTrip(Node *node1, Node *node2){
    int distance(problemInstance->calculateDistance(node1, node2));
    return new Trip(0, node1, node2, distance); // TODO arreglar el id trip
}

//crea una nueva ruta a partir del siguiente camion mas grande y lo saca de la lista unused trucks
// TODO podria ser a partir del camion con capacidad mas cercana a la demanda de calidad actual
void Solution::addRoute(int type) {
    Truck *truck = this->getNextTruck();
    auto route = new Route(truck, type);
    this->routes.push_back(route);
    this->removeTruck(truck);
}

int Solution::getUnsatisfiedType() {
    for (int i = 0; i < this->unsatisfiedDemand.size(); ++i) {
        if (this->unsatisfiedDemand[i] != 0) {
            return i + 1;
        }
    }
    return -1; //si ya se suplieron todas las demandas, devuelve cero
}

// entrega el ultimo nodo visitado
Node *Solution::getCurrentNode(){
    if(this->routes.back()->trips.empty()){
        return this->plant;
    }
    return routes.back()->trips.back()->finalNode;
}


// entrega el camion mas grande
Truck *Solution::getNextTruck() {
    return *max_element(this->unusedTrucks.begin(), this->unusedTrucks.end());
}

void Solution::removeTruck(Truck *truck) {
    auto it = find(this->unusedTrucks.begin(), this->unusedTrucks.end(), truck);
    long index = std::distance(this->unusedTrucks.begin(), it);
    this->unusedTrucks.erase(this->unusedTrucks.begin() + index);
}

void Solution::removeNode(Node *node) {
    auto it = find(this->unvisitedNodes.begin(), this->unvisitedNodes.end(), node);
    long index = std::distance(this->unvisitedNodes.begin(), it);
    this->unvisitedNodes.erase(this->unvisitedNodes.begin() + index);
    for (int i = node->getTypeIndex(); i < this->nodesXQuality.size(); ++i) {
        if (nodesXQuality[i] != 0) {
            this->nodesXQuality[i] -= 1;
        }
    }
}

void Solution::decreaseDemand(int position, int production) {
    this->unsatisfiedDemand[position] -= production;
}

void Solution::updateDemands(int position, Trip *trip, int production) { // TODO cuando se satisface la leche sigue con la siguiente en otra ruta
    decreaseDemand(position, production);
    if(this->unsatisfiedDemand[position] < 0){
        if(position < this->unsatisfiedDemand.size()) {
            decreaseDemand(position+1, -this->unsatisfiedDemand[position]); // si se pasa del size
            Trip *toPlant = newTrip(trip->finalNode, this->plant);
            addTrip(toPlant);
        }
    }
}

//int Solution::updateDemands(int position, Trip *trip, int production) { // TODO cuando se satisface la leche sigue con la siguiente en otra ruta
//    if (this->unsatisfiedDemand[position] > production){
//        this->unsatisfiedDemand[position] -= production;
//    }
//    else{
//        for(int i = position; i < this->unsatisfiedDemand.size(); ++i){
//            int rest(production - this->unsatisfiedDemand[position]); //exceso de leche
//            this->unsatisfiedDemand[i]=0;
//            this->unsatisfiedDemand[i+1]-=rest;
//            Trip *toPlant = newTrip(trip->finalNode, this->plant);
//            addTrip(toPlant);
//        }
//    }
//
//
//}

void Solution::updateSolution(Trip *trip) {
    this->distance += trip->distance;
    if (trip->finalNode != this->plant) {
        int tripProduction(trip->finalNode->getProduction());
        this->recollected[trip->finalNode->getTypeIndex()] += tripProduction;
        this->routes.back()->remainingCapacity -= tripProduction;
        updateDemands(this->routes.back()->getTypeIndex(), trip, tripProduction);
        removeNode(trip->finalNode);
    }
    printAll();
}

void Solution::printAll() {
    cout << "distance: " << this->distance << endl;

    double totalRecollected(0);
    cout << "recollected x quality: " << endl;
    for (double r: this->recollected) {
        totalRecollected += r;
        cout << r << endl;
    }

    cout << "Demand satisfaction: " << endl;
    for (double d: this->unsatisfiedDemand) {
        cout << d << endl;
    }

    double totalDemand(0);
    for (int q: this->problemInstance->qualities) {
        totalDemand += q;
    }
    cout << "milk excess: " << totalRecollected - totalDemand << endl;

    cout << "# Unused trucks: " << this->unusedTrucks.size() << endl;
    for (Truck *t: this->unusedTrucks) {
        cout << "truck: " << t->getId() << endl;
    }

    cout << "# Unvisited nodes: " << this->unvisitedNodes.size() << endl;
    for (Node *n: this->unvisitedNodes) {
        cout << " node: " << n->getId() << " type: " << n->getType() << " prod: " << n->getProduction() << endl;
    }

    cout << "# nodes x quality: " << endl;
    for (int q: this->nodesXQuality) {
        cout << q << endl;
    }
//    cout << "Distance cost: " << this->kilometerCost *  this->distance << endl;
//
//    cout << "Milk cost: " << endl;
//    double suma(0);
//    for(int i = 0; i < this->recollected.size(); ++i){
//        suma +=this->recollected[i] * this->literCost[i];
//        cout << this->recollected[i] * this->literCost[i] << endl;
//    }
//    cout << "Total Milk cost: " << suma << endl;

    printRoute();
}

void Solution::printRoute() {
    for (Route *r: this->routes) {
        cout << "Route truck: " << r->truck->getId() << " milk type: " << r->type << endl;
        cout << "Num. of trips: " << r->trips.size() << " remaining Capacity: " << r->remainingCapacity << endl;
        for (Trip *trip: r->trips) {
            cout << "from: " << trip->initialNode->getId() << " to: " << trip->finalNode->getId() << " type: "
                 << trip->finalNode->getType() << " prod: " << trip->finalNode->getProduction() << endl;
        }
    }
}