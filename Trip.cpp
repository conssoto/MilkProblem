#include "Trip.h"

Trip::Trip(Node * initialNode, Node * finalNode, int distance):
        initialNode(initialNode), finalNode(finalNode), distance(distance){}

Trip::~Trip(){}

void Trip::setRouteId(int id){ this->routeId = id; }

void Trip::updateInitalNode(Node *node){ this->initialNode = node; }



bool sortByDistance(const Trip *t1, const Trip *t2){ return t1->distance < t2->distance; }
