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
    Trip(Node *initialNode, Node *finalNode, int distancecombinamos);
    ~Trip();

    void setRouteId(int id);
    void setBenefit(double benefit);

    void updateInitalNode(Node *node);
    void printAll();



    };

bool sortByDistance(const Trip *t1, const Trip *t2);

bool sortByBenefit(const Trip *t1, const Trip *t2);

