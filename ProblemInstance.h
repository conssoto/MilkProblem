#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
#include "Truck.h"
#include "Route.h"

using namespace std;

class ProblemInstance {
public:
    int **distances;

    vector<int> qualities;
    vector<Node *> nodes;
    vector<Truck *> trucks;

public:
    explicit ProblemInstance(int totalNodes);
    ~ProblemInstance();

    double getNumberOfNodes();
    double getNumberOfQualities();
    double getNumberOfTrucks();

    void addNode(Node *node);
    void addTruck(Truck *truck);
    void addQuality(int quality);

    void setDistances(int row, int col, int distance);

    int calculateDistance(Node *initialNode, Node *finalNode);

    void sortNodes();

    void printAll();
};
