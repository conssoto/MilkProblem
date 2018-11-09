#include "Trip.h"

Trip::Trip(int id, Node * initialNode, Node * finalNode, int distance):
        id(id), initialNode(initialNode), finalNode(finalNode), distance(distance){}

Trip::~Trip(){cout<< "Deleting Node" << endl;}

bool sortByDistance(const Trip *t1, const Trip *t2){ return t1->distance < t2->distance; }
