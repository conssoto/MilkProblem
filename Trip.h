#pragma once
#include "Node.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Trip {
public:
    int routeId;
    Node *initialNode;
    Node *finalNode;
    double distance;

public:
    Trip(Node *initialNode, Node *finalNode, int distance);
    ~Trip();

    void setRouteId(int id);
    void updateInitalNode(Node *node);

};

bool sortByDistance(const Trip *t1, const Trip *t2);
