#include "Trip.h"

Trip::Trip(Node * initialNode, Node * finalNode, int distance): initialNode(initialNode), finalNode(finalNode), distance(distance){}

Trip::~Trip() = default;

void Trip::setBenefit(double benefit){ this->benefit = benefit;}

void Trip::setRouteId(int id){ this->routeId = id; }

void Trip::updateInitalNode(Node *node){ this->initialNode = node; }

void Trip::printAll() {
    cout << "trip: " << this->routeId << "  from: " << this->initialNode->getId() << "  to: "
         << this->finalNode->getId() << "  type: "
         << this->finalNode->getType() << " prod: " << this->finalNode->getProduction() << "    dist: "
         << this->distance << "    benefit: " << this->benefit << endl;

}

bool sortByDistance(const Trip *t1, const Trip *t2){ return t1->distance < t2->distance; }

bool sortByBenefit(const Trip *t1, const Trip *t2){ return t1->benefit < t2->benefit; }
