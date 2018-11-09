#pragma once
#include "Node.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Trip {
public:
    int id;
    Node *initialNode;
    Node *finalNode;
    double distance;

public:
    Trip(int id, Node *initialNode, Node *finalNode, int distance);
    ~Trip();
};

bool sortByDistance(const Trip *t1, const Trip *t2);
