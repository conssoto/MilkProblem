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
    double benefit;

public:
    Trip(Node *initialNode, Node *finalNode, int distance, double literCost, double kilometerCost);
    ~Trip();

    void setRouteId(int id);
    void updateInitalNode(Node *node);
    void printAll();

    };

bool sortByDistance(const Trip *t1, const Trip *t2);
